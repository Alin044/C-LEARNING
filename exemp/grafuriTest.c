#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int N[MAX];
int A[MAX][MAX];
int pondere[MAX][MAX];

void initialize(){
    int i, j;
    for(i = 0; i < MAX; i++){
        N[i] = 0;
        for(j = 0; j < MAX; j++){
            A[i][j] = 0;
            pondere[i][j] = 0;
        }
    }
}

void addNode(int *numberOfNodes){
    int i, x;
    do{
        printf("\nIntroduceti nodul : ");
        scanf("%d", &x);
        N[*numberOfNodes] = x;
        (*numberOfNodes)++;
        printf("\nPrint 0 to exit and 1 to continue : ");
        scanf("%d", &i);
    }while(i != 0);
}

void addArch(int *numberOfNodes, int *numberOfArches){
    int x, y, pond, opt;
    do{
        printf("\nIntroduceti pos x : ");
        scanf("%d", &x);
        printf("\nIntroduceti pos y : ");
        scanf("%d", &y);
        printf("\nIntroduceti ponderea : ");
        scanf("%d", &pond);
        if(x < *numberOfNodes && y < *numberOfNodes){
            A[x][y] = 1;
            A[y][x] = 1;
            pondere[x][y] = pond;
            pondere[y][x] = pond;
            (*numberOfArches)++;
        }else{
            printf("\nERROR : the node does not exist \n");
        }
        printf("\nChose 0 - exit / 1 - continue : ");
        scanf("%d", &opt);
    }while(opt != 0);
}

void displayMatrix(int numberOfNodes, int numberOfArches){
    int i, j;
    printf("\n==================================\n");
    printf("Graful are %d - noduri si %d - arcuri.\n");
    printf("Matricea de adiacenta : \n");
    for(i = 0; i < numberOfNodes; i++){
        for(j = 0; j < numberOfNodes; j++){
            printf("%d\t", A[i][j]);
        }
        printf("\n");
    }
    printf("Array nodurilor din graf : \n");
    for(i = 0; i < numberOfNodes; i++){
        printf("%d\t", N[i]);
    }
    printf("\n==================================\n");
}

void BreadthFirstSearch(int startNode, int numberOfNodes){
    int visited[MAX] = {0};
    int queue[MAX];
    int front = 0, rear = 0;

    visited[startNode] = 1;
    queue[rear++] = startNode;

    while(front < rear){
        int currentNode = queue[front++];
        printf("%d\t", currentNode);
        for(int i = 0; i < numberOfNodes; i++){
            if(A[currentNode][i] == 1 && visited[i] == 0){
                visited[i] = 1;
                queue[rear++] = i;
            }
        }
    }
}

int main(){

    return 0;
}