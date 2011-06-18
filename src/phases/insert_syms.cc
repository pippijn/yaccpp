#include "phase.h"
#include "symtab.h"

#include <boost/lexical_cast.hpp>

namespace
{
  struct insert_syms
    : visitor
  {
    node_ptr visit (token &n);
    node_ptr visit (identifier &n);
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

    int altc;
  };

  static phase<insert_syms> thisphase ("insert_syms");
}

node_ptr
insert_syms::visit (token &n)
{
  return visitor::visit (n);
}

#include "is_ref.h"

node_ptr
insert_syms::visit (identifier &n)
{
  if (!is_ref (n.string[0]))
    symtab.insert (n.string, &n);
  return visitor::visit (n);
}

node_ptr
insert_syms::visit (documents &n)
{
  return visitor::visit (n);
}

node_ptr
insert_syms::visit (document &n)
{
  return visitor::visit (n);
}

node_ptr
insert_syms::visit (options &n)
{
  return visitor::visit (n);
}

node_ptr
insert_syms::visit (directive &n)
{
  return visitor::visit (n);
}

node_ptr
insert_syms::visit (default_rule_type &n)
{
  return visitor::visit (n);
}

node_ptr
insert_syms::visit (default_token_type &n)
{
  return visitor::visit (n);
}

node_ptr
insert_syms::visit (include_enum &n)
{
  return visitor::visit (n);
}

node_ptr
insert_syms::visit (token_decl &n)
{
  return visitor::visit (n);
}

node_ptr
insert_syms::visit (rules &n)
{
  return visitor::visit (n);
}

node_ptr
insert_syms::visit (rule &n)
{
  symtab.enter_scope (&n);
  symtab.insert ("$", n.nonterm);
  visitor::visit (n);
  symtab.leave_scope ();
  return &n;
}

node_ptr
insert_syms::visit (rule_rhs &n)
{
  return visitor::visit (n);
}

node_ptr
insert_syms::visit (rule_alt &n)
{
  symtab.enter_scope (&n);
  altc = 1;
  visitor::visit (n);
  symtab.leave_scope ();
  return &n;
}

node_ptr
insert_syms::visit (rule_alt_part &n)
{
  symtab.insert (boost::lexical_cast<std::string> (altc++), n.part);
  if (n.name)
    symtab.insert (n.name->as<identifier> ().string, n.part);
  return visitor::visit (n);
}

node_ptr
insert_syms::visit (nonterminal &n)
{
  return visitor::visit (n);
}

node_ptr
insert_syms::visit (anonymous_rule &n)
{
  return visitor::visit (n);
}

node_ptr
insert_syms::visit (macro_call &n)
{
  return visitor::visit (n);
}

node_ptr
insert_syms::visit (macro_args &n)
{
  return visitor::visit (n);
}

node_ptr
insert_syms::visit (macro_arg &n)
{
  return visitor::visit (n);
}

node_ptr
insert_syms::visit (code &n)
{
  return visitor::visit (n);
}
