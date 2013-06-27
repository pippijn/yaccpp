%{
%}

%start start

%%
start
	: (a | b)[L] c $L
	| $2 $3 c $1 { $$ = $1; }
	;
%%
