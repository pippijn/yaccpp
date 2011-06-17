#include "node.h"
#include "object_pool.h"

namespace nodes
{
  void intrusive_ptr_release (node *n) { if (!--n->refcnt) delete n; }
  void intrusive_ptr_add_ref (node *n) { ++n->refcnt; }

  static object_pool<48> mempool;

  void *
  node::operator new (size_t bytes)
  {
    return mempool.alloc (bytes);
  }

  void
  node::operator delete (void *ptr, size_t bytes)
  {
    return mempool.free (ptr, bytes);
  }
}
