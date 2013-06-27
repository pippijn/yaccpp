#include "parser.h"

#include <iostream>

parser::parser (lexer &lex)
  : lex (lex)
{
}

parser::~parser ()
{
}


node_ptr
parser::operator () ()
{
  extern int yyparse (parser *parse);
  yyparse (this);
  return doc;
}


void
yyerror (YYLTYPE const *llocp, parser *parser, char const *msg)
{
  printf ("%s:%d:%d: error: \"%s\"\n",
          "llocp->file->c_str ()",
          llocp->first_line,
          llocp->first_column,
          msg);
  exit (EXIT_FAILURE);
}
