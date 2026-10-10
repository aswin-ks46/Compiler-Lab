%{
#include "y.tab.h"
%}
%%
[0-9]+ { return NUMBER; }
[_a-zA-Z][_a-zA-Z0-9]* { return ID; }
\n { return 0; }
[ \t] { /* skip whitespace */ }
. { return yytext[0]; }
%%
int yywrap() { return 1; }
