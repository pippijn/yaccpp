#include "exception.h"
#include "node.h"

#include <boost/foreach.hpp>
#include <sstream>

semantic_error::semantic_error (node_vec const &nodes, std::string const &message)
{
  std::ostringstream s;
  BOOST_FOREACH (node_ptr const &n, nodes)
    {
      if (&n != &nodes.back ())
        s << "from ";
      s << *n->loc.file << ":"
        << n->loc.first_line << ":"
        << n->loc.first_column;
      if (&n == &nodes.back ())
        s << ": " << message;
      else
        s << "\n";
    }
  this->message = s.str ();
}

semantic_error::semantic_error (nodes::node_ptr node, std::string const &message)
{
  std::ostringstream s;
  s << *node->loc.file << ":"
    << node->loc.first_line << ":"
    << node->loc.first_column << ": "
    << message;
  this->message = s.str ();
}

char const *
semantic_error::what () const throw ()
{
  return message.c_str ();
}
