#pragma once

#include <string>
#include <vector>

#include <boost/intrusive_ptr.hpp>

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
    virtual void accept (visitor &v) = 0;
    node () : refcnt (0) { }
    virtual ~node () { }

    friend void intrusive_ptr_release (node *n);
    friend void intrusive_ptr_add_ref (node *n);

    void *operator new (size_t bytes);
    void operator delete (void *ptr, size_t bytes);

  private:
    int refcnt;
  };

  typedef boost::intrusive_ptr<node> node_ptr;

  struct node_list
    : node
  {
    void add (node *n) { list.push_back (n); }

    std::vector<node_ptr> list;
  };

  struct token
    : node
  {
    virtual void accept (visitor &v) { v.visit (*this); }
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


  struct documents
    : node_list
  {
    virtual void accept (visitor &v) { v.visit (*this); }
  };
  
  struct document
    : node
  {
    virtual void accept (visitor &v) { v.visit (*this); }
    document (node *prologue, node *options, node *rules, node *epilogue) : prologue (prologue), options (options), rules (rules), epilogue (epilogue) { }

    node_ptr prologue;
    node_ptr options;
    node_ptr rules;
    node_ptr epilogue;
  };

  struct options
    : node_list
  {
    virtual void accept (visitor &v) { v.visit (*this); }
  };
  
  struct directive
    : node
  {
    virtual void accept (visitor &v) { v.visit (*this); }
    directive (node *dir, node *a1 = 0, node *a2 = 0, node *a3 = 0) : dir (dir), a1 (a1), a2 (a2), a3 (a3) { }

    node_ptr dir;
    node_ptr a1;
    node_ptr a2;
    node_ptr a3;
  };
  
  struct default_rule_type
    : node
  {
    virtual void accept (visitor &v) { v.visit (*this); }
    default_rule_type (node *type) : type (type) { }

    node_ptr type;
  };
  
  struct default_token_type
    : node
  {
    virtual void accept (visitor &v) { v.visit (*this); }
    default_token_type (node *type) : type (type) { }

    node_ptr type;
  };
  
  struct include_enum
    : node
  {
    virtual void accept (visitor &v) { v.visit (*this); }
    include_enum (node *file, node *id) : file (file), id (id) { }

    node_ptr file;
    node_ptr id;
  };
  
  struct token_decl
    : node
  {
    virtual void accept (visitor &v) { v.visit (*this); }
    token_decl (node *type, node *name, node *num, node *desc) : type (type), name (name), num (num), desc (desc) { }

    node_ptr type;
    node_ptr name;
    node_ptr num;
    node_ptr desc;
  };
  
  struct rules
    : node_list
  {
    virtual void accept (visitor &v) { v.visit (*this); }
  };
  
  struct rule
    : node
  {
    virtual void accept (visitor &v) { v.visit (*this); }
    rule (node *nonterm, node *type, node *rhs) : nonterm (nonterm), type (type), rhs (rhs) { }

    node_ptr nonterm;
    node_ptr type;
    node_ptr rhs;
  };
  
  struct rule_rhs
    : node_list
  {
    virtual void accept (visitor &v) { v.visit (*this); }
  };
  
  struct rule_alt
    : node_list
  {
    virtual void accept (visitor &v) { v.visit (*this); }
  };
  
  struct macro_call
    : node
  {
    virtual void accept (visitor &v) { v.visit (*this); }
    macro_call (node *macro, node *args, node *name) : macro (macro), args (args), name (name) { }

    node_ptr macro;
    node_ptr args;
    node_ptr name;
  };
  
  struct macro_args
    : node_list
  {
    virtual void accept (visitor &v) { v.visit (*this); }
  };
  
  struct code
    : node_list
  {
    virtual void accept (visitor &v) { v.visit (*this); }
  };
}

using nodes::node;
using nodes::node_ptr;
