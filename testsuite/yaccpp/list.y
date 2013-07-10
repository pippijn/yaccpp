%{
%}

%start start

%%
list.1(E)
	: E
	| list.1(E) E
	;

foo: list.1(E);
%%
