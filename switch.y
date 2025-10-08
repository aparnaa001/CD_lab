%{
#include <stdio.h>
int yylex();
void yyerror(const char *s);
%}

/* ----------- TOKEN DECLARATIONS ----------- */
%token SWITCH CASE DEFAULT BREAK COLON LPAREN RPAREN LBRACE RBRACE SEMI ASSIGN OP ID NUM INVALID

%%
/* ----------- GRAMMAR RULES ----------- */

stmt : SWITCH LPAREN ID RPAREN LBRACE case_list default_opt RBRACE
        { printf("✅ Valid switch statement.\n"); }
     | INVALID
        { printf("❌ Invalid switch statement.\n"); }
     ;

case_list : case_list case_block
          | case_block
          ;

case_block : CASE NUM COLON stmt_list BREAK SEMI
           ;

default_opt : DEFAULT COLON stmt_list
            | /* empty */
            ;

stmt_list : stmt_list stmt_simple
          | stmt_simple
          | /* empty */
          ;

stmt_simple : ID ASSIGN expr SEMI
            ;

expr : ID
     | NUM
     | expr OP expr
     ;
%%

void yyerror(const char *s) {
    printf("❌ Invalid switch statement.\n");
}

int main() {
    printf("Enter a switch statement:\n");
    yyparse();
    return 0;
}

