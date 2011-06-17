%{
%}

%start start

%%
start
	: (a b | c d) c
	| a (b | (c | d a))
	;
%%
