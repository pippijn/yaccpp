#pragma once

#include <boost/intrusive_ptr.hpp>

#define NODE(T) struct T; typedef boost::intrusive_ptr<T> T##_ptr

namespace nodes
{
  NODE (node);
  void intrusive_ptr_release (node *n);
  void intrusive_ptr_add_ref (node *n);

  struct node_hash
  {
    size_t operator () (node_ptr n) const;
  };

  struct node_eq
  {
    bool operator () (node_ptr n1, node_ptr n2) const;
  };

  NODE (node_list);
  NODE (documents);
  NODE (document);
  NODE (options);
  NODE (directive);
  NODE (default_rule_type);
  NODE (default_token_type);
  NODE (include_enum);
  NODE (token_decl);
  NODE (rules);
  NODE (rule);
  NODE (rule_rhs);
  NODE (rule_alt);
  NODE (rule_alt_part);
  NODE (nonterminal);
  NODE (anonymous_rule);
  NODE (macro_call);
  NODE (macro_args);
  NODE (macro_arg);
  NODE (code);
}

namespace tokens
{
  NODE (token);
  NODE (identifier);
  NODE (yaccvar);

  template<short Tok>
  token *make_token (char const *text, int leng);
}

template<typename T>
boost::intrusive_ptr<T>
move (boost::intrusive_ptr<T> &p)
{
  boost::intrusive_ptr<T> r;
  swap (r, p);
  return r;
}
