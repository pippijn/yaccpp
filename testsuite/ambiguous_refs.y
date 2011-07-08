%{
%}

%start start

%%
start
	: first second first
		{ $first $second $first; }
	;
%%
