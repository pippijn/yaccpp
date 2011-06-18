#include "symtab.h"
#include "node.h"
#include <cstdio>

symbol_table symtab;

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

void
symbol_table::insert (std::string const &name, node_ptr id)
{
  if (stack.empty ())
    return;

#if 0
  printf ("insert (%s)\n", name.c_str ());
#endif

  node_map &scope = *stack.back ();

  if (!scope[name])
    scope[name] = id;
}

node_ptr
symbol_table::lookup (std::string const &name)
{
  node_ptr resolved;
  size_t scope = stack.size ();
#if 0
  printf ("lookup: %d scopes for %s\n", scope, name.c_str ());
#endif
  while (!resolved && scope)
    resolved = (*stack[--scope])[name];
  return resolved;
}
