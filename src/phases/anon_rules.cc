#include "phase.h"

#include <boost/lexical_cast.hpp>

namespace
{
  struct anon_rules
    : visitor
  {
    node_ptr visit (rules &n);
    node_ptr visit (rule_rhs &n);
    node_ptr visit (rule_alt &n);
    node_ptr visit (anonymous_rule &n);

    anon_rules ();

    rules_ptr g_rules;
    rule_ptr cur_rule;
    bool in_rule_alt;
  };

  static phase<anon_rules> thisphase ("anon_rules");
}

anon_rules::anon_rules ()
  : g_rules (0)
  , in_rule_alt (false)
{
}

node_ptr
anon_rules::visit (rules &n)
{
  g_rules = &n;
  return visitor::visit (n);
}

node_ptr
anon_rules::visit (rule_rhs &n)
{
  if (in_rule_alt)
    {
      static int anon_idx = 1;
      token_ptr name = make_token<TK_IDENTIFIER> ("_anon" + boost::lexical_cast<std::string> (anon_idx++));
      cur_rule = new rule (name, 0, &n);
      return name;
    }
  return visitor::visit (n);
}

node_ptr
anon_rules::visit (rule_alt &n)
{
  local (in_rule_alt) = true;
  return visitor::visit (n);
}

node_ptr
anon_rules::visit (anonymous_rule &n)
{
  visitor::visit (n);
  cur_rule->type = n.type;
  g_rules->add (cur_rule);
  return n.rule;
}
