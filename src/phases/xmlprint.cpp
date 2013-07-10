#include "phase.h"

namespace
{
  struct xmlprint
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
  };

  static phase<xmlprint> thisphase ("xmlprint");
}


struct xmlelement
{
  xmlelement (char const *name)
    : name (name)
    , eol (true)
  {
    printf ("<%s>", name);
  }

  void cdata (std::string const &data)
  {
    printf ("<![CDATA[%s]]>\n", data.c_str ());
  }

  void noeol ()
  {
    eol = false;
  }

  ~xmlelement ()
  {
    printf ("%s</%s>\n", eol ? "\n" : "", name);
  }

  char const *const name;
  bool eol;
};

#define xmlresume(member) do { xmlelement e (#member); if (n.member) n.member->accept (*this); else e.noeol (); } while (0)

node_ptr
xmlprint::visit (token &n)
{
  xmlelement e ("token");
  e.cdata (n.string);
  return &n;
}

node_ptr
xmlprint::visit (identifier &n)
{
  xmlelement e ("identifier");
  e.cdata (n.string);
  return &n;
}

node_ptr
xmlprint::visit (yaccvar &n)
{
  xmlelement e ("yaccvar");
  e.cdata (n.string);
  return &n;
}

node_ptr
xmlprint::visit (documents &n)
{
  xmlelement e ("documents");
  resume_list ();
  return &n;
}

node_ptr
xmlprint::visit (document &n)
{
  xmlelement e ("document");
  xmlresume (prologue);
  xmlresume (options);
  xmlresume (rules);
  xmlresume (epilogue);
  return &n;
}

node_ptr
xmlprint::visit (options &n)
{
  xmlelement e ("options");
  resume_list ();
  return &n;
}

node_ptr
xmlprint::visit (directive &n)
{
  xmlelement e ("directive");
  xmlresume (dir);
  xmlresume (a1);
  xmlresume (a2);
  xmlresume (a3);
  return &n;
}

node_ptr
xmlprint::visit (default_rule_type &n)
{
  xmlelement e ("default_rule_type");
  xmlresume (type);
  return &n;
}

node_ptr
xmlprint::visit (default_token_type &n)
{
  xmlelement e ("default_token_type");
  xmlresume (type);
  return &n;
}

node_ptr
xmlprint::visit (include_enum &n)
{
  xmlelement e ("include_enum");
  xmlresume (file);
  xmlresume (id);
  return &n;
}

node_ptr
xmlprint::visit (token_decl &n)
{
  xmlelement e ("token_decl");
  xmlresume (type);
  xmlresume (name);
  xmlresume (num);
  xmlresume (desc);
  return &n;
}

node_ptr
xmlprint::visit (rules &n)
{
  xmlelement e ("rules");
  resume_list ();
  return &n;
}

node_ptr
xmlprint::visit (rule &n)
{
  xmlelement e ("rule");
  xmlresume (nonterm);
  xmlresume (type);
  xmlresume (rhs);
  return &n;
}

node_ptr
xmlprint::visit (rule_rhs &n)
{
  xmlelement e ("rule_rhs");
  resume_list ();
  return &n;
}

node_ptr
xmlprint::visit (rule_alt &n)
{
  xmlelement e ("rule_alt");
  resume_list ();
  return &n;
}

node_ptr
xmlprint::visit (rule_alt_part &n)
{
  xmlelement e ("rule_alt_part");
  xmlresume (part);
  xmlresume (name);
  return &n;
}

node_ptr
xmlprint::visit (nonterminal &n)
{
  xmlelement e ("nonterminal");
  xmlresume (nonterm);
  return &n;
}

node_ptr
xmlprint::visit (anonymous_rule &n)
{
  xmlelement e ("anonymous_rule");
  xmlresume (rule);
  xmlresume (type);
  return &n;
}

node_ptr
xmlprint::visit (macro_call &n)
{
  xmlelement e ("macro_call");
  xmlresume (macro);
  xmlresume (args);
  return &n;
}

node_ptr
xmlprint::visit (macro_args &n)
{
  xmlelement e ("macro_args");
  resume_list ();
  return &n;
}

node_ptr
xmlprint::visit (macro_arg &n)
{
  xmlelement e ("macro_arg");
  xmlresume (name);
  xmlresume (arg);
  return &n;
}

node_ptr
xmlprint::visit (code &n)
{
  xmlelement e ("code");
  resume_list ();
  return &n;
}
