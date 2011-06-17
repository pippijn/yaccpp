#pragma once

#include "visitor.h"

struct printer
  : nodes::visitor
{
  void visit (nodes::token &n);
  void visit (nodes::documents &n);
  void visit (nodes::document &n);
  void visit (nodes::options &n);
  void visit (nodes::directive &n);
  void visit (nodes::default_rule_type &n);
  void visit (nodes::default_token_type &n);
  void visit (nodes::include_enum &n);
  void visit (nodes::token_decl &n);
  void visit (nodes::rules &n);
  void visit (nodes::rule &n);
  void visit (nodes::rule_rhs &n);
  void visit (nodes::rule_alt &n);
  void visit (nodes::macro_call &n);
  void visit (nodes::macro_args &n);
  void visit (nodes::code &n);
};
