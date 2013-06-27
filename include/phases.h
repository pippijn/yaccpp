#pragma once

#include "node.h"

struct phases
{
  phases (std::string const &name);

  static void run (std::string const &name, node_ptr doc);

  virtual void run (node_ptr doc) = 0;
};

template<typename Visitor>
struct phase
  : phases
{
  phase (std::string const &name)
    : phases (name)
  {
  }

  void run (node_ptr doc)
  {
    Visitor v;
    doc->accept (v);
  }
};
