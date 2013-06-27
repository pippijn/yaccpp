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
  char character;
  nodes::node *node;
  tokens::token *token;
  nodes::node_list *list;
  nodes::macro_args *macro_args;
}

%define api.pure
%locations
%debug
%error-verbose
%token-table
%glr-parser

%expect 3

%parse-param	{ parser *self }
%lex-param	{ parser *self }

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
%token<token> TK_ELLIPSIS		"..."
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
%type<token> ellipsis.opt

%type<list> documents
%type<list> options
%type<node> document
%type<node> option
%type<token> expect
%type<list> rules
%type<node> rule
%type<list> rule_rhs
%type<list> rule_rhs.2
%type<list> rule_alt
%type<node> rule_alt_part
%type<node> named_rule_alt_part
%type<node> nonterminal
%type<character> cardinality
%type<node> macro_call
%type<token> name
%type<macro_args> macro_args.opt macro_args
%type<token> macro_name
%type<node> macro_arg
%type<token> named_arg.opt named_arg
%type<list> code
%type<token> code_part

%destructor { delete $$; } <*>
%destructor { } <character>

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
	: document							{ ($$ = new documents)->add ($1)->loc = @$; }
	| documents document						{ ($$ = $1)->add ($2); }
	;

document
	: TK_CDECL options "%%" rules "%%" TK_CDECL			{ ($$ = new document ($1, $2, $4, $6))->loc = @$; delete $3; delete $5; }
	;

options
	: /* empty */							{ ($$ = new options)->loc = @$; }
	| options option						{ ($$ = $1)->add ($2); }
	;

option
	: TK_DIRECTIVE							{ ($$ = new directive ($1))->loc = @$; }
	| TK_DIRECTIVE TK_IDENTIFIER					{ ($$ = new directive ($1, $2))->loc = @$; }
	| TK_DIRECTIVE TK_CDECL						{ ($$ = new directive ($1, $2))->loc = @$; }
	| TK_DIRECTIVE TK_CDECL TK_TYPE					{ ($$ = new directive ($1, $2, $3))->loc = @$; }
	| expect TK_INTEGER						{ ($$ = new directive ($1, $2))->loc = @$; }
	| "%default-rule-type" TK_TYPE					{ ($$ = new default_rule_type ($2))->loc = @$; delete $1; }
	| "%default-token-type" TK_TYPE					{ ($$ = new default_token_type ($2))->loc = @$; delete $1; }
	| "%include-enum" TK_STRING TK_IDENTIFIER			{ ($$ = new include_enum ($2, $3))->loc = @$; delete $1; }
	| "%token" type.opt TK_IDENTIFIER integer.opt string.opt	{ ($$ = new token_decl ($2, $3, $4, $5))->loc = @$; delete $1; }
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
	: rule								{ ($$ = new rules)->add ($1)->loc = @$; }
	| rules rule							{ ($$ = $1)->add ($2); }
	;

rule
	: macro_call type.opt ':' rule_rhs ';'				{ ($$ = new rule ($1, $2, $4))->loc = @$; }
	;

rule_rhs
	: rule_alt							{ ($$ = new rule_rhs)->add ($1)->loc = @$; }
	| rule_rhs.2
	;

/* at least two alternatives */
rule_rhs.2
	: rule_rhs '|' rule_alt						{ ($$ = $1)->add ($3); }
	;

rule_alt
	:								{ ($$ = new rule_alt)->loc = @$; }
	| rule_alt named_rule_alt_part					{ ($$ = $1)->add ($2); }
	;

named_rule_alt_part
	: rule_alt_part							{ ($$ = new rule_alt_part ($1,  0))->loc = @$; }
	| rule_alt_part name						{ ($$ = new rule_alt_part ($1, $2))->loc = @$; }
	;

name
	: '[' TK_IDENTIFIER ']'						{ $$ = $2; }
	;


rule_alt_part
	: nonterminal							{ $$ = $1; }
	| nonterminal cardinality					{ ($$ = new nonterminal ($1, $2,  0,  0))->loc = @$; }
	| nonterminal cardinality cardinality				{ ($$ = new nonterminal ($1, $2, $3,  0))->loc = @$; }
	| nonterminal cardinality cardinality cardinality		{ ($$ = new nonterminal ($1, $2, $3, $4))->loc = @$; }
	| '{' code '}'							{ $$ = $2; }
	;

cardinality
	: '*'								{ $$ = '*'; }
	| '?'								{ $$ = '?'; }
	| '+'								{ $$ = '+'; }
	;

nonterminal
	: macro_call							{ $$ = $1; }
	| TK_CHARACTER							{ $$ = $1; }
	| '(' rule_rhs.2 ')' type.opt					{ ($$ = new anonymous_rule ($2, $4))->loc = @$; }
	;

macro_call
	: macro_name macro_args.opt					{ ($$ = new macro_call ($1, $2))->loc = @$; }
	;

macro_name
	: TK_IDENTIFIER
	| TK_STRING
	;

macro_args.opt
	: /* empty */							{ $$ = NULL; }
	| '(' macro_args ellipsis.opt ')'				{ $$ = $2; $$->is_variadic = $3; delete $3; }
	;

ellipsis.opt
	: /* empty */							{ $$ = NULL; }
	| "..."
	;

macro_args
	: macro_arg							{ ($$ = new macro_args)->add ($1)->loc = @$; }
	| macro_args ',' macro_arg					{ ($$ = $1)->add ($3); }
	;

macro_arg
	: named_arg.opt nonterminal					{ ($$ = new macro_arg ($1, $2))->loc = @$; }
	;

named_arg.opt
	: /* empty */							{ $$ = NULL; }
	| named_arg
	;

named_arg
	: TK_IDENTIFIER ':'
	;

code
	: code_part							{ ($$ = new code)->add ($1)->loc = @$; }
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
