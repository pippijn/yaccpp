#pragma once

namespace nodes
{
  struct visitor
  {
    virtual void visit (struct token &n) { }
    virtual void visit (struct documents &n) { }
    virtual void visit (struct document &n) { }
    virtual void visit (struct options &n) { }
    virtual void visit (struct directive &n) { }
    virtual void visit (struct default_rule_type &n) { }
    virtual void visit (struct default_token_type &n) { }
    virtual void visit (struct include_enum &n) { }
    virtual void visit (struct token_decl &n) { }
    virtual void visit (struct rules &n) { }
    virtual void visit (struct rule &n) { }
    virtual void visit (struct rule_rhs &n) { }
    virtual void visit (struct rule_alt &n) { }
    virtual void visit (struct macro_call &n) { }
    virtual void visit (struct macro_args &n) { }
    virtual void visit (struct code &n) { }
  };
}
