#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int N[MAX];
int A[MAX][MAX];
int pondere[MAX][MAX];

void intialize(){
    int i, j;
    for(i = 0; i < MAX; i++){
        N[i] = 0;
        for(j = 0; j < MAX; j++){
            A[i][j] = 0;
            pondere[i][j] = 0;
        }
    }
}

void addNode(int *n){
    do{ 
        printf("\nIntroduceti N - cheia nodului (0 - exit) : ");
        scanf("%d", &N[*n]);

        (*n)++;
    }while(N[*n-1] != 0);
    n--;
}

void addArch(int *numberOfArches, int *numberOfNodes){
    int x, y, w;    //nod a, nod b, pondere
    int opt;
    do{
        printf("\nIntroduceti pos keii a (0 - exit) : ");
        scanf("%d", &x);
        printf("\nIntroduceti pos keii b (0 - exit) : ");
        scanf("%d", &y);
        printf("\nIntroduceti ponderea arcului (0 - exit) : ");
        scanf("%d", &w);
        if(x >= *numberOfNodes){
            printf("\nERROR: inafara intervalului grafului!");
            continue;
        }
        A[x][y] = 1;
        A[y][x] = 1;
        pondere[x][y] = w;
        pondere[y][x] = w;
    }while();
}
int main(){
    int numberOfNodes = 0, numberOfArches = 0;



    return 0;
}