%{
#include <stdio.h>
int yylex();
void yyerror(const char *s);
%}


%token FOR ID NUM ASSIGN RELOP OP LPAREN RPAREN LBRACE RBRACE SEMI INVALID

%%


stmt : FOR LPAREN init SEMI cond SEMI incr RPAREN LBRACE body RBRACE
        { printf("✅ Valid for loop statement.\n"); }
     | INVALID
        { printf("❌ Invalid for loop statement.\n"); }
     ;


init : ID ASSIGN expr
     ;

cond : ID RELOP expr
     | /* empty */   // allow missing condition
     ;


incr : ID ASSIGN expr
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
%%

void yyerror(const char *s) {
    printf("❌ Invalid for loop statement.\n");
}

int main() {
    printf("Enter a for loop statement:\n");
    yyparse();
    return 0;
}

