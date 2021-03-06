#include "phase.h"

#include <boost/foreach.hpp>

namespace
{
  struct cardinality
    : visitor
  {
    node_ptr visit (nonterminal &n);
  };

  static phase<cardinality> thisphase ("cardinality");
}

static char const *
cardinality_name (char cardinality)
{
  switch (cardinality)
    {
    case '*': return "list.0";
    case '+': return "list.1";
    case '?': return "opt";
    }
  throw std::runtime_error (std::string ("impossible cardinality: ") + cardinality);
}

node_ptr
cardinality::visit (nonterminal &n)
{
  visitor::visit (n);
  node_ptr p = n.nonterm;

  BOOST_FOREACH (char cardinality, n.cardinality)
    if (cardinality)
      p = new macro_call
        ( make_token<TK_IDENTIFIER> (cardinality_name (cardinality))
        , (new macro_args)->add (p));
  return p;
}
