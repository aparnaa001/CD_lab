#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10
#define EPSILON 'e'

int n_states, n_symbols;
char symbols[MAX];
int transition[MAX][MAX][MAX];
int epsilon_closure[MAX][MAX]; 
int closure_size[MAX];

void initialize() {
    for (int i = 0; i < MAX; i++) {
        closure_size[i] = 0;
        for (int j = 0; j < MAX; j++) {
            epsilon_closure[i][j] = 0;
            for (int k = 0; k < MAX; k++) {
                transition[i][j][k] = 0;
            }
        }
    }
}

void compute_epsilon_closure(int state, int visited[]) {
    visited[state] = 1;
    epsilon_closure[state][closure_size[state]++] = state;

    for (int next = 0; next < n_states; next++) {
        if (transition[state][n_symbols][next] && !visited[next]) {
            compute_epsilon_closure(next, visited);
            for (int k = 0; k < closure_size[next]; k++) {
                int val = epsilon_closure[next][k];
                int found = 0;
                for (int m = 0; m < closure_size[state]; m++) {
                    if (epsilon_closure[state][m] == val) {
                        found = 1;
                        break;
                    }
                }
                if (!found) {
                    epsilon_closure[state][closure_size[state]++] = val;
                }
            }
        }
    }
}

void remove_epsilon() {
    int new_trans[MAX][MAX][MAX] = {0};

    for (int state = 0; state < n_states; state++) {
        for (int i = 0; i < closure_size[state]; i++) {
            int eps_state = epsilon_closure[state][i];
            for (int sym = 0; sym < n_symbols; sym++) {
                for (int k = 0; k < n_states; k++) {
                    if (transition[eps_state][sym][k]) {
                        for (int c = 0; c < closure_size[k]; c++) {
                            int final_state = epsilon_closure[k][c];
                            new_trans[state][sym][final_state] = 1;
                        }
                    }
                }
            }
        }
    }

    // Print result
    printf("\nNFA without ε-transitions:\n");
    for (int state = 0; state < n_states; state++) {
        for (int sym = 0; sym < n_symbols; sym++) {
            printf("δ(q%d, %c) = { ", state, symbols[sym]);
            for (int k = 0; k < n_states; k++) {
                if (new_trans[state][sym][k])
                    printf("q%d ", k);
            }
            printf("}\n");
        }
    }
}

int symbol_index(char sym) {
    for (int i = 0; i < n_symbols; i++) {
        if (symbols[i] == sym)
            return i;
    }
    return -1;
}

int main() {
    initialize();

    printf("Enter number of states: ");
    scanf("%d", &n_states);

    printf("Enter number of input symbols (excluding epsilon): ");
    scanf("%d", &n_symbols);

    printf("Enter the input symbols: ");
    for (int i = 0; i < n_symbols; i++) {
        scanf(" %c", &symbols[i]);
    }

    printf("Enter the transition table:\n");
    printf("Format: from_state input_symbol to_state (Enter -1 - to stop)\n");

    while (1) {
        int from, to;
        char sym;
        scanf("%d %c %d", &from, &sym, &to);
        if (from == -1 || to == -1)
            break;

        int idx = (sym == EPSILON) ? n_symbols : symbol_index(sym);
        if (idx >= 0 && from < n_states && to < n_states) {
            transition[from][idx][to] = 1;
        } else {
            printf("Invalid input\n");
        }
    }

    for (int i = 0; i < n_states; i++) {
        int visited[MAX] = {0};
        compute_epsilon_closure(i, visited);
    }

    printf("\nEpsilon closures:\n");
    for (int i = 0; i < n_states; i++) {
        printf("ε-closure(q%d) = { ", i);
        for (int j = 0; j < closure_size[i]; j++) {
            printf("q%d ", epsilon_closure[i][j]);
        }
        printf("}\n");
    }

    remove_epsilon();

    return 0;
}

