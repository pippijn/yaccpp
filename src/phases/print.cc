#include "phase.h"

#include <cstdio>

#include <boost/foreach.hpp>

#undef resume_list
#define resume_list(p)          BOOST_FOREACH (node_ptr const &p, n.list)

using namespace nodes;

namespace
{
  struct print
    : visitor
  {
    node_ptr visit (token &n);
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
    node_ptr visit (macro_call &n);
    node_ptr visit (macro_args &n);
    node_ptr visit (macro_arg &n);
    node_ptr visit (code &n);

    print ();

    bool in_rule_alt;
  };

  static phase<print> thisphase ("print");
}


print::print ()
  : in_rule_alt (false)
{
}

node_ptr
print::visit (token &n)
{
  switch (n.tok)
    {
    case TK_TYPE:
      printf ("<%s>", n.string.c_str ());
      break;
    default:
      printf ("%s", n.string.c_str ());
      break;
    }
  return &n;
}

node_ptr
print::visit (document &n)
{
  printf ("%%{");
  resume (prologue);
  printf ("%%}\n\n");
  resume (options);
  puts ("\n%%");
  resume (rules);
  printf ("%%%%");
  resume (epilogue);
  return &n;
}

node_ptr
print::visit (options &n)
{
  resume_list (p)
    {
      p->accept (*this);
    }
  return &n;
}

node_ptr
print::visit (directive &n)
{
  resume (dir);
  printf (" ");
  resume_if (a1);
  printf (" ");
  resume_if (a2);
  printf (" ");
  resume_if (a3);
  printf ("\n");
  return &n;
}

node_ptr
print::visit (default_rule_type &n)
{
  printf ("%%default-rule-type ");
  resume (type);
  printf ("\n");
  return &n;
}

node_ptr
print::visit (default_token_type &n)
{
  printf ("%%default-token-type ");
  resume (type);
  printf ("\n");
  return &n;
}

node_ptr
print::visit (include_enum &n)
{
  printf ("%%include-enum ");
  resume (file);
  printf (" ");
  resume (id);
  printf ("\n");
  return &n;
}

node_ptr
print::visit (token_decl &n)
{
  printf ("%%token");
  resume_if (type);
  printf (" ");
  resume (name);
  printf (" ");
  resume_if (num), printf (" ");
  resume_if (desc);
  printf ("\n");
  return &n;
}

node_ptr
print::visit (rules &n)
{
  resume_list (p)
    {
      p->accept (*this);
      printf ("\n");
    }
  return &n;
}

node_ptr
print::visit (rule &n)
{
  resume (nonterm);
  resume_if (type);
  printf ("\n\t:");
  resume (rhs);
  printf ("\n\t;\n");
  return &n;
}

node_ptr
print::visit (rule_rhs &n)
{
  if (in_rule_alt)
    printf ("(");
  resume_list (p)
    {
      p->accept (*this);
      if (&p != &n.list.back ())
        {
          printf (in_rule_alt ? " " : "\n\t");
          printf ("|");
          if (in_rule_alt)
            printf (" ");
        }
    }
  if (in_rule_alt)
    printf (")");
  return &n;
}

node_ptr
print::visit (rule_alt &n)
{
  resume_list (p)
    {
      bool const was_rule_alt = in_rule_alt;
      in_rule_alt = true;
      if (!was_rule_alt)
        printf (" ");
      p->accept (*this);
      if (&p != &n.list.back () && was_rule_alt)
        printf (" ");
      in_rule_alt = was_rule_alt;
    }
  return &n;
}

node_ptr
print::visit (nonterminal &n)
{
  resume (nonterm);
  BOOST_FOREACH (char cardinality, n.cardinality)
    if (cardinality)
      printf ("%c", cardinality);
  return &n;
}

node_ptr
print::visit (macro_call &n)
{
  resume (macro);
  resume_if (args);
  if (n.name)
    {
      printf ("[");
      resume (name);
      printf ("]");
    }
  return &n;
}

node_ptr
print::visit (macro_args &n)
{
  printf ("(");
  resume_list (p)
    {
      p->accept (*this);
      if (&p != &n.list.back ())
        printf (", ");
    }
  if (n.is_variadic)
    printf ("...");
  printf (")");
  return &n;
}

node_ptr
print::visit (macro_arg &n)
{
  resume_if (name), printf (": ");
  resume (arg);
  return &n;
}

node_ptr
print::visit (code &n)
{
  printf ("\n\t\t{");
  resume_list (p)
    {
      p->accept (*this);
    }
  printf ("}");
  return &n;
}
