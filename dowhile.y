%{
#include <stdio.h>

int yylex();
void yyerror(const char *s);
%}

/* ---------- Tokens ---------- */
%token DO WHILE ID NUM ASSIGN RELOP OP LPAREN RPAREN LBRACE RBRACE SEMI INVALID

%%
stmt : DO LBRACE body RBRACE WHILE LPAREN cond RPAREN SEMI
        { printf("✅ Valid do-while statement.\n"); }
     | INVALID
        { printf("❌ Invalid statement.\n"); }
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
    printf("❌ Invalid do-while statement.\n");
}

int main() {
    printf("Enter a do-while loop statement:\n");
    yyparse();
    return 0;
}

