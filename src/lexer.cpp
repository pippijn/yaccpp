#define YY_HEADER_EXPORT_START_CONDITIONS
#include "lexer.h"

#include <cassert>
#include <climits>
#include <iomanip>
#include <sstream>
#include <stdexcept>
#include <vector>

static char const *
strcond (int cond)
{
  switch (cond)
    {
    case INITIAL        : return "in initial state";
    case COMMENT        : return "in comment";
    default             : return "<unknown>";
    }
}

lexer::lexer (std::vector<std::string> const &files)
  : loc (0)
  , it (files.begin ())
  , et (files.end ())
{
  yylex_init (&lex);
  yyset_extra (this, lex);
  yyset_in (NULL, lex);

  wrap ();
}

lexer::~lexer ()
{
  close_file ();
  yylex_destroy (lex);
}

bool
lexer::close_file ()
{
  if (FILE *oldfh = yyget_in (lex))
    {
      fclose (oldfh);
      yyset_in (NULL, lex);
      return true;
    }
  return false;
}

int
lexer::next (YYSTYPE *yylval, YYLTYPE *yylloc)
{
  return yylex (yylval, yylloc, lex);
}

int
lexer::wrap ()
{
  if (cond () != INITIAL && cond () != EPILOGUE)
    {
      std::string msg = "end of file ";
      msg += strcond (cond ());
      yyerror (loc, 0, msg.c_str ());
    }

  if (close_file ())
    yyset_lineno (1, lex);

  if (it == et)
    {
#if !LEXER_TEST
      return 1;
#else
      it = it0;
#endif
    }

  FILE *fh = fopen (it->c_str (), "r");
  if (!fh)
    throw std::runtime_error ("Could not open " + *it + " for reading");
  ++it;

  yyset_in (fh, lex);
  return 0;
}

void
lexer::lloc (YYLTYPE *yylloc, int lineno, int column, int leng)
{
  assert (yylloc != NULL);
  assert (lineno >= 1);
  assert (column >= 0);
  assert (leng >= 1);
  assert (UINT_MAX - column - leng > INT_MAX);

  if (column == 0)
    column = 1;

  yylloc->file = &it[-1];
  yylloc->first_line = lineno;
  yylloc->first_column = column;
  yylloc->last_column = column + leng;
  yylloc->last_line = lineno;

  loc = yylloc;
}
