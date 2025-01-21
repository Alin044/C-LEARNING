#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int N[MAX];
int A[MAX][MAX];
int weight[MAX][MAX];

void initialize(){  // Initializam toata matricea A si N cu 0;
    int i, j;
    for(i = 0; i < MAX; i++){
        N[i] = 0;
        for(j = 0; j < MAX; j++){
            A[i][j] = 0;
            weight[i][j] = 0;
        }
    }
}

//populam matricea de noduri
void addNode(int *n){ //n - numarul de noduri
    do{
        printf("\nIntroduceit -0 daca ati terminat \nIntroduceti keia : ");
        scanf("%d", &N[*n]);
        
        (*n)++;
    }while(N[*n - 1] != 0);
}

void addArc(int *a, int *n){
    int x, y, w;
    int j;
    do{
        printf("\nIntroduceti pos keii a : ");
        scanf("%d", &x);
        printf("\nIntroduceti pos keii b : ");
        scanf("%d", &y);
        printf("\nIntroduceți ponderea muchiei: ");
        scanf("%d", &w);
        if(x >= *n || y >= *n){
            printf("\nERROR, no nodes at this position\n");
        }else{
            A[x][y] = 1;
            A[y][x] = 1;
            weight[x][y] = w;  
            weight[y][x] = w; 
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
    A[y][x] = 0;
    weight[x][y] = 0;  
    weight[y][x] = 0; 
}

void deleteNode(int *a, int *n) {
    int keyToDelete;
    printf("\nIntroduceți poziția cheii pentru a fi ștearsă: ");
    scanf("%d", &keyToDelete);

    if (keyToDelete >= *n || keyToDelete < 0) {
        printf("\nEROARE: Poziția nu există\n");
        return;
    }

    // Ștergem nodul din vectorul N
    for (int i = keyToDelete; i < *n - 1; i++) {
        N[i] = N[i + 1];
    }
    N[*n - 1] = 0;
    (*n)--;

    // Ștergem nodul din matricea de adiacență A și din matricea de ponderi weight
    for (int i = 0; i < *n; i++) {
        for (int j = keyToDelete; j < *n; j++) {
            A[i][j] = A[i][j + 1];
            weight[i][j] = weight[i][j + 1];
        }
        A[i][*n] = 0;  // Setăm ultima coloană la 0
        weight[i][*n] = 0;
    }

    for (int i = keyToDelete; i < *n; i++) {
        for (int j = 0; j < *n; j++) {
            A[i][j] = A[i + 1][j];
            weight[i][j] = weight[i + 1][j];
        }
    }

    // Setăm ultimul rând și ultima coloană la 0
    for (int j = 0; j <= *n; j++) {
        A[*n][j] = 0;
        weight[*n][j] = 0;
    }
    for (int i = 0; i <= *n; i++) {
        A[i][*n] = 0;
        weight[i][*n] = 0;
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



void primMST(int n) {
    int parent[MAX];      // Vector pentru a stoca arborele parțial de cost minim
    int key[MAX];         // Vector pentru a stoca costurile minime
    int visited[MAX];     // Vector pentru a marca nodurile incluse în MST
    int notVisited[MAX];  // Vector pentru a marca nodurile neincluse în MST

    // Definim o valoare foarte mare pentru "infinit"
    const int INF = 999999;

    // Inițializăm cheile cu "infinit" și toate nodurile ca nevizitate
    for (int i = 0; i < n; i++) {
        key[i] = INF;      // Costul inițial este "infinit"
        visited[i] = 0;    // Niciun nod nu este în MST
        notVisited[i] = 1; // Toate nodurile sunt în notVisited
    }

    // Începem cu primul nod (nodul 0)
    key[0] = 0;          // Costul pentru nodul de start este 0
    parent[0] = -1;      // Primul nod este rădăcina arborelui

    // Construim MST-ul
    for (int count = 0; count < n - 1; count++) {
        // Găsim nodul cu cheia minimă din notVisited
        int u = -1;
        for (int v = 0; v < n; v++) {
            if (notVisited[v] && (u == -1 || key[v] < key[u])) {
                u = v;  // Alegem nodul cu costul minim din notVisited
            }
        }

        // Adăugăm nodul găsit în MST (visited)
        notVisited[u] = 0;  // Nodul u este scos din notVisited
        visited[u] = 1;     // Nodul u este adăugat în visited

        // Actualizăm cheile și părinții nodurilor din notVisited adiacente cu u
        for (int v = 0; v < n; v++) {
            if (A[u][v] && notVisited[v] && weight[u][v] < key[v]) {
                parent[v] = u;          // Actualizăm părintele
                key[v] = weight[u][v];  // Actualizăm costul minim
            }
        }
    }

    // Afișăm arborele parțial de cost minim
    printf("\nArbore parțial de cost minim (MST) folosind algoritmul lui Prim:\n");
    printf("Muchie \tPondere\n");
    for (int i = 1; i < n; i++) {
        printf("%d - %d \t%d\n", parent[i], i, weight[i][parent[i]]);
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
    printf("6. Cautare prin cuprindere (BFS)\n");
    printf("7. Cautare in adancime (DFS)\n");
    printf("8. Arbore parțial de cost minim (Prim)\n");
    printf("0. Iesire\n");
    printf("Alegeti optiunea : ");
    scanf("%d", &option);
    return option;
}

int main(){
    int i, j, x, y, a = 0, n = 0; //a - numar de arce || n - numar de noduri
    int opt;
    int visited[MAX] = {0}; 
    initialize();
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
            case 5: 
                displayMatrix(&n);
                break;
            case 6:
                printf("\nIntroduceti nodul de pornire : ");
                scanf("%d", &x);
                BFS(x, n);
                break;
            case 7:
                printf("\nIntroduceti nodul de pornire : ");
                scanf("%d", &x);
                DFS(x, visited, A, n);
                break;
            case 8:
                if (n > 0) {
                    primMST(n);
                } else {
                    printf("\nNu există noduri în graf!\n");
                }
                break;
            case 0:
                break;
            default:
                printf("\nOptiune invalida.\n");
        }
    }while(opt != 0);
    return 0;
}