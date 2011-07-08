%{
#include "lexer.h"

#define SELF static_cast<lexer *> (yyget_extra (yyscanner))

#define APPEND() SELF->append (yytext, yyleng)

#define YY_USER_ACTION					\
  {							\
    SELF->lloc (yylloc, yylineno, yycolumn, yyleng);	\
    if (*yytext == '\n')				\
      yycolumn = 1;					\
    else						\
      yycolumn += yyleng;				\
  }

#define Return(TOK)					\
  return SELF->make_token<TOK> (yytext, yyleng, yylval, yylloc)

#define PUSH(STATE)	yy_push_state (STATE, yyscanner)
#define POP()		yy_pop_state (yyscanner)

%}

%option prefix="yy"
%option header-file="yylex.h"
%option bison-locations
%option reentrant
/*%option ecs full 8bit*/
%option yylineno stack
%option nounput noinput nounistd
%option never-interactive

%x COMMENT INIT_CODE CDECL CODE TYPE RULES EPILOGUE

WS	[ \t\v\n\r]
CID	[a-zA-Z_][a-zA-Z0-9_]*
YID	[a-zA-Z`_$.-](\.?[a-zA-Z0-9_$-])*
YVARID	[a-zA-Z0-9$_]
YVAR	[$@`]("["({YVARID}|-)+"]"|{YVARID}+)
CODE	[^a-zA-Z`$@_{}"']
DIGIT	[0-9]

%%
<INITIAL,RULES>{
	{WS}+				{ }
	"//".*				{ }
	"/*"				{ PUSH (COMMENT); }
}
<COMMENT>{
	[^*]+				{ }
	"*"				{ }
	"*/"				{ POP (); }
}

^"%{"					{ PUSH (INIT_CODE); }
<INIT_CODE>{
	[^%]+				{ APPEND (); }
	"%"				{ APPEND (); }
	^"%}"				{ POP (); Return (TK_CDECL); }
}

"%code"					{ Return (TK_DIRECTIVE); }
"%debug"				{ Return (TK_DIRECTIVE); }
"%default-rule-type"			{ Return (DIR_DEFAULT_RULE_TYPE); }
"%default-token-type"			{ Return (DIR_DEFAULT_TOKEN_TYPE); }
"%define"				{ Return (TK_DIRECTIVE); }
"%defines"				{ Return (TK_DIRECTIVE); }
"%destructor"				{ Return (TK_DIRECTIVE); }
"%dprec"				{ Return (TK_DIRECTIVE); }
"%error-verbose"			{ Return (TK_DIRECTIVE); }
"%expect"				{ Return (DIR_EXPECT); }
"%expect-rr"				{ Return (DIR_EXPECT_RR); }
"%file-prefix"				{ Return (TK_DIRECTIVE); }
"%glr-parser"				{ Return (TK_DIRECTIVE); }
"%include-enum"				{ Return (DIR_INCLUDE_ENUM); }
"%initial-action"			{ Return (TK_DIRECTIVE); }
"%language"				{ Return (TK_DIRECTIVE); }
"%left"					{ Return (TK_DIRECTIVE); }
"%lex-param"				{ Return (TK_DIRECTIVE); }
"%locations"				{ Return (TK_DIRECTIVE); }
"%merge"				{ Return (TK_DIRECTIVE); }
"%name-prefix"				{ Return (TK_DIRECTIVE); }
"%no-lines"				{ Return (TK_DIRECTIVE); }
"%nonassoc"				{ Return (TK_DIRECTIVE); }
"%output"				{ Return (TK_DIRECTIVE); }
"%parse-param"				{ Return (TK_DIRECTIVE); }
"%prec"					{ Return (TK_DIRECTIVE); }
"%printer"				{ Return (TK_DIRECTIVE); }
"%require"				{ Return (TK_DIRECTIVE); }
"%right"				{ Return (TK_DIRECTIVE); }
"%skeleton"				{ Return (TK_DIRECTIVE); }
"%start"				{ Return (TK_DIRECTIVE); }
"%token"				{ Return (DIR_TOKEN); }
"%token-table"				{ Return (TK_DIRECTIVE); }
"%type"					{ Return (DIR_TYPE); }
"%union"				{ Return (TK_DIRECTIVE); }
"%"{YID}				{ yyerror (yylloc, 0, yytext); }

"{"					{ APPEND (); PUSH (CDECL); }
<CDECL>{
	[^{}]+				{ APPEND (); }
	"{"				{ APPEND (); PUSH (CDECL); }
	"}"				{ APPEND (); POP (); if (YY_START != CDECL) Return (TK_CDECL); }
}

<INITIAL,RULES>{
	"<"				{ PUSH (TYPE); }
}
<TYPE>{
	[^<>]+				{ APPEND (); }
	"<"				{ PUSH (TYPE); }
	">"				{ POP (); if (YY_START != TYPE) Return (TK_TYPE); }
}

^"%%"					{ PUSH (RULES); Return (TK_SEPARATOR); }
<RULES>{
	{YID}				{ Return (TK_IDENTIFIER); }
	"..."				{ Return (TK_ELLIPSIS); }
	[?*+\[\],:|;()]			{ return yytext[0]; }
	"%%"				{ POP (); BEGIN (EPILOGUE); Return (TK_SEPARATOR); }
	"{"				{ PUSH (CODE); return yytext[0]; }
}
<CODE>{
	{YVAR}				{ Return (TK_YACCVAR); }
	{CID}				{ Return (TK_CDECL); }
	"{"				{ PUSH (CODE); Return (TK_CDECL); }
	"}"				{ POP (); if (YY_START == RULES) return yytext[0]; Return (TK_CDECL); }
	{CODE}+				{ Return (TK_CDECL); }
}

<*>\"(\\.|[^\\"])*\"			{ Return (TK_STRING); }
<*>\'(\\.|[^\\'])*\'			{ Return (TK_CHARACTER); }
{YID}					{ Return (TK_IDENTIFIER); }
{DIGIT}					{ Return (TK_INTEGER); }

<EPILOGUE>{
	(.|\n)+				{ Return (TK_CDECL); }
}

<*>.					{ yyerror (yylloc, 0, yytext); }
%%

int
yywrap (yyscan_t yyscanner)
{
  yyguts_t *yyg = (yyguts_t *)yyscanner;
  BEGIN (INITIAL);
  return SELF->wrap ();
}

int
lexer::cond ()
{
  yyguts_t *yyg = (yyguts_t *)lex;
  return YY_START;
}

template<short Tok>
inline short
lexer::make_token (char const *text, int leng, YYSTYPE *lval, YYLTYPE *lloc)
{
  if (!tmp.empty ())
    (lval->token
       = tokens::make_token<Tok> (this->text ()))
       ->loc = *lloc;
  else
    (lval->token
       = tokens::make_token<Tok> (text, leng))
       ->loc = *lloc;
  return Tok;
}
