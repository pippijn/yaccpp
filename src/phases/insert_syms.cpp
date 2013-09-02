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

    ~insert_syms ()
    {
      //symtab->print ();
    }

    enum state_type
    {
      S_NONE,
      S_IN_ALT,
      S_IN_ARGLIST
    };

    node_ptr sym;
    int altc;
    state_type state;
    symbol_type symtype;
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
    symtab->insert (symtype, n.string, sym ? move (sym) : &n);
  return visitor::visit (n);
}

node_ptr
insert_syms::visit (documents &n)
{
  symtab->clear ();
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
  state = S_NONE;
  symtype = T_NONTERM;
  return visitor::visit (n);
}

node_ptr
insert_syms::visit (rule &n)
{
  symtab->enter_scope (&n);
  symtab->insert (T_NONTERM, "$", n.nonterm);
  {
    local (sym) = &n;
    resume (nonterm);
  }
  resume_if (type);
  resume (rhs);
  symtab->leave_scope ();
  return &n;
}

node_ptr
insert_syms::visit (rule_rhs &n)
{
  local (state) = S_IN_ALT;
  return visitor::visit (n);
}

node_ptr
insert_syms::visit (rule_alt &n)
{
  symtab->enter_scope (&n);
  altc = 1;
  visitor::visit (n);
  symtab->leave_scope ();
  return &n;
}

node_ptr
insert_syms::visit (rule_alt_part &n)
{
  resume (part);
  symtab->insert (T_NONTERM, boost::lexical_cast<std::string> (altc++), n.part);
  if (n.name)
    {
      local (sym) = n.part;
      resume (name);
    }
  return &n;
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
  if (state == S_NONE)
    {
      //printf ("macro definition\n");
      local (symtype) = T_MACRO;
      // sym comes from rule
      resume (macro);
    }
  else
    {
      resume (macro);
    }
  if (n.args)
    {
      local (state) = S_IN_ARGLIST;
      resume (args);
    }
  return &n;
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
