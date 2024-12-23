#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX 100

int ctn = 0, x;
int N[MAX];
int A[MAX][MAX];
int visited[MAX][MAX];
void initialize(){
    int i = 0;
    int j = 0;
    for(i = 0; i < MAX; i++){
        for(j = 0; j < MAX; j++){
            A[i][j] = 0;
        }
    }
}
void insertNode(){
    int i;
    printf("Insert the key: ");
    scanf("%d", &x);
    N[ctn] = x;
    ctn++;
}

void visitedReturn(){
    for(int i = 0; i < ctn; i++){
        for(int j = 0; j < ctn; j++){
            visited[i][j] = 1;
        }
    }
}

void insertArc(){
    int a, b;
    int i;
    printf("\nIntroduceti indexurile de relatie intre noduri: ");
    do{
        printf("\nNode A : ");
        scanf("%d", &a);
        printf("\nNode B : ");
        scanf("%d", &b);
        A[a][b] = 1;
        printf("\n1 to add | 0 to exit");
        scanf("%d", &i);
    }while(i);
    
}


void afisare(){
    int i, j;
    printf("\nArrayiul de relatie arcuri intre noduri: \n");
    for(i = 0; i < ctn; i++){
        for(j = 0; j < ctn; j++){
            printf("%d\t", A[i][j]);
        }
        printf("\n");
    }
    printf("\nArrayiul de noduri : \n " );
    for(i = 0; i < ctn; i++){
        printf("%d\t", N[i]);
    }
}

// void parcurgeriPrinCuprinderi(int x){
//     int i;
//     for(i = 0; i < ctn; i++){

//     }
// }


void deleteNode(){
    int mod;
    int interm;
    int i;
    printf("\nInsert the index of node to delte : ");
    scanf("%d", &mod);
    for(i = mod; i < ctn - 1; i++){
        N[mod] = N[mod+1];
    }
    int j;
    for(i = 0; i < ctn-1; i++){
        for(j = mod; j < ctn-1; j++){
            A[i][j] = A[i][j+1];
        }
    }
    for(i = mod; i < ctn - 1; i++){
        for(j = 0; j < ctn -1; j++){
            A[i][j] = A[i+1][j];
        }
    }
    ctn--;
}

void dsf(int nod){
    int i;
    
}

int algLuiPrim(){

    return 0;
}


int meniu(){
    int i;
    printf("\n1. Introduceti un nod nou_ ");
    printf("\n2. Introduceti un arc intre noduri_");
    printf("\n3. Stergeti un nod_");
    printf("\n4. Stergeti un arc_");
    printf("\n5. Afisati array-ul de noduri si matricea de relatie_");
    printf("\n6. Parcurgeri print cuprinderi_");
    printf("\n7. Parcurgeri in adincime_");
    printf("\n0. Exit_");
    printf("\n----Alegeti o optiune----");
    scanf("%d", &i);
    return i;
}

int main(){
    unsigned int opt = 0;
    initialize();
    do{
        opt = meniu();
        switch(opt){
            case 1: 
                insertNode();
                break;
            case 2:
                insertArc();
                break;
            case 3:
                deleteNode();
                break;
            case 4: 
                afisare();
                break;
            case 5: 
            
                break;
            case 6:
                break;
            case 7: 
                break;
            case 0:
                break;
        }
    }while(opt != 0);
    
    return 0;
}

//implementarea grafului cu lista de adiacenta simpluinlantuita