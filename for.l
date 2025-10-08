%{
#include <stdio.h>
#include "y.tab.h"
%}

/* ---------- TOKEN PATTERNS ---------- */
%%
"for"                   { return FOR; }
"("                     { return LPAREN; }
")"                     { return RPAREN; }
"{"                     { return LBRACE; }
"}"                     { return RBRACE; }
";"                     { return SEMI; }
"="                     { return ASSIGN; }
"<"|">"|"<="|">="|"=="|"!="  { return RELOP; }
"+"|"-"|"*"|"/"          { return OP; }
[0-9]+                   { return NUM; }
[a-zA-Z_][a-zA-Z0-9_]*   { return ID; }
[ \t\n]+                 ;   // ignore whitespace
.                        { return INVALID; }
%%

int yywrap() {
    return 1;
}

