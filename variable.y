%{
#include <stdio.h>


int yylex();
int yyerror(const char *msg);
%}

%token VARIABLE INVALID

%%

input:
    VARIABLE    { printf("Valid variable name\n"); }
  | INVALID     { printf("Invalid variable name\n"); }
  ;

%%

int main() {
    printf("Enter a variable name: ");
    yyparse();
    return 0;
}

int yyerror(const char *msg) {
   
    return 0;
}

