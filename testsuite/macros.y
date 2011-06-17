%{
%}

%start start

%%
start
	:
	;

list.0(E)
	:
	| $$ E
	;

list.1(E)
	: E
	| list.1(E,Sep) E
	;

opt(E)
	:
	| E
	;

expand(arg,rest...)
	: arg expand(rest...)
	;

named_args
	: opt(E: start)
	;

// E (sep E)*
list(E,sep,list_type)
	: E
		// You may refer to arguments of macros in action code using the ` prefix.
		{ ($$ = new `list_type)->add ($1); }
	| list(E, sep, list_type) sep E
		{ ($$ = $1)->add ($3); }
	;

argument_list: '(' list (argument, ';', node_list) ')';

macro(A): A;

// no macro call; explicit type on anonymous rule
nonterm: macro (alt1 | alt2)<node>;
// macro calls
nonterm: macro ((alt1 | alt2));
nonterm: macro (A: (alt1 | alt2));
%%
