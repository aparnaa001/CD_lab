%{
#include <stdio.h>
#include "y.tab.h"
%}

/* ----------- TOKEN DEFINITIONS ----------- */
%%
"switch"                { return SWITCH; }
"case"                  { return CASE; }
"default"               { return DEFAULT; }
"break"                 { return BREAK; }
":"                     { return COLON; }
"("                     { return LPAREN; }
")"                     { return RPAREN; }
"{"                     { return LBRACE; }
"}"                     { return RBRACE; }
";"                     { return SEMI; }
"="                     { return ASSIGN; }
"+"|"-"|"*"|"/"          { return OP; }
"<"|">"|"<="|">="|"=="|"!=" { return RELOP; }
[0-9]+                  { return NUM; }
[a-zA-Z_][a-zA-Z0-9_]*  { return ID; }
[ \t\n]+                ;   // ignore whitespace
.                       { return INVALID; }
%%

int yywrap() {
    return 1;
}

