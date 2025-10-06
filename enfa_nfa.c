#include <stdio.h>
#define MAX 10

int states, transitions;
char symbols[2] = {'a', 'b'};
int eps[MAX][MAX], trans[MAX][2][MAX];
int closure[MAX][MAX], closureSize[MAX];
int result[MAX][2][MAX], resultSize[MAX][2];
int visited[MAX];


void addEps(int from, int to) {
    int i = 0;
    while (eps[from][i] != -1)
        i++;
    eps[from][i] = to;
}


void addTrans(int from, char sym, int to) {
    int idx = (sym == 'a') ? 0 : 1;
    int i = 0;
    while (trans[from][idx][i] != -1)
        i++;
    trans[from][idx][i] = to;
}


void dfs(int s, int *arr, int *size) {
    if (visited[s])
        return;
    visited[s] = 1;
    arr[(*size)++] = s;
    for (int i = 0; eps[s][i] != -1; i++)
        dfs(eps[s][i], arr, size);
}


void computeClosures() {
    for (int i = 0; i < states; i++) {
        for (int j = 0; j < states; j++)
            visited[j] = 0;
        closureSize[i] = 0;
        dfs(i, closure[i], &closureSize[i]);
    }
}


void build() {
    for (int s = 0; s < states; s++) {
        for (int a = 0; a < 2; a++) {
            int mark[MAX] = {0};
            for (int i = 0; i < closureSize[s]; i++) {
                int q = closure[s][i];
                for (int j = 0; trans[q][a][j] != -1; j++) {
                    int t = trans[q][a][j];
                    for (int k = 0; k < closureSize[t]; k++)
                        mark[closure[t][k]] = 1;
                }
            }
            resultSize[s][a] = 0;
            for (int i = 0; i < states; i++)
                if (mark[i])
                    result[s][a][resultSize[s][a]++] = i;
        }
    }
}

int main() {
    for (int i = 0; i < MAX; i++) {
        closureSize[i] = resultSize[i][0] = resultSize[i][1] = 0;
        for (int j = 0; j < MAX; j++) {
            eps[i][j] = closure[i][j] = -1;
            trans[i][0][j] = trans[i][1][j] = -1;
            result[i][0][j] = result[i][1][j] = -1;
        }
    }

    printf("Enter number of states: ");
    scanf("%d", &states);

    printf("Enter number of transitions: ");
    scanf("%d", &transitions);
    printf("Enter transitions in form: <from> <symbol> <to>\nUse 'e' for epsilon.\n");

    for (int i = 0; i < transitions; i++) {
        int u, v;
        char c;
        scanf("%d %c %d", &u, &c, &v);
        if (c == 'e')
            addEps(u, v);
        else
            addTrans(u, c, v);
    }

    computeClosures();
    build();

    printf("\nNFA without epsilon transitions:\n");
    for (int s = 0; s < states; s++) {
        for (int a = 0; a < 2; a++) {
            printf("From state %d on '%c': ", s, symbols[a]);
            if (resultSize[s][a] == 0)
                printf("{}");
            else {
                printf("{ ");
                for (int i = 0; i < resultSize[s][a]; i++)
                    printf("%d ", result[s][a][i]);
                printf("}");
            }
            printf("\n");
        }
    }

    return 0;
}
