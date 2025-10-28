#include <stdio.h>
#include <string.h>

char result[20][20], copy[3], states[20][20];

void add_state(char a[3], int i) {
    strcpy(result[i], a);
}

void display(int n) {
    printf("\nEpsilon closure of %s = {", copy);
    for (int k = 0; k < n; k++) {
        printf(" %s", result[k]);
    }
    printf(" }\n");
}

int main() {
    FILE *INPUT = fopen("automata.txt", "r");
    if (!INPUT) {
        printf("Error: Could not open file 'automata.txt'\n");
        return 1;
    }

    char state[3], state1[3], input[3], state2[3];
    int n, i = 0, k = 0, end;

    printf("Enter the number of states: ");
    scanf("%d", &n);

    printf("Enter the state names (max 20):\n");
    for (k = 0; k < n; k++) {
        scanf("%s", states[k]);
    }

    for (k = 0; k < n; k++) {
        i = 0;
        strcpy(state, states[k]);
        strcpy(copy, state);
        add_state(state, i++);

        while (1) {
            end = fscanf(INPUT, "%s%s%s", state1, input, state2);
            if (end == EOF) break;

            if (strcmp(state, state1) == 0 && strcmp(input, "e") == 0) {
                add_state(state2, i++);
                strcpy(state, state2);
            }
        }

        display(i);
        rewind(INPUT);
    }

    fclose(INPUT);
    return 0;
}

