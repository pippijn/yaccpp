#include "phase.h"

#include <algorithm>
#include <vector>

namespace
{
  struct resolve_refs
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
    node_ptr visit (nonterminal &n);
    node_ptr visit (anonymous_rule &n);
    node_ptr visit (macro_call &n);
    node_ptr visit (macro_args &n);
    node_ptr visit (macro_arg &n);
    node_ptr visit (code &n);

    std::vector<node_ptr> refs;
  };

  static phase<resolve_refs> thisphase ("resolve_refs");
}

node_ptr
resolve_refs::visit (token &n)
{
  return visitor::visit (n);
}

node_ptr
resolve_refs::visit (identifier &n)
{
  if (std::find (refs.begin (), refs.end (), &n) != refs.end ())
    throw semantic_error (refs, "variable `" + n.string + "' references itself (eventually)");
  if (n.ref)
    {
      refs.push_back (&n);
      resume (ref);
      refs.pop_back ();
      return n.ref;
    }
  return visitor::visit (n);
}

node_ptr
resolve_refs::visit (yaccvar &n)
{
  if (n.ref)
    {
      resume (ref);
      return n.ref;
    }
  return visitor::visit (n);
}

node_ptr
resolve_refs::visit (documents &n)
{
  return visitor::visit (n);
}

node_ptr
resolve_refs::visit (document &n)
{
  return visitor::visit (n);
}

node_ptr
resolve_refs::visit (options &n)
{
  return visitor::visit (n);
}

node_ptr
resolve_refs::visit (directive &n)
{
  return visitor::visit (n);
}

node_ptr
resolve_refs::visit (default_rule_type &n)
{
  return visitor::visit (n);
}

node_ptr
resolve_refs::visit (default_token_type &n)
{
  return visitor::visit (n);
}

node_ptr
resolve_refs::visit (include_enum &n)
{
  return visitor::visit (n);
}

node_ptr
resolve_refs::visit (token_decl &n)
{
  return visitor::visit (n);
}

node_ptr
resolve_refs::visit (rules &n)
{
  return visitor::visit (n);
}

node_ptr
resolve_refs::visit (rule &n)
{
  return visitor::visit (n);
}

node_ptr
resolve_refs::visit (rule_rhs &n)
{
  return visitor::visit (n);
}

node_ptr
resolve_refs::visit (rule_alt &n)
{
  return visitor::visit (n);
}

node_ptr
resolve_refs::visit (nonterminal &n)
{
  return visitor::visit (n);
}

node_ptr
resolve_refs::visit (anonymous_rule &n)
{
  return visitor::visit (n);
}

node_ptr
resolve_refs::visit (macro_call &n)
{
  return visitor::visit (n);
}

node_ptr
resolve_refs::visit (macro_args &n)
{
  return visitor::visit (n);
}

node_ptr
resolve_refs::visit (macro_arg &n)
{
  return visitor::visit (n);
}

node_ptr
resolve_refs::visit (code &n)
{
  return visitor::visit (n);
}
