#include "printer.h"
#include "node.h"
#include "ylcode.h"

#include <cstdio>

#include <boost/foreach.hpp>

#define resume(member) n.member->accept (*this)
#define resume_if(member) if (n.member) resume (member)

void
printer::visit (nodes::token &n)
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
  //printf ("%-16s: \"%s\"\n", yytokname (n.tok - 255), n.string.c_str ());
}

void
printer::visit (nodes::documents &n)
{
  BOOST_FOREACH (node_ptr const &p, n.list)
    {
      p->accept (*this);
    }
}

void
printer::visit (nodes::document &n)
{
  printf ("%{");
  resume (prologue);
  printf ("%}\n");
  resume (options);
  puts ("\n%%\n");
  resume (rules);
  puts ("\n%%\n");
  resume (epilogue);
  printf ("\n");
}

void
printer::visit (nodes::options &n)
{
  BOOST_FOREACH (node_ptr const &p, n.list)
    {
      p->accept (*this);
    }
}

void
printer::visit (nodes::directive &n)
{
  resume (dir);
  printf (" ");
  resume_if (a1);
  printf (" ");
  resume_if (a2);
  printf (" ");
  resume_if (a3);
  printf ("\n");
}

void
printer::visit (nodes::default_rule_type &n)
{
  printf ("%%default-rule-type ");
  resume (type);
  printf ("\n");
}

void
printer::visit (nodes::default_token_type &n)
{
  printf ("%%default-token-type ");
  resume (type);
  printf ("\n");
}

void
printer::visit (nodes::include_enum &n)
{
  printf ("%%include-enum ");
  resume (file);
  printf (" ");
  resume (id);
  printf ("\n");
}

void
printer::visit (nodes::token_decl &n)
{
  printf ("%%token");
  resume_if (type);
  printf (" ");
  resume (name);
  printf (" ");
  resume_if (num), printf (" ");
  resume_if (desc);
  printf ("\n");
}

void
printer::visit (nodes::rules &n)
{
  BOOST_FOREACH (node_ptr const &p, n.list)
    {
      p->accept (*this);
      printf ("\n");
    }
}

void
printer::visit (nodes::rule &n)
{
  resume (nonterm);
  resume_if (type);
  printf ("\n\t:");
  resume (rhs);
  printf ("\n\t;\n");
}

void
printer::visit (nodes::rule_rhs &n)
{
  BOOST_FOREACH (node_ptr const &p, n.list)
    {
      p->accept (*this);
      if (&p != &n.list.back ())
        printf ("\n\t|");
    }
}

void
printer::visit (nodes::rule_alt &n)
{
  BOOST_FOREACH (node_ptr const &p, n.list)
    {
      printf (" ");
      p->accept (*this);
    }
}

void
printer::visit (nodes::macro_call &n)
{
  resume (macro);
  resume_if (args);
  if (n.name)
    {
      printf ("[");
      resume (name);
      printf ("]");
    }
}

void
printer::visit (nodes::macro_args &n)
{
  printf ("(");
  BOOST_FOREACH (node_ptr const &p, n.list)
    {
      p->accept (*this);
      if (&p != &n.list.back ())
        printf (", ");
    }
  printf (")");
}

void
printer::visit (nodes::code &n)
{
  printf ("\n\t\t{");
  BOOST_FOREACH (node_ptr const &p, n.list)
    {
      p->accept (*this);
    }
  printf ("}");
}
