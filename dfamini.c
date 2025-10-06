#include <stdio.h>
#include <string.h>

#define MAX 20

int n_states, n_symbols;
int dfa[MAX][MAX];
char symbols[MAX];
int final_states[MAX], n_final;
int distinguishable[MAX][MAX];
int group[MAX];

int is_final(int s) {
    for (int i = 0; i < n_final; i++) {
        if (final_states[i] == s)
            return 1;
    }
    return 0;
}

int symbol_index(char c) {
    for (int i = 0; i < n_symbols; i++) {
        if (symbols[i] == c)
            return i;
    }
    return -1;
}

void printGroup(int g) {
    printf("{ ");
    for (int i = 0; i < n_states; i++) {
        if (group[i] == g)
            printf("%d ", i);
    }
    printf("}");
}

void input_dfa() {
    printf("Enter number of states: ");
    scanf("%d", &n_states);

    printf("Enter number of input symbols: ");
    scanf("%d", &n_symbols);

    printf("Enter symbols: ");
    for (int i = 0; i < n_symbols; i++) {
        scanf(" %c", &symbols[i]);
    }

    for (int i = 0; i < n_states; i++)
        for (int j = 0; j < n_symbols; j++)
            dfa[i][j] = -1;

    int n_trans;
    printf("Enter number of transitions: ");
    scanf("%d", &n_trans);
    printf("Enter transitions in format <from> <symbol> <to>:\n");
    for (int i = 0; i < n_trans; i++) {
        int from, to;
        char sym;
        scanf("%d %c %d", &from, &sym, &to);
        int idx = symbol_index(sym);
        if (idx == -1) {
            printf("Invalid symbol.\n");
            continue;
        }
        dfa[from][idx] = to;
    }

    printf("Enter number of final states: ");
    scanf("%d", &n_final);
    printf("Enter final states: ");
    for (int i = 0; i < n_final; i++) {
        scanf("%d", &final_states[i]);
    }
}

void minimize_dfa() {
   
    for (int i = 0; i < n_states; i++) {
        for (int j = 0; j < n_states; j++) {
            if (i == j)
                distinguishable[i][j] = 0;
            else if ((is_final(i) && !is_final(j)) || (!is_final(i) && is_final(j))) {
                distinguishable[i][j] = distinguishable[j][i] = 1;
            }
            else {
                distinguishable[i][j] = distinguishable[j][i] = 0;
            }
        }
    }

   
    int changed = 1;
    while (changed) {
        changed = 0;
        for (int i = 0; i < n_states; i++) {
            for (int j = 0; j < n_states; j++) {
                if (i == j || distinguishable[i][j])
                    continue;

                for (int k = 0; k < n_symbols; k++) {
                    int a = dfa[i][k];
                    int b = dfa[j][k];

                    if (a == -1 && b == -1)
                        continue;
                    if ((a == -1 && b != -1) || (a != -1 && b == -1) || distinguishable[a][b]) {
                        distinguishable[i][j] = distinguishable[j][i] = 1;
                        changed = 1;
                        break;
                    }
                }
            }
        }
    }

 
    for (int i = 0; i < n_states; i++)
        group[i] = -1;

    int group_count = 0;
    for (int i = 0; i < n_states; i++) {
        if (group[i] == -1) {
            group[i] = group_count;
            for (int j = i + 1; j < n_states; j++) {
                if (!distinguishable[i][j])
                    group[j] = group_count;
            }
            group_count++;
        }
    }

   
    printf("\nMinimized DFA:\n");
    for (int g = 0; g < group_count; g++) {
        printf("From ");
        printGroup(g);
        printf(":\n");

        int rep = -1;
        for (int i = 0; i < n_states; i++) {
            if (group[i] == g) {
                rep = i;
                break;
            }
        }

        for (int s = 0; s < n_symbols; s++) {
            int to = dfa[rep][s];
            printf("  on '%c' -> ", symbols[s]);
            if (to == -1) {
                printf("{}\n");
            }
            else {
                printGroup(group[to]);
                printf("\n");
            }
        }
    }
}

int main() {
    input_dfa();
    minimize_dfa();
    return 0;
}
