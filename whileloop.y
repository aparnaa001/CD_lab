%{
#include <stdio.h>

int yylex();
void yyerror(const char *s);
%}

/* ---------- Token Declarations ---------- */
%token WHILE ID NUM ASSIGN RELOP OP LPAREN RPAREN LBRACE RBRACE SEMI INVALID

%%
stmt : WHILE LPAREN cond RPAREN LBRACE body RBRACE
        { printf("✅ Valid while loop statement.\n"); }
     | INVALID
        { printf("❌ Invalid while loop statement.\n"); }
     ;

body : stmt_list
     | /* empty */
     ;

stmt_list : stmt_list stmt_simple
          | stmt_simple
          ;

stmt_simple : ID ASSIGN expr SEMI
            ;

expr : ID
     | NUM
     | expr OP expr
     ;

cond : ID RELOP ID
     | ID RELOP NUM
     | NUM RELOP ID
     | NUM RELOP NUM
     ;
%%

void yyerror(const char *s) {
    printf("❌ Invalid while loop statement.\n");
}

int main() {
    printf("Enter a while loop statement:\n");
    yyparse();
    return 0;
}

