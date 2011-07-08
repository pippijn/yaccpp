#include "node.h"
#include "phases.h"
#include "symtab.h"

#include <cstdio>
#include <stdexcept>
#include <typeinfo>

#include <boost/foreach.hpp>

symbol_table symtab;

static node_ptr ambiguous = new tokens::identifier ("<ambiguous>");

void
symbol_table::enter_scope (node_ptr scope)
{
#if 0
  puts ("enter_scope");
#endif
  stack.push_back (&scopes[scope]);
}

void
symbol_table::leave_scope ()
{
#if 0
  puts ("leave_scope");
#endif
  stack.pop_back ();
}

static symbol_table::node_map &
get_scope (symbol_table::type_map &map, symbol_type type)
{
  if (map.size () <= type)
    map.resize (type + 1);
  return map[type];
}

void
symbol_table::insert (symbol_type type, std::string const &name, node_ptr id)
{
  if (stack.empty ())
    return;

#if 0
  printf ("insert (%s)\n", name.c_str ());
#endif

  node_map &scope = get_scope (*stack.back (), type);

  if (scope[name])
    scope[name] = ambiguous;
  else
    scope[name] = id;
}

node_ptr
symbol_table::lookup (symbol_type type, std::string const &name)
{
  node_ptr resolved;
  size_t scope = stack.size ();
#if 0
  printf ("lookup: %d scopes for %s\n", scope, name.c_str ());
#endif
  while (!resolved && scope)
    resolved = get_scope (*stack[--scope], type)[name];
  return resolved;
}

static char const *
symbol_type_name (int type)
{
  switch (type)
    {
    case T_MACRO:   return "macro";
    case T_NONTERM: return "nonterm";
    }

  throw std::runtime_error ("invalid symbol type");
}

void
symbol_table::print () const
{
  puts ("symbol table:");
  BOOST_FOREACH (scope_map::const_reference scope, scopes)
    {
      printf ("scope for %s[%d]\n", scope.first->node_type (), scope.first->index);
      BOOST_FOREACH (node_map const &type, scope.second)
        if (!type.empty ())
          {
            printf ("  type %s\n", symbol_type_name (scope.second.size () - (&scope.second.back () - &type) - 1));
            BOOST_FOREACH (node_map::const_reference sym, type)
              {
                printf ("    sym %s (%s[%d])\n", sym.first.c_str (), sym.second->node_type (), sym.second->index);
              }
          }
    }
}
