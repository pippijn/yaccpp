#include "phase.h"
#include "symtab.h"

namespace
{
  struct call_macros
    : visitor
  {
    node_ptr visit (identifier &n);
    node_ptr visit (rule &n);
    node_ptr visit (rule_alt &n);

    enum state_type
    {
      S_NONE,
      S_IN_ALT
    };

    node_ptr ref;
    state_type state;
  };

  static phase<call_macros> thisphase ("call_macros");
}


static bool
has_args (node &n)
{
  return n.as<rule> ().nonterm->as<macro_call> ().args != NULL;
}

node_ptr
call_macros::visit (identifier &n)
{
  if (state == S_IN_ALT)
    if (node_ptr ref = symtab.lookup (T_MACRO, n.string))
      if (has_args (*ref))
        {
          printf ("calling macro %s\n", n.string.c_str ());
          phases::run ("print", ref);
        }
  return visitor::visit (n);
}

node_ptr
call_macros::visit (rule &n)
{
  state = S_NONE;
  symtab.enter_scope (&n);
  visitor::visit (n);
  symtab.leave_scope ();
  return &n;
}

node_ptr
call_macros::visit (rule_alt &n)
{
  state = S_IN_ALT;
  symtab.enter_scope (&n);
  visitor::visit (n);
  symtab.leave_scope ();
  return &n;
}
