#include "phase.h"
#include "symtab.h"

namespace
{
  struct scobind
    : visitor
  {
    node_ptr visit (token &n);
    node_ptr visit (identifier &n);
    node_ptr visit (yaccvar &n);
    node_ptr visit (documents &n);
    node_ptr visit (document &n);
    node_ptr visit (options &n);
    node_ptr visit (directive &n);
    node_ptr visit (default_rule_type &n);
    node_ptr visit (default_token_type &n);
    node_ptr visit (include_enum &n);
    node_ptr visit (token_decl &n);
    node_ptr visit (rules &n);
    node_ptr visit (rule &n);
    node_ptr visit (rule_rhs &n);
    node_ptr visit (rule_alt &n);
    node_ptr visit (rule_alt_part &n);
    node_ptr visit (nonterminal &n);
    node_ptr visit (anonymous_rule &n);
    node_ptr visit (macro_call &n);
    node_ptr visit (macro_args &n);
    node_ptr visit (macro_arg &n);
    node_ptr visit (code &n);

    node_ptr ref;
  };

  static phase<scobind> thisphase ("scobind");
}

node_ptr
scobind::visit (token &n)
{
  return visitor::visit (n);
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
      node_ptr ref = symtab.lookup (n.string.substr (1));
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
      node_ptr ref = symtab.lookup (n.string.substr (1));
      if (!ref)
        throw semantic_error (&n, "could not resolve reference `" + n.string + "'");
      n.ref = ref;
    }
  return visitor::visit (n);
}

node_ptr
scobind::visit (documents &n)
{
  return visitor::visit (n);
}

node_ptr
scobind::visit (document &n)
{
  return visitor::visit (n);
}

node_ptr
scobind::visit (options &n)
{
  return visitor::visit (n);
}

node_ptr
scobind::visit (directive &n)
{
  return visitor::visit (n);
}

node_ptr
scobind::visit (default_rule_type &n)
{
  return visitor::visit (n);
}

node_ptr
scobind::visit (default_token_type &n)
{
  return visitor::visit (n);
}

node_ptr
scobind::visit (include_enum &n)
{
  return visitor::visit (n);
}

node_ptr
scobind::visit (token_decl &n)
{
  return visitor::visit (n);
}

node_ptr
scobind::visit (rules &n)
{
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
scobind::visit (rule_rhs &n)
{
  return visitor::visit (n);
}

node_ptr
scobind::visit (rule_alt &n)
{
  symtab.enter_scope (&n);
  visitor::visit (n);
  symtab.leave_scope ();
  return &n;
}

node_ptr
scobind::visit (rule_alt_part &n)
{
  return visitor::visit (n);
}

node_ptr
scobind::visit (nonterminal &n)
{
  return visitor::visit (n);
}

node_ptr
scobind::visit (anonymous_rule &n)
{
  return visitor::visit (n);
}

node_ptr
scobind::visit (macro_call &n)
{
  return visitor::visit (n);
}

node_ptr
scobind::visit (macro_args &n)
{
  return visitor::visit (n);
}

node_ptr
scobind::visit (macro_arg &n)
{
  return visitor::visit (n);
}

node_ptr
scobind::visit (code &n)
{
  return visitor::visit (n);
}
