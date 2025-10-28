#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 100

int tempVarCount = 1;

// Function to generate a new temporary variable
char* newTemp(char* temp) {
    sprintf(temp, "t%d", tempVarCount++);
    return temp;
}

// Function to check operator precedence
int precedence(char op) {
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

int main() {
    char expr[MAX], lhs, rhs[MAX];
    char stackOp[MAX];
    char stackVal[MAX][MAX];
    int topOp = -1, topVal = -1;
    
    printf("Enter expression : ");
    fgets(expr, MAX, stdin);
    expr[strcspn(expr, "\n")] = 0; // remove newline

    // Separate LHS and RHS
    sscanf(expr, "%c = %[^\n]", &lhs, rhs);

    // Shunting-yard like parsing (to handle operator precedence)
    for (int i = 0; i < strlen(rhs); i++) {
        if (isspace(rhs[i])) continue;

        if (isalnum(rhs[i])) {
            char operand[2] = { rhs[i], '\0' };
            strcpy(stackVal[++topVal], operand);
        } else if (strchr("+-*/", rhs[i])) {
            while (topOp >= 0 && precedence(stackOp[topOp]) >= precedence(rhs[i])) {
                char op = stackOp[topOp--];
                char right[MAX], left[MAX], temp[MAX];
                strcpy(right, stackVal[topVal--]);
                strcpy(left, stackVal[topVal--]);
                printf("%s = %s %c %s\n", newTemp(temp), left, op, right);
                strcpy(stackVal[++topVal], temp);
            }
            stackOp[++topOp] = rhs[i];
        }
    }

    // Process remaining operators
    while (topOp >= 0) {
        char op = stackOp[topOp--];
        char right[MAX], left[MAX], temp[MAX];
        strcpy(right, stackVal[topVal--]);
        strcpy(left, stackVal[topVal--]);
        printf("%s = %s %c %s\n", newTemp(temp), left, op, right);
        strcpy(stackVal[++topVal], temp);
    }

    // Final assignment to LHS
    printf("%c = %s\n", lhs, stackVal[topVal]);

    return 0;
}

