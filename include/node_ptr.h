#pragma once

#include <boost/intrusive_ptr.hpp>

namespace nodes
{
  struct node;
  typedef boost::intrusive_ptr<node> node_ptr;
}
