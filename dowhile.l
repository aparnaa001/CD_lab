%{
#include <stdio.h>
#include "y.tab.h"
%}

/* ---------- Token Definitions ---------- */
%%
"do"                    { return DO; }
"while"                 { return WHILE; }
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
[ \t\n]+                 ;   // ignore spaces and newlines
.                        { return INVALID; } // invalid character
%%

int yywrap() {
    return 1;
}

