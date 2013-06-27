#include "node.h"
#include "phase.h"
#include "visitor.h"

using namespace nodes;
using namespace tokens;

node_ptr
visitor::visit (token &n)
{
  return &n;
}

node_ptr
visitor::visit (identifier &n)
{
  return &n;
}

node_ptr
visitor::visit (yaccvar &n)
{
  return &n;
}


node_ptr
visitor::visit (documents &n)
{
  resume_list ();
  return &n;
}

node_ptr
visitor::visit (document &n)
{
  resume (prologue);
  resume (options);
  resume (rules);
  resume (epilogue);
  return &n;
}

node_ptr
visitor::visit (options &n)
{
  resume_list ();
  return &n;
}

node_ptr
visitor::visit (directive &n)
{
  resume (dir);
  resume_if (a1);
  resume_if (a2);
  resume_if (a3);
  return &n;
}

node_ptr
visitor::visit (default_rule_type &n)
{
  resume (type);
  return &n;
}

node_ptr
visitor::visit (default_token_type &n)
{
  resume (type);
  return &n;
}

node_ptr
visitor::visit (include_enum &n)
{
  resume (file);
  resume (id);
  return &n;
}

node_ptr
visitor::visit (token_decl &n)
{
  resume_if (type);
  resume (name);
  resume_if (num);
  resume_if (desc);
  return &n;
}

node_ptr
visitor::visit (rules &n)
{
  resume_list ();
  return &n;
}

node_ptr
visitor::visit (rule &n)
{
  resume (nonterm);
  resume_if (type);
  resume (rhs);
  return &n;
}

node_ptr
visitor::visit (rule_rhs &n)
{
  resume_list ();
  return &n;
}

node_ptr
visitor::visit (rule_alt &n)
{
  resume_list ();
  return &n;
}

node_ptr
visitor::visit (rule_alt_part &n)
{
  resume (part);
  resume_if (name);
  return &n;
}

node_ptr
visitor::visit (nonterminal &n)
{
  resume (nonterm);
  return &n;
}

node_ptr
visitor::visit (anonymous_rule &n)
{
  resume (rule);
  resume_if (type);
  return &n;
}

node_ptr
visitor::visit (macro_call &n)
{
  resume (macro);
  resume_if (args);
  return &n;
}

node_ptr
visitor::visit (macro_args &n)
{
  resume_list ();
  return &n;
}

node_ptr
visitor::visit (macro_arg &n)
{
  resume_if (name);
  resume (arg);
  return &n;
}

node_ptr
visitor::visit (code &n)
{
  resume_list ();
  return &n;
}
