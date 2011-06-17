%{
#include "parser.h"
#define YYSTYPE YYSTYPE

union YYSTYPE;
struct YYLTYPE;
static int
yylex (YYSTYPE *yylval, YYLTYPE *yylloc, parser *self)
{
  return self->lex.next (yylval, yylloc);
}

using namespace nodes;
%}

%union {
  nodes::node *node;
  nodes::token *token;
  nodes::node_list *list;
}

%define api.pure
%locations
%debug
%error-verbose
%token-table
%glr-parser

%parse-param { parser *self }
%lex-param { parser *self }

%token TK_EOF 0				"end of file"

%token<token> DIR_TOKEN			"%token"
%token<token> DIR_INCLUDE_ENUM		"%include-enum"
%token<token> DIR_EXPECT		"%expect"
%token<token> DIR_EXPECT_RR		"%expect-rr"
%token<token> DIR_DEFAULT_RULE_TYPE	"%default-rule-type"
%token<token> DIR_DEFAULT_TOKEN_TYPE	"%default-token-type"
%token<token> DIR_TYPE			"%type"

%token<token> TK_CDECL			"C declarations"
%token<token> TK_SEPARATOR		"%%"
%token<token> TK_YACCVAR		"variable"
%token<token> TK_DIRECTIVE		"directive"
%token<token> TK_TYPE			"type"
%token<token> TK_IDENTIFIER		"identifier"
%token<token> TK_INTEGER		"integer"
%token<token> TK_KEYWORD		"keyword"
%token<token> TK_STRING			"string literal"
%token<token> TK_CHARACTER		"character literal"

%type<token> type.opt
%type<token> integer.opt
%type<token> string.opt

%type<list> documents
%type<list> options
%type<node> document
%type<node> option
%type<token> expect
%type<list> rules
%type<node> rule
%type<list> rule_rhs
%type<list> rule_alt
%type<node> rule_alt_part
%type<node> nonterminal
%type<node> macro_call
%type<token> name_opt
%type<token> name
%type<list> macro_args_opt
%type<list> macro_args
%type<token> macro_name
%type<token> macro_arg
%type<list> code
%type<token> code_part

%destructor { delete $$; } <*>

%%
/****************************************************************************
 *
 *	Toplevel declarations
 *
 ****************************************************************************/
start
	: documents							{ self->doc = $1; }
	;

documents
	: document							{ ($$ = new documents)->add ($1); }
	| documents document						{ ($$ = $1)->add ($2); }
	;

document
	: TK_CDECL options "%%" rules "%%" TK_CDECL			{ $$ = new document ($1, $2, $4, $6); delete $3; delete $5; }
	;

options
	: /* empty */							{ $$ = new options; }
	| options option						{ ($$ = $1)->add ($2); }
	;

option
	: TK_DIRECTIVE							{ $$ = new directive ($1); }
	| TK_DIRECTIVE TK_IDENTIFIER					{ $$ = new directive ($1, $2); }
	| TK_DIRECTIVE TK_CDECL						{ $$ = new directive ($1, $2); }
	| TK_DIRECTIVE TK_CDECL TK_TYPE					{ $$ = new directive ($1, $2, $3); }
	| expect TK_INTEGER						{ $$ = new directive ($1, $2); }
	| "%default-rule-type" TK_TYPE					{ $$ = new default_rule_type ($2); delete $1; }
	| "%default-token-type" TK_TYPE					{ $$ = new default_token_type ($2); delete $1; }
	| "%include-enum" TK_STRING TK_IDENTIFIER			{ $$ = new include_enum ($2, $3); delete $1; }
	| "%token" type.opt TK_IDENTIFIER integer.opt string.opt	{ $$ = new token_decl ($2, $3, $4, $5); delete $1; }
	;

expect
	: "%expect"
	| "%expect-rr"
	;

type.opt
	: /* empty */							{ $$ = NULL; }
	| TK_TYPE
	;

integer.opt
	: /* empty */							{ $$ = NULL; }
	| TK_INTEGER
	;

string.opt
	: /* empty */							{ $$ = NULL; }
	| TK_STRING
	;

rules
	: rule								{ ($$ = new rules)->add ($1); }
	| rules rule							{ ($$ = $1)->add ($2); }
	;

rule
	: macro_call type.opt ':' rule_rhs ';'				{ $$ = new rule ($1, $2, $4); }
	;

rule_rhs
	: rule_alt							{ ($$ = new rule_rhs)->add ($1); }
	| rule_rhs '|' rule_alt						{ ($$ = $1)->add ($3); }
	;

rule_alt
	:								{ $$ = new rule_alt; }
	| rule_alt rule_alt_part					{ ($$ = $1)->add ($2); }
	;

rule_alt_part
	: nonterminal
	| '{' code '}'							{ $$ = $2; }
	;

nonterminal
	: macro_call
	| TK_CHARACTER							{ $$ = $1; }
	;

macro_call
	: macro_name macro_args_opt name_opt				{ $$ = new macro_call ($1, $2, $3); }
	;

macro_name
	: TK_IDENTIFIER
	| TK_STRING
	;

name_opt
	: /* empty */							{ $$ = NULL; }
	| name
	;

name
	: '[' TK_IDENTIFIER ']'						{ $$ = $2; }
	;

macro_args_opt
	: /* empty */							{ $$ = NULL; }
	| '(' macro_args ')'						{ $$ = $2; }
	;

macro_args
	: macro_arg							{ ($$ = new macro_args)->add ($1); }
	| macro_args ',' macro_arg					{ ($$ = $1)->add ($3); }
	;

macro_arg
	: TK_IDENTIFIER
	;

code
	: code_part							{ ($$ = new code)->add ($1); }
	| code code_part						{ ($$ = $1)->add ($2); }
	;

code_part
	: TK_YACCVAR
	| TK_CDECL
	;
%%

char const *
yytokname (yySymbol yytoken)
{
  return yytokenName (yytoken);
}
