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

void addNode(int *n){
    do{ 
        printf("\nIntroduceti N - cheia nodului (0 - exit) : ");
        scanf("%d", &N[*n]);

        (*n)++;
    }while(N[*n-1] != 0);
    n--;
}

void addArch(int *numberOfArches, int *numberOfNodes){
    int x = 0, y = 0, w = 0;    //nod a, nod b, pondere
    int opt;
    do{
        opt = 0;
        printf("\nIntroduceti pos keii a (0 - exit) : ");
        scanf("%d", &x);
        printf("\nIntroduceti pos keii b (0 - exit) : ");
        scanf("%d", &y);
        printf("\nIntroduceti ponderea arcului (0 - exit) : ");
        scanf("%d", &w);
        for(int i = 0; i < *numberOfNodes; i++){
            if(N[i] == x){
                x = i;
                opt++;
            }
            if(N[i] == y){
                y = i;
                opt++;
            }
        }
        if(opt >= 2){
            A[x][y] = 1;
            A[y][x] = 1;    
            pondere[x][y] = w;
            pondere[y][x] = w;
            (*numberOfArches)++;
        }else{
            opt = 1;
            printf("\nNu exista nodul %d sau nodul %d.\n", x, y);
        }
        
    }while(x != 0 || y != 0 || w != 0 || opt != 0);
}

void deleteArch(int *numberOfNodes, int* numberOfArches){
    int x, y;
    printf("\nIntroduceti arcul pe care doriti sa il stergeti.");
    printf("\na : ");
    scanf("%d", &x);
    printf("\nb : ");
    scanf("%d", &y);
    if(x <= *numberOfNodes && y <= *numberOfNodes){
        if(A[x][y] == 1 && A[y][x] == 1){
            A[x][y] = 0;
            A[y][x] = 0;
            pondere[x][y] = 0;
            pondere[y][x] = 0;
            (*numberOfArches)--;
        }
    }
}


void deleteNode(int *numberOfNodes, int *numberOfArches){
    int x, opt = 0;
    printf("\nIntroduceti nodul pe care doriti sa il stergeti : ");
    scanf("%d", &x);
    x--;
    if(x <= *numberOfNodes){
        for(int i = x; i < (*numberOfNodes)-1; i++){
            N[i] = N[i+1];
            for(int j = 0; j < *numberOfNodes; j++){
                A[i][j] = A[i+1][j];
                pondere[i][j] = pondere[i+1][j];
            }
            
        }
        for(int i = 0; i < *numberOfNodes; i++){
            for(int j = x; j < (*numberOfNodes)-1; j++){
                A[i][j] = A[i][j+1];
                pondere[i][j] = pondere[i][j+1];
            }
            A[*numberOfNodes - 1][i] = 0;
            A[i][*numberOfNodes - 1] = 0;
            pondere[*numberOfNodes - 1][i] = 0;
            pondere[i][*numberOfNodes - 1] = 0;
        }
        N[*numberOfNodes - 1] = 0;
        (*numberOfNodes)--;
        for(int i = 0; i < *numberOfNodes; i++){
            for(int j = 0; j < *numberOfNodes; j++){
                if(A[i][j] == 1){
                    if(i == j){
                        opt++;
                    }
                    opt++;
                }
            }
        }
        *numberOfArches = opt / 2;
    }else{
        printf("\nERROR : Pozitia nu exitsta");
        return;
    }
}


void displayMatrix(int numberOfNodes, int numberOfArches){
    printf("\n=============================");
    printf("\nMatricea de adiacenta a grafului: ");
    for(int i = 0; i < numberOfNodes; i++){
        printf("\n");
        for(int j = 0; j < numberOfNodes; j++){
            printf("%d\t", A[i][j]);
        }
    }
    printf("\n=============================\n");
    printf("Keile nodurilor grafului : ");
    for(int i = 0; i < numberOfNodes; i++){
        printf("%d\t", N[i]);
    }
}
void BreadthFirstSearch(int numberOfNodes, int startNode){
    int visited[MAX] = {0};
    int queue[MAX];
    int front = 0, rear = 0;

    visited[startNode] = 1;
    queue[rear++] = startNode;

    printf("Cautare prin Cuprindere (Breadth First Search), nod de start = %d : ", N[startNode]);
    
    while(front < rear){
        int currentNode = queue[front++];
        printf("%d\t", currentNode);

        for(int i = 0; i < numberOfNodes; i++){
            if(A[currentNode][i] == 1 && !visited[i]){
                visited[i] = 1;
                queue[rear++] = i;
            }
        }
    }
    printf("\n");
}

void DepthFirstSearch(int startNode, int visited[], int numberOfNodes){
    visited[startNode] = 1;
    printf("Visited node : %d\n", N[startNode]);

    for(int i = 0; i < numberOfNodes; i++){
        if(A[startNode][i] == 1 && visited[i] == 0){
            DepthFirstSearch(i, visited, numberOfNodes);
        }
    } 
}

void algoritmulLuiPrim(int numberOfNodes){
    int parent[MAX];
    int key[MAX]; //Lungimea de acoperire minima
    int visited[MAX];
    int costDeAcoperireMinim = 0;

    const int INF = 999999;


    //Initializarea variabilelor
    for(int i = 0; i < numberOfNodes; i++){
        key[i] = INF;
        visited[i] = 0;
    }

    key[0] = 0;
    parent[0] = -1;

    for(int count = 0; count < numberOfNodes - 1; count++){
        int u = -1;
        for(int v = 0; v < numberOfNodes; v++){
            if(visited[v] == 0 && (u == -1 || key[v] < key[u])){
                u = v;
            }
        }

        visited[u] = 1;

        for(int v = 0; v < numberOfNodes; v++){
            if(A[u][v] && visited[v] == 0 && pondere[u][v] < key[v]){
                parent[v] = u;
                key[v] = pondere[u][v];
            }
        }
    }

    printf("\nArborele de coperire minima folosind algoritmul lui Prim : \n");
    printf("Muchie\tPondere\n");
    for(int i = 1; i < numberOfNodes; i++){
        printf("%d - %d\t%d\n", parent[i], i, pondere[i][parent[i]]);
        costDeAcoperireMinim = pondere[i][parent[i]] + costDeAcoperireMinim;
    }
    printf("\nCost de acoperire minim : %d \n", costDeAcoperireMinim);

}
int meniu();
int main(){
    int numberOfNodes = 0, numberOfArches = 0;
    int opt;
    int visited[MAX] = {0};
    initialize();
    do{
        opt = meniu();
        switch(opt){
            case 1:
                addNode(&numberOfNodes);
                break;
            case 2:
                addArch(&numberOfNodes, &numberOfArches);
                break;
            case 3:
                displayMatrix(numberOfNodes, numberOfArches);
                break;
            case 4:
                printf("\nIntroduceti nodul de pornire pentru cautare prin Cuprindere (BFS): ");
                int startNode;
                scanf("%d", &startNode);
                BreadthFirstSearch(numberOfNodes, startNode);
                break;
            case 5:
                printf("\nAfisare nodurile vizitate prin DFS:\n");
                DepthFirstSearch(0, visited, numberOfNodes);
                break;
            case 6:
                algoritmulLuiPrim(numberOfNodes);
                break;
            case 7:
                deleteArch(&numberOfNodes, &numberOfArches);
                break;
            case 8:
                deleteNode(&numberOfNodes, &numberOfArches);
                break;
            case 0:
                printf("\nExiting....");
                break;
            default:
                printf("\nInvalid option, please try again\n");
                break;
        }
    }while(opt != 0);


    return 0;
}

int meniu(){
    int option;
    printf("\n\tMeniu : \n");
    printf("1. Adaugare nod.\n");
    printf("2. Adaugare arc.\n");
    printf("3. Afisarea matricei de adiacenta\n");
    printf("4. Cautare prin Curprindere (BFS)\n");
    printf("5. Cautare prin Adancime (DFS)\n");
    printf("6. Algoritmul lui Prim\n");
    printf("7. Stergere arc\n");
    printf("8. Stergere nod\n");
    printf("0. Exit");
    printf("--------Alegeti optiunea dorita--------");
    scanf("%d",&option);
    return option;
}