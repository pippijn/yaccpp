%{
%}

%start start

%%
start
	: ((a | b) | b)<node> c
	| a (b | c)<node>
	;
%%
