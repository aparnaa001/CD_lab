#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

int main() {
    FILE *f1;
    char c, str[100];
    int lineno = 1, num = 0, i = 0;

    clrscr(); 
    printf("Enter the C program (Press Ctrl+Z then Enter to end input):\n");

    f1 = fopen("input.txt", "w");
    if (f1 == NULL) {
        printf("Error opening file!\n");
        return;
    }

    while ((c = getchar()) != EOF) {
        putc(c, f1);
    }

    fclose(f1);

    f1 = fopen("input.txt", "r");
    if (f1 == NULL) {
        printf("Error reading file!\n");
        return;
    }

    while ((c = getc(f1)) != EOF) {
        if (isdigit(c)) {
            num = c - '0';
            c = getc(f1);
            while (isdigit(c)) {
                num = num * 10 + (c - '0');
                c = getc(f1);
            }
            printf("%d is a number\n", num);
            ungetc(c, f1);  // push back last non-digit
        }
        else if (isalpha(c)) {
            i = 0;
            str[i++] = c;
            c = getc(f1);
            while (isalnum(c) || c == '_' || c == '$') {
                str[i++] = c;
                c = getc(f1);
            }
            str[i] = '\0';

            if (
                strcmp("for", str) == 0 || strcmp("while", str) == 0 || strcmp("do", str) == 0 ||
                strcmp("int", str) == 0 || strcmp("float", str) == 0 || strcmp("char", str) == 0 ||
                strcmp("double", str) == 0 || strcmp("static", str) == 0 ||
                strcmp("switch", str) == 0 || strcmp("case", str) == 0
            ) {
                printf("%s is a keyword\n", str);
            } else {
                printf("%s is an identifier\n", str);
            }

            ungetc(c, f1);
        }
        else if (c == ' ' || c == '\t') {
          
        }
        else if (c == '\n') {
            lineno++;
        }
        else {
            printf("%c is a special symbol\n", c);
        }
    }

    printf("Total number of lines: %d\n", lineno);
    fclose(f1);
    getch();
    return 0;
}




