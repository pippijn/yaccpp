#pragma once

#include <cstddef>
#include <string>
#include "node.h"
#include "yyparse.h"
#ifndef FLEX_SCANNER
#include "yylex.h"
#endif

struct parser;

void yyerror (YYLTYPE const *llocp, parser *parse, char const *msg);
char const *yytokname (short yytoken);
