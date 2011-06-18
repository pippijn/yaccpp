%{
%}

%start start

%%
start(E: opt(E))
	: a* b+ c?[L] $L
	| a+?
	;
%%
