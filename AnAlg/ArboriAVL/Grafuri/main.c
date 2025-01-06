#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

int N[MAX];
int A[MAX][MAX];
int ctn = 0;

void initializare(){
    int i, j;
    for(i = 0; i < MAX; i++){
        for(j = 0; j < MAX; j++){
            A[i][j] = 0;
        }
    }
}

void inserare_node(){
    int x;
    printf("\nIntroduceti valoarea unui nod : ");
    scanf("%d", &x);
    N[ctn] = x;
    ctn++;
}

void insert_arc(){
    int a, b;
    do{
        printf("\nInsert 2 noduri pentru a le asocia unui arc : ");
        printf("\na : ");
        scanf("%d", &a);
        printf("\nb : ");
        scanf("%d", &b);
        A[a][b] = 1;
        printf("\n1 to add | 0 to exit");
        scanf("%d", &a);
    }while(a);
}

void afisare(){
    int i, j;
    for(i = 0; i < ctn; i++){
        printf("%d\t", N[i]);
    }
    printf("\n");
    for(i = 0; i < ctn; i++){
        for(j = 0; j < ctn; j++){
            printf("%d\t", A[i][j]);
        }
        printf("\n");
    }
}

void deleteNode(){
    int x, y;
    int i, j;
    printf("\nCe nod doriti sa stergeti : ");
    scanf("%d", &x);
    for(i = 0; i < ctn; i++){
        if(N[i] == x){
            for(j = i; j < ctn-1; j++){
                N[j] = N[j+1];
            }
            break;
        }
    }
    
}

int main(){

    return 0;
}