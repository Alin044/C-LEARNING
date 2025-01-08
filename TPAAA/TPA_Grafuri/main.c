#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int N[MAX];
int A[MAX][MAX];

void initialize(){  // Initializam toata matricea A si N cu 0;
    int i, j;
    for(i = 0; i < N; i++){
        N[i] = 0;
        for(j = 0; j < N; j++){
            A[i][j] = 0;
        }
    }
}

//populam matricea de noduri
void addNode(int *n){ //n - numarul de noduri
    do{
        printf("\nIntroduceit -0 daca ati terminat \nIntroduceti keia : ");

        scanf("%d", N[*n]);
        (*n)++;
    }while(N[*n] != 0);
}

void addArc(int *a){
    int x, y;
    int j;
    do{
        printf("\nIntroduceti pos keii a : ");
        scanf("%d", &x);
        printf("\nIntroduceti pos keii b : ");
        scanf("%d", &y);
        A[x][y] = 1;
        A[y][x] = 1;
        (*a)++;
        printf("\nIntroduceti - 0 daca ati introdus toate arcele - 1 pt a continua : ");
        scanf("%d", &j);
    }while(j != 0);
}

void deleteArch(int *a){
    int x, y;
    printf("\nIntroduceti pos keii a : ");
    scanf("%d", &x);
    printf("\nIntroduceti pos keii b : ");
    scanf("%d", &y);
    A[x][y] = 0;
}

void deleteNode(int *a, int *n){
    int keyToDelete;
    printf("\nIntroduceti pos keii pentru a fi stearsa : ");
    scanf("%d", &keyToDelete);
    for(int i = keyToDelete; i <= *n; i++){
        if(i == *n){
            N[i] = 0;
        }else{
            N[i] = N[i+1];
        }
        
    }
    for(int i = 0; i < *n; i++){
        for(int j = 0; j < *n; j++){
            if(i == keyToDelete || j == keyToDelete){
                A[i][j] = 0;
            }
        }
    }
    for(int i = 0; i < *n; i++){
        for(int j = keyToDelete; j <= *n; j++){
            A[i][j] = A[i][j+1];
        }
    }
        for(int i = keyToDelete; i <= *n; i++){
        for(int j = 0; j < *n; j++){
            A[i][j] = A[i+1][j];
        }
    }
}

int menu(){
    int option;
    printf("\nMeniu : \n");
    printf("1. Adaugare nod\n");
    printf("2. Adaugare arc\n");
    printf("3. Stergere arc\n");
    printf("4. Stergere nod\n");
    printf("5. Afisare matricea de adiacenta\n");
    printf("6. Iesire\n");
    printf("Alegeti optiunea : ");
    scanf("%d", &option);
    return option;
}

int main(){
    int j, x, y, a = 0, n = 0; //a - numar de arce || n - numar de noduri
    return 0;
}