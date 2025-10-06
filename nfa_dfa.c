#include <stdio.h>
#include <string.h>

#define MAX 20       
#define MAX_DFA 1024 

int numStates, numSymbols;
char symbols[MAX];
int symbolIndex(char c);

int nfa[MAX][MAX];
int dfa[MAX_DFA][MAX];
int visited[MAX_DFA];
int dfaStates[MAX_DFA];
int dfaCount = 0;


void printSet(int stateSet)
{
    printf("{ ");
    for (int i = 0; i < numStates; i++)
    {
        if (stateSet & (1 << i))
            printf("%d ", i);
    }
    printf("}");
}


int getNextState(int stateSet, int sym)
{
    int result = 0;
    for (int i = 0; i < numStates; i++)
    {
        if (stateSet & (1 << i))
        {
            result |= nfa[i][sym];
        }
    }
    return result;
}

void convertNFAtoDFA()
{
    int queue[MAX_DFA], front = 0, rear = 0;

    int startSet = 1 << 0; 
    queue[rear++] = startSet;
    visited[startSet] = 1;
    dfaStates[dfaCount++] = startSet;

    while (front < rear)
    {
        int currSet = queue[front++];

        for (int s = 0; s < numSymbols; s++)
        {
            int nextSet = getNextState(currSet, s);
            dfa[currSet][s] = nextSet;

            if (nextSet && !visited[nextSet])
            {
                visited[nextSet] = 1;
                queue[rear++] = nextSet;
                dfaStates[dfaCount++] = nextSet;
            }
        }
    }
}

void printDFA()
{
    printf("\nDFA Transition Table:\n");
    for (int i = 0; i < dfaCount; i++)
    {
        int curr = dfaStates[i];
        printf("From ");
        printSet(curr);
        printf(":\n");
        for (int s = 0; s < numSymbols; s++)
        {
            printf("  on '%c' -> ", symbols[s]);
            printSet(dfa[curr][s]);
            printf("\n");
        }
    }
}


int symbolIndex(char c)
{
    for (int i = 0; i < numSymbols; i++)
    {
        if (symbols[i] == c)
            return i;
    }
    return -1;
}

int main()
{
    printf("Enter number of NFA states: ");
    scanf("%d", &numStates);

    printf("Enter number of input symbols: ");
    scanf("%d", &numSymbols);

    printf("Enter symbols: ");
    for (int i = 0; i < numSymbols; i++)
    {
        scanf(" %c", &symbols[i]);
    }

    memset(nfa, 0, sizeof(nfa));
    memset(visited, 0, sizeof(visited));

    int numTrans;
    printf("Enter number of transitions: ");
    scanf("%d", &numTrans);

    printf("Enter transitions in format: <from> <symbol> <to>\n");
    for (int i = 0; i < numTrans; i++)
    {
        int from, to;
        char sym;
        scanf("%d %c %d", &from, &sym, &to);
        int sIdx = symbolIndex(sym);
        nfa[from][sIdx] |= (1 << to);
    }

    convertNFAtoDFA();
    printDFA();

    return 0;
}
