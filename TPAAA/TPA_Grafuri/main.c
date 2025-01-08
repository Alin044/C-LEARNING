#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int N[MAX];
int A[MAX][MAX];

void initialize(){  // Initializam toata matricea A si N cu 0;
    int i, j;
    for(i = 0; i < MAX; i++){
        N[i] = 0;
        for(j = 0; j < MAX; j++){
            A[i][j] = 0;
        }
    }
}

//populam matricea de noduri
void addNode(int *n){ //n - numarul de noduri
    do{
        printf("\nIntroduceit -0 daca ati terminat \nIntroduceti keia : ");

        scanf("%d", &N[*n]);
        (*n)++;
    }while(N[*n] != 0);
}

void addArc(int *a, int *n){
    int x, y;
    int j;
    do{
        printf("\nIntroduceti pos keii a : ");
        scanf("%d", &x);
        printf("\nIntroduceti pos keii b : ");
        scanf("%d", &y);
        if(x >= *n || y >= *n){
            printf("\nERROR, no nodes at this position\n");
        }else{
            A[x][y] = 1;
            A[y][x] = 1;
            (*a)++;
        }
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

void displayMatrix(int *n){
    printf("\n");
    for(int i = 0; i < *n; i++){
        printf("%d\t", N[i]);
    }
    printf("\n\n");
    for(int i = 0; i < *n; i++){
        for(int j = 0; j < *n; j++){
            printf("%d\t", A[i][j]);
        }
        printf("\n");
    }
}

void BFS(int startNode, int n) {
    int visited[MAX] = {0};
    int queue[MAX];
    int front = 0, rear = 0;

    visited[startNode] = 1;
    queue[rear++] = startNode;

    printf("Căutare prin cuprindere (BFS) pornind de la nodul %d: ", startNode);

    while (front < rear) {
        int currentNode = queue[front++];
        printf("%d ", currentNode);

        for (int i = 0; i < n; i++) {
            if (A[currentNode][i] == 1 && !visited[i]) {
                visited[i] = 1;
                queue[rear++] = i;
            }
        }
    }
    printf("\n");
}

void DFS(int node, int visited[], int Arch[MAX][MAX], int n){
    visited[node] = 1;
    printf("Visited node %d\n", node);

    for(int i = 0; i < n; i++){
        if(Arch[node][i] == 1 && visited[i] == 0){
            DFS(i, visited, Arch, n);
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
    int i, j, x, y, a = 0, n = 0; //a - numar de arce || n - numar de noduri
    int opt;
    int visited[MAX] = {0}; 
    do{ 
        opt = menu();
        switch(opt){
            case 1:
                addNode(&n);
                break;
            case 2:
                addArc(&a, &n);
                break;
            case 3:
                deleteArch(&a);
                break;
            case 4:
                deleteNode(&a, &n);
                break;
            default:
                printf("\nOptiune invalida.\n");
        }
    }while(opt != 0);
    return 0;
}