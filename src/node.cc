#include "node.h"
#include "object_pool.h"

#if 0
#include <cstdio>
#endif

#include <valgrind/valgrind.h>

namespace nodes
{
  void intrusive_ptr_release (node *n) { if (!--n->refcnt) delete n; }
  void intrusive_ptr_add_ref (node *n) { ++n->refcnt; }

  static object_pool<88> mempool;

  void *
  node::operator new (size_t bytes)
  {
    if (RUNNING_ON_VALGRIND)
      return ::operator new (bytes);
    return mempool.alloc (bytes);
  }

  void
  node::operator delete (void *ptr, size_t bytes)
  {
    if (RUNNING_ON_VALGRIND)
      return ::operator delete (ptr);
    return mempool.free (ptr, bytes);
  }


  std::vector<node *> node::nodes;

  node::node ()
    : refcnt (0)
  {
    index = nodes.size ();
    nodes.push_back (this);
  }

  node::~node ()
  {
    if (this == nodes.back ())
      nodes.pop_back ();
    else
      nodes[index] = 0;
  }

  void
  node::compress_hash ()
  {
    std::vector<node *>::reverse_iterator it = nodes.rbegin ();
    std::vector<node *>::reverse_iterator et = nodes.rend ();

    while (it != et)
      {
        if (!*it)
          {
            *it = nodes.back ();
            int index = et - it - 1;
#if 0
            printf ("rewriting %d's index to %d\n", (*it)->index, index);
#endif
            (*it)->index = index;
            nodes.pop_back ();
            ++it;
          }
        ++it;
      }
  }

  bool
  node::audit_hash ()
  {
    std::vector<node *>::reverse_iterator it = nodes.rbegin ();
    std::vector<node *>::reverse_iterator et = nodes.rend ();

    while (it != et)
      {
        if (*it && (*it)->index != et - it - 1)
          return false;
        ++it;
      }
    return true;
  }
}
