#include<stdio.h>
#include<stdlib.h>
#define MAX 100
int n;
int visited[MAX];
int epsilon[MAX][MAX];
void dfs(int start,int closure[],int *size)
{
    if(!visited[start])
    {
        visited[start]=1;
        closure[(*size)++]=start;
        for(int i=0;i<n;i++)
    {
        if(epsilon[start][i] && !visited[i])
        {
            dfs(i,closure,size);
        }
    }
    }
}
void find_epsilon()
{
    for(int i=0;i<n;i++)
    {
        for(int k=0;k<n;k++)
        {
            visited[k]=0;
        }
    int closure[MAX];
    int size=0;
    dfs(i,closure,&size);
    printf("e-closure(q%d){",i);
    for(int j=0;j<size;j++)
    {
        printf("q%d",closure[j]);
    }
    printf("}\n");
    }
}
int main()
{
    int transitions;
    printf("enter no of states:");
    scanf("%d",&n);
    printf("enter no of ep trans:");
    scanf("%d",&transitions);
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            epsilon[i][j]=0;
        }
    }
    for(int i=0;i<transitions;i++)
    {
        int from,to;
        scanf("%d %d",&from,&to);
        epsilon[from][to]=1;

    }
    find_epsilon();
    return 0;

}
