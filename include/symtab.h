#pragma once

#include "node_ptr.h"

#include <map>
#include <string>
#include <vector>

struct symbol_table
{
  void enter_scope (nodes::node_ptr scope);
  void leave_scope ();

  void insert (std::string const &name, nodes::node_ptr id);
  nodes::node_ptr lookup (std::string const &name);


private:
  typedef std::map<std::string, nodes::node_ptr> node_map;
  typedef std::map<nodes::node_ptr, node_map> scope_map;

  std::vector<node_map *> stack;
  scope_map scopes;
};

extern symbol_table symtab;
