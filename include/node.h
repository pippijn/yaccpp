#pragma once

#include <string>
#include <list>

#include "visitor.h"

struct YYLTYPE
{
  std::string const *file;
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
#define YYLTYPE_IS_DECLARED 1
#define YYLTYPE_IS_TRIVIAL 1

namespace nodes
{
  struct node
  {
    virtual node_ptr accept (visitor &v) = 0;
    node () : refcnt (0) { }
    virtual ~node () { }

    friend void intrusive_ptr_release (node *n);
    friend void intrusive_ptr_add_ref (node *n);

    void *operator new (size_t bytes);
    void operator delete (void *ptr, size_t bytes);

  private:
    int refcnt;
  };

  typedef boost::intrusive_ptr<struct node_list> node_list_ptr;
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

  typedef boost::intrusive_ptr<struct token> token_ptr;
  struct token
    : node
  {
    virtual node_ptr accept (visitor &v) { return v.visit (*this); }
    token (int tok, char const *text, int leng)
      : tok (tok)
      , string (text, leng)
    {
    }
    token (int tok, std::string const &string)
      : tok (tok)
      , string (string)
    {
    }

    int const tok;
    std::string const string;
  };


  typedef boost::intrusive_ptr<struct documents> documents_ptr;
  struct documents
    : node_list_t<documents>
  {
    virtual node_ptr accept (visitor &v) { return v.visit (*this); }
  };
  
  typedef boost::intrusive_ptr<struct document> document_ptr;
  struct document
    : node
  {
    virtual node_ptr accept (visitor &v) { return v.visit (*this); }
    document (node_ptr prologue, node_ptr options, node_ptr rules, node_ptr epilogue) : prologue (prologue), options (options), rules (rules), epilogue (epilogue) { }

    node_ptr prologue;
    node_ptr options;
    node_ptr rules;
    node_ptr epilogue;
  };

  typedef boost::intrusive_ptr<struct options> options_ptr;
  struct options
    : node_list_t<options>
  {
    virtual node_ptr accept (visitor &v) { return v.visit (*this); }
  };
  
  typedef boost::intrusive_ptr<struct directive> directive_ptr;
  struct directive
    : node
  {
    virtual node_ptr accept (visitor &v) { return v.visit (*this); }
    directive (node_ptr dir, node_ptr a1 = 0, node_ptr a2 = 0, node_ptr a3 = 0) : dir (dir), a1 (a1), a2 (a2), a3 (a3) { }

    node_ptr dir;
    node_ptr a1;
    node_ptr a2;
    node_ptr a3;
  };
  
  typedef boost::intrusive_ptr<struct default_rule_type> default_rule_type_ptr;
  struct default_rule_type
    : node
  {
    virtual node_ptr accept (visitor &v) { return v.visit (*this); }
    default_rule_type (node_ptr type) : type (type) { }

    node_ptr type;
  };
  
  typedef boost::intrusive_ptr<struct default_token_type> default_token_type_ptr;
  struct default_token_type
    : node
  {
    virtual node_ptr accept (visitor &v) { return v.visit (*this); }
    default_token_type (node_ptr type) : type (type) { }

    node_ptr type;
  };
  
  typedef boost::intrusive_ptr<struct include_enum> include_enum_ptr;
  struct include_enum
    : node
  {
    virtual node_ptr accept (visitor &v) { return v.visit (*this); }
    include_enum (node_ptr file, node_ptr id) : file (file), id (id) { }

    node_ptr file;
    node_ptr id;
  };
  
  typedef boost::intrusive_ptr<struct token_decl> token_decl_ptr;
  struct token_decl
    : node
  {
    virtual node_ptr accept (visitor &v) { return v.visit (*this); }
    token_decl (node_ptr type, node_ptr name, node_ptr num, node_ptr desc) : type (type), name (name), num (num), desc (desc) { }

    node_ptr type;
    node_ptr name;
    node_ptr num;
    node_ptr desc;
  };
  
  typedef boost::intrusive_ptr<struct rules> rules_ptr;
  struct rules
    : node_list_t<rules>
  {
    virtual node_ptr accept (visitor &v) { return v.visit (*this); }
  };
  
  typedef boost::intrusive_ptr<struct rule> rule_ptr;
  struct rule
    : node
  {
    virtual node_ptr accept (visitor &v) { return v.visit (*this); }
    rule (node_ptr nonterm, node_ptr type, node_ptr rhs) : nonterm (nonterm), type (type), rhs (rhs) { }

    node_ptr nonterm;
    node_ptr type;
    node_ptr rhs;
  };
  
  typedef boost::intrusive_ptr<struct rule_rhs> rule_rhs_ptr;
  struct rule_rhs
    : node_list_t<rule_rhs>
  {
    virtual node_ptr accept (visitor &v) { return v.visit (*this); }
  };
  
  typedef boost::intrusive_ptr<struct rule_alt> rule_alt_ptr;
  struct rule_alt
    : node_list_t<rule_alt>
  {
    virtual node_ptr accept (visitor &v) { return v.visit (*this); }
  };
  
  typedef boost::intrusive_ptr<struct nonterminal> nonterminal_ptr;
  struct nonterminal
    : node
  {
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
  
  typedef boost::intrusive_ptr<struct nonterminal> anonymous_rule_ptr;
  struct anonymous_rule
    : node
  {
    virtual node_ptr accept (visitor &v) { return v.visit (*this); }
    anonymous_rule (node_ptr rule, node_ptr type) : rule (rule), type (type) { }

    node_ptr rule;
    node_ptr type;
  };
  
  typedef boost::intrusive_ptr<struct macro_call> macro_call_ptr;
  struct macro_call
    : node
  {
    virtual node_ptr accept (visitor &v) { return v.visit (*this); }
    macro_call (node_ptr macro, node_ptr args, node_ptr name) : macro (macro), args (args), name (name) { }

    node_ptr macro;
    node_ptr args;
    node_ptr name;
  };
  
  typedef boost::intrusive_ptr<struct macro_args> macro_args_ptr;
  struct macro_args
    : node_list_t<macro_args>
  {
    virtual node_ptr accept (visitor &v) { return v.visit (*this); }
    macro_args () : is_variadic (false) { }

    bool is_variadic;
  };
  
  typedef boost::intrusive_ptr<struct macro_arg> macro_arg_ptr;
  struct macro_arg
    : node
  {
    virtual node_ptr accept (visitor &v) { return v.visit (*this); }
    macro_arg (node_ptr name, node_ptr arg) : name (name), arg (arg) { }

    node_ptr name;
    node_ptr arg;
  };
  
  typedef boost::intrusive_ptr<struct code> code_ptr;
  struct code
    : node_list_t<code>
  {
    virtual node_ptr accept (visitor &v) { return v.visit (*this); }
  };
}

using nodes::node;
using nodes::node_ptr;

using boost::static_pointer_cast;
