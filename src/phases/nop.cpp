#include "phase.h"

namespace
{
  struct nop
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
    node_ptr visit (nonterminal &n);
    node_ptr visit (anonymous_rule &n);
    node_ptr visit (macro_call &n);
    node_ptr visit (macro_args &n);
    node_ptr visit (macro_arg &n);
    node_ptr visit (code &n);
  };

  static phase<nop> thisphase ("nop");
}

node_ptr
nop::visit (token &n)
{
  return visitor::visit (n);
}

node_ptr
nop::visit (identifier &n)
{
  return visitor::visit (n);
}

node_ptr
nop::visit (yaccvar &n)
{
  return visitor::visit (n);
}

node_ptr
nop::visit (documents &n)
{
  return visitor::visit (n);
}

node_ptr
nop::visit (document &n)
{
  return visitor::visit (n);
}

node_ptr
nop::visit (options &n)
{
  return visitor::visit (n);
}

node_ptr
nop::visit (directive &n)
{
  return visitor::visit (n);
}

node_ptr
nop::visit (default_rule_type &n)
{
  return visitor::visit (n);
}

node_ptr
nop::visit (default_token_type &n)
{
  return visitor::visit (n);
}

node_ptr
nop::visit (include_enum &n)
{
  return visitor::visit (n);
}

node_ptr
nop::visit (token_decl &n)
{
  return visitor::visit (n);
}

node_ptr
nop::visit (rules &n)
{
  return visitor::visit (n);
}

node_ptr
nop::visit (rule &n)
{
  return visitor::visit (n);
}

node_ptr
nop::visit (rule_rhs &n)
{
  return visitor::visit (n);
}

node_ptr
nop::visit (rule_alt &n)
{
  return visitor::visit (n);
}

node_ptr
nop::visit (nonterminal &n)
{
  return visitor::visit (n);
}

node_ptr
nop::visit (anonymous_rule &n)
{
  return visitor::visit (n);
}

node_ptr
nop::visit (macro_call &n)
{
  return visitor::visit (n);
}

node_ptr
nop::visit (macro_args &n)
{
  return visitor::visit (n);
}

node_ptr
nop::visit (macro_arg &n)
{
  return visitor::visit (n);
}

node_ptr
nop::visit (code &n)
{
  return visitor::visit (n);
}
