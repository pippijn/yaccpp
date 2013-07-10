%{
%}

%start start

%%
start
	: a* b+ c?[L] $L?
	| a+?
	;
%%
