#pragma once

#include "node_ptr.h"

#include <map>
#include <string>
#include <vector>

enum symbol_type
{
  T_MACRO,
  T_NONTERM
};

struct symbol_table
{
  void enter_scope (nodes::node_ptr scope);
  void leave_scope ();

  void insert (symbol_type type, std::string const &name, nodes::node_ptr id);
  nodes::node_ptr lookup (symbol_type type, std::string const &name);

  void clear () { assert (stack.empty ()); scopes.clear (); }
  void print () const;


  typedef std::map<std::string, nodes::node_ptr> node_map;
  typedef std::vector<node_map> type_map;
  typedef std::map<nodes::node_ptr, type_map> scope_map;

  std::vector<type_map *> stack;
  scope_map scopes;
};

extern symbol_table *symtab;
