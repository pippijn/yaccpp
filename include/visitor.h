#pragma once

#include "node_ptr.h"

namespace nodes
{
  struct visitor
  {
    virtual node_ptr visit (struct token &n);
    virtual node_ptr visit (struct documents &n);
    virtual node_ptr visit (struct document &n);
    virtual node_ptr visit (struct options &n);
    virtual node_ptr visit (struct directive &n);
    virtual node_ptr visit (struct default_rule_type &n);
    virtual node_ptr visit (struct default_token_type &n);
    virtual node_ptr visit (struct include_enum &n);
    virtual node_ptr visit (struct token_decl &n);
    virtual node_ptr visit (struct rules &n);
    virtual node_ptr visit (struct rule &n);
    virtual node_ptr visit (struct rule_rhs &n);
    virtual node_ptr visit (struct rule_alt &n);
    virtual node_ptr visit (struct nonterminal &n);
    virtual node_ptr visit (struct anonymous_rule &n);
    virtual node_ptr visit (struct macro_call &n);
    virtual node_ptr visit (struct macro_args &n);
    virtual node_ptr visit (struct macro_arg &n);
    virtual node_ptr visit (struct code &n);
  };
}
