#pragma once

#include "node_ptr.h"

namespace nodes
{
  struct visitor
  {
    virtual node_ptr visit (tokens::token &n);
    virtual node_ptr visit (tokens::identifier &n);
    virtual node_ptr visit (tokens::yaccvar &n);

    virtual node_ptr visit (documents &n);
    virtual node_ptr visit (document &n);
    virtual node_ptr visit (options &n);
    virtual node_ptr visit (directive &n);
    virtual node_ptr visit (default_rule_type &n);
    virtual node_ptr visit (default_token_type &n);
    virtual node_ptr visit (include_enum &n);
    virtual node_ptr visit (token_decl &n);
    virtual node_ptr visit (rules &n);
    virtual node_ptr visit (rule &n);
    virtual node_ptr visit (rule_rhs &n);
    virtual node_ptr visit (rule_alt &n);
    virtual node_ptr visit (rule_alt_part &n);
    virtual node_ptr visit (nonterminal &n);
    virtual node_ptr visit (anonymous_rule &n);
    virtual node_ptr visit (macro_call &n);
    virtual node_ptr visit (macro_args &n);
    virtual node_ptr visit (macro_arg &n);
    virtual node_ptr visit (code &n);
  };
}
