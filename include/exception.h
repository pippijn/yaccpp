#pragma once

#include "node_ptr.h"

#include <exception>
#include <vector>

struct semantic_error
  : std::exception
{
  typedef std::vector<nodes::node_ptr> node_vec;

  semantic_error (node_vec const &nodes, std::string const &message);
  semantic_error (nodes::node_ptr node, std::string const &message);

  ~semantic_error () throw ()
  {
  }

  char const *what () const throw ();

  std::string message;
};
