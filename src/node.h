#pragma once

#include <list>
#include <string>
#include <vector>

#include "visitor.h"

struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;

  std::string const *file;
};
#define YYLTYPE_IS_DECLARED 1
#define YYLTYPE_IS_TRIVIAL 1

namespace nodes
{
  struct node
  {
    virtual char const *node_type () const = 0;
    virtual node_ptr accept (visitor &v) = 0;
    node ();
    virtual ~node ();

    template<typename T>
    T &as ()
    {
      return dynamic_cast<T &> (*this);
    }

    void *operator new (size_t bytes);
    void operator delete (void *ptr, size_t bytes);

    YYLTYPE loc;
    int refcnt;
    int index;

    static std::vector<node *> nodes;
    static void compress_hash ();
    static bool audit_hash ();
  };

  struct node_list
    : node
  {
    node_list *add (node_ptr n) { list.push_back (n); return this; }

    std::list<node_ptr> list;
  };

  template<typename Derived>
  struct node_list_t
    : node_list
  {
    Derived *add (node_ptr n) { list.push_back (n); return static_cast<Derived *> (this); }
  };


  struct documents
    : node_list_t<documents>
  {
    virtual char const *node_type () const { return "documents"; }
    virtual node_ptr accept (visitor &v) { return v.visit (*this); }
  };
  
  struct document
    : node
  {
    virtual char const *node_type () const { return "document"; }
    virtual node_ptr accept (visitor &v) { return v.visit (*this); }
    document (node_ptr prologue, node_ptr options, node_ptr rules, node_ptr epilogue) : prologue (prologue), options (options), rules (rules), epilogue (epilogue) { }

    node_ptr prologue;
    node_ptr options;
    node_ptr rules;
    node_ptr epilogue;
  };

  struct options
    : node_list_t<options>
  {
    virtual char const *node_type () const { return "options"; }
    virtual node_ptr accept (visitor &v) { return v.visit (*this); }
  };
  
  struct directive
    : node
  {
    virtual char const *node_type () const { return "directive"; }
    virtual node_ptr accept (visitor &v) { return v.visit (*this); }
    directive (node_ptr dir, node_ptr a1 = 0, node_ptr a2 = 0, node_ptr a3 = 0) : dir (dir), a1 (a1), a2 (a2), a3 (a3) { }

    node_ptr dir;
    node_ptr a1;
    node_ptr a2;
    node_ptr a3;
  };
  
  struct default_rule_type
    : node
  {
    virtual char const *node_type () const { return "default_rule_type"; }
    virtual node_ptr accept (visitor &v) { return v.visit (*this); }
    default_rule_type (node_ptr type) : type (type) { }

    node_ptr type;
  };
  
  struct default_token_type
    : node
  {
    virtual char const *node_type () const { return "default_token_type"; }
    virtual node_ptr accept (visitor &v) { return v.visit (*this); }
    default_token_type (node_ptr type) : type (type) { }

    node_ptr type;
  };
  
  struct include_enum
    : node
  {
    virtual char const *node_type () const { return "include_enum"; }
    virtual node_ptr accept (visitor &v) { return v.visit (*this); }
    include_enum (node_ptr file, node_ptr id) : file (file), id (id) { }

    node_ptr file;
    node_ptr id;
  };
  
  struct token_decl
    : node
  {
    virtual char const *node_type () const { return "token_decl"; }
    virtual node_ptr accept (visitor &v) { return v.visit (*this); }
    token_decl (node_ptr type, node_ptr name, node_ptr num, node_ptr desc) : type (type), name (name), num (num), desc (desc) { }

    node_ptr type;
    node_ptr name;
    node_ptr num;
    node_ptr desc;
  };
  
  struct rules
    : node_list_t<rules>
  {
    virtual char const *node_type () const { return "rules"; }
    virtual node_ptr accept (visitor &v) { return v.visit (*this); }
  };
  
  struct rule
    : node
  {
    virtual char const *node_type () const { return "rule"; }
    virtual node_ptr accept (visitor &v) { return v.visit (*this); }
    rule (node_ptr nonterm, node_ptr type, node_ptr rhs) : nonterm (nonterm), type (type), rhs (rhs) { }

    node_ptr nonterm;
    node_ptr type;
    node_ptr rhs;
  };
  
  struct rule_rhs
    : node_list_t<rule_rhs>
  {
    virtual char const *node_type () const { return "rule_rhs"; }
    virtual node_ptr accept (visitor &v) { return v.visit (*this); }
  };
  
  struct rule_alt
    : node_list_t<rule_alt>
  {
    virtual char const *node_type () const { return "rule_alt"; }
    virtual node_ptr accept (visitor &v) { return v.visit (*this); }
  };
  
  struct rule_alt_part
    : node
  {
    virtual char const *node_type () const { return "rule_alt_part"; }
    virtual node_ptr accept (visitor &v) { return v.visit (*this); }
    rule_alt_part (node_ptr part, node_ptr name) : part (part), name (name) { }

    node_ptr part;
    node_ptr name;
  };
  
  struct nonterminal
    : node
  {
    virtual char const *node_type () const { return "nonterminal"; }
    virtual node_ptr accept (visitor &v) { return v.visit (*this); }
    nonterminal (node_ptr nonterm, char c1, char c2, char c3)
      : nonterm (nonterm)
    {
      cardinality[0] = c1;
      cardinality[1] = c2;
      cardinality[2] = c3;
    }

    node_ptr nonterm;
    short cardinality[3];
  };
  
  struct anonymous_rule
    : node
  {
    virtual char const *node_type () const { return "anonymous_rule"; }
    virtual node_ptr accept (visitor &v) { return v.visit (*this); }
    anonymous_rule (node_ptr rule, node_ptr type) : rule (rule), type (type) { }

    node_ptr rule;
    node_ptr type;
  };
  
  struct macro_call
    : node
  {
    virtual char const *node_type () const { return "macro_call"; }
    virtual node_ptr accept (visitor &v) { return v.visit (*this); }
    macro_call (node_ptr macro, node_ptr args) : macro (macro), args (args) { }

    node_ptr macro;
    node_ptr args;
  };
  
  struct macro_args
    : node_list_t<macro_args>
  {
    virtual char const *node_type () const { return "macro_args"; }
    virtual node_ptr accept (visitor &v) { return v.visit (*this); }
    macro_args () : is_variadic (false) { }

    bool is_variadic;
  };
  
  struct macro_arg
    : node
  {
    virtual char const *node_type () const { return "macro_arg"; }
    virtual node_ptr accept (visitor &v) { return v.visit (*this); }
    macro_arg (node_ptr name, node_ptr arg) : name (name), arg (arg) { }

    node_ptr name;
    node_ptr arg;
  };
  
  struct code
    : node_list_t<code>
  {
    virtual char const *node_type () const { return "code"; }
    virtual node_ptr accept (visitor &v) { return v.visit (*this); }
  };
}

namespace tokens
{
  struct token
    : nodes::node
  {
    virtual char const *node_type () const { return "token"; }
    virtual nodes::node_ptr accept (nodes::visitor &v) { return v.visit (*this); }
    token (int tok, std::string const &string)
      : tok (tok)
      , string (string)
    {
    }

    int const tok;
    std::string const string;
  };

  struct identifier
    : token
  {
    virtual char const *node_type () const { return "identifier"; }
    virtual nodes::node_ptr accept (nodes::visitor &v) { return v.visit (*this); }
    identifier (std::string const &string);

    nodes::node_ptr ref;
  };

  struct yaccvar
    : token
  {
    virtual char const *node_type () const { return "yaccvar"; }
    virtual nodes::node_ptr accept (nodes::visitor &v) { return v.visit (*this); }
    yaccvar (std::string const &string);

    nodes::node_ptr ref;
  };

  template<short Tok>
  token *make_token (std::string const &string);

  template<short Tok>
  token *make_token (char const *text, int leng)
  {
    return make_token<Tok> (std::string (text, leng));
  }
}


using nodes::node;
using nodes::node_ptr;

using boost::static_pointer_cast;
