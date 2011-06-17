#pragma once

#include "lexer.h"
#include "node.h"

struct parser
{
  parser (lexer &lex);
  ~parser ();

  node_ptr operator () ();

  lexer &lex;
  node_ptr doc;
};
