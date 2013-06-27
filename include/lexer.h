#pragma once

#include "ylcode.h"

#include <vector>

struct lexer
{
  lexer (std::vector<std::string> const &files);
  ~lexer ();

  bool close_file ();

  int next (YYSTYPE *yylval, YYLTYPE *yylloc);
  int cond ();
  int wrap ();
  void lloc (YYLTYPE *yylloc, int lineno, int column, int leng);

  void append (char const *text, int leng) { tmp.append (text, leng); }
  std::string text () { std::string s = tmp; tmp.clear (); return s; }
  template<short Tok>
  short make_token (char const *text, int leng, YYSTYPE *lval, YYLTYPE *lloc);

  void *lex;
  YYLTYPE *loc;
  std::string tmp;

  std::string const base;
  std::vector<std::string>::const_iterator it;
  std::vector<std::string>::const_iterator et;
};
