#include "phase.h"
#include "symtab.h"

namespace
{
  struct scobind
    : visitor
  {
    node_ptr visit (identifier &n);
    node_ptr visit (yaccvar &n);
    node_ptr visit (rule &n);
    node_ptr visit (rule_alt &n);

    node_ptr ref;
  };

  static phase<scobind> thisphase ("scobind");
}

struct selfref_error
  : visitor
{
  selfref_error (identifier &n)
    : n (n)
  {
  }

  node_ptr visit (identifier &n)
  {
    if (&n == &this->n)
      throw semantic_error (&n, "variable `" + n.string + "' references itself (eventually)");
    return &n;
  }

  identifier &n;
};


node_ptr
scobind::visit (identifier &n)
{
  if (n.string[0] == '$')
    {
      node_ptr ref = symtab.lookup (T_NONTERM, n.string.substr (1));
      if (!ref)
        throw semantic_error (&n, "could not resolve reference `" + n.string + "'");

      selfref_error find_selfref (n);
      ref->accept (find_selfref);

      n.ref = ref;
    }
  return visitor::visit (n);
}

node_ptr
scobind::visit (yaccvar &n)
{
  if (n.string[0] == '$')
    {
      node_ptr ref = symtab.lookup (T_NONTERM, n.string.substr (1));
      if (!ref)
        throw semantic_error (&n, "could not resolve reference `" + n.string + "'");
      n.ref = ref;
    }
  return visitor::visit (n);
}

node_ptr
scobind::visit (rule &n)
{
  symtab.enter_scope (&n);
  visitor::visit (n);
  symtab.leave_scope ();
  return &n;
}

node_ptr
scobind::visit (rule_alt &n)
{
  symtab.enter_scope (&n);
  visitor::visit (n);
  symtab.leave_scope ();
  return &n;
}
