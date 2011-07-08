#include "phase.h"

#include <algorithm>
#include <vector>

namespace
{
  struct resolve_refs
    : visitor
  {
    node_ptr visit (identifier &n);
    node_ptr visit (yaccvar &n);

    std::vector<node_ptr> refs;
  };

  static phase<resolve_refs> thisphase ("resolve_refs");
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
