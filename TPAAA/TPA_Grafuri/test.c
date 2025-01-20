#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int N[MAX];
int A[MAX][MAX];
int weight[MAX][MAX];

void initialize() {
    int i, j;
    for (i = 0; i < MAX; i++) {
        N[i] = 0;
        for (j = 0; j < MAX; j++) {
            A[i][j] = 0;
            weight[i][j] = 0;
        }
    }
}

void addNode(int *n) {
    do {
        printf("\nIntroduceți -0 dacă ați terminat \nIntroduceți cheia: ");
        scanf("%d", &N[*n]);
        (*n)++;
    } while (N[*n - 1] != 0);
}

void addArc(int *a, int *n) {
    int x, y, w;
    int j;
    do {
        printf("\nIntroduceți poziția cheii a: ");
        scanf("%d", &x);
        printf("\nIntroduceți poziția cheii b: ");
        scanf("%d", &y);
        printf("\nIntroduceți ponderea muchiei: ");
        scanf("%d", &w);

        if (x >= *n || y >= *n) {
            printf("\nEROARE: Nu există noduri la această poziție\n");
        } else {
            A[x][y] = 1;
            A[y][x] = 1;
            weight[x][y] = w;
            weight[y][x] = w;
            (*a)++;
        }
        printf("\nIntroduceți -0 dacă ați introdus toate arcele, altfel 1: ");
        scanf("%d", &j);
    } while (j != 0);
}

void deleteArch(int *a) {
    int x, y;
    printf("\nIntroduceți poziția cheii a: ");
    scanf("%d", &x);
    printf("\nIntroduceți poziția cheii b: ");
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
    }

    for (int i = keyToDelete; i < *n; i++) {
        for (int j = 0; j < *n; j++) {
            A[i][j] = A[i + 1][j];
            weight[i][j] = weight[i + 1][j];
        }
    }

    // Setăm ultimul rând și ultima coloană la 0
    for (int i = 0; i <= *n; i++) {
        A[i][*n] = 0;
        weight[i][*n] = 0;
    }
    for (int j = 0; j <= *n; j++) {
        A[*n][j] = 0;
        weight[*n][j] = 0;
    }
}

void displayMatrix(int *n) {
    printf("\nNoduri:\n");
    for (int i = 0; i < *n; i++) {
        printf("%d\t", N[i]);
    }
    printf("\n\nMatricea de adiacență:\n");
    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *n; j++) {
            printf("%d\t", A[i][j]);
        }
        printf("\n");
    }
    printf("\nMatricea de ponderi:\n");
    for (int i = 0; i < *n; i++) {
        for (int j = 0; j < *n; j++) {
            printf("%d\t", weight[i][j]);
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

void DFS(int node, int visited[], int Arch[MAX][MAX], int n) {
    visited[node] = 1;
    printf("Visited node %d\n", node);

    for (int i = 0; i < n; i++) {
        if (Arch[node][i] == 1 && visited[i] == 0) {
            DFS(i, visited, Arch, n);
        }
    }
}

void algoritmulPrim(int n) {
    int parent[MAX];      
    int key[MAX];         
    int visited[MAX];     
    int notVisited[MAX];  

    const int INF = 999999;

    for (int i = 0; i < n; i++) {
        key[i] = INF;     
        visited[i] = 0;    
        notVisited[i] = 1; 
    }

    key[0] = 0;          
    
    parent[0] = -1;      
    

    for (int count = 0; count < n - 1; count++) {
        int u = -1;
        for (int v = 0; v < n; v++) {
            if (notVisited[v] && (u == -1 || key[v] < key[u])) {
                u = v;  
            }
        }

        if (u == -1) {
            printf("\nGraful nu este conex!\n");
            return;
        }

        
        notVisited[u] = 0;  
        visited[u] = 1;     

        // Actualizăm cheile și părinții nodurilor din notVisited adiacente cu u
        for (int v = 0; v < n; v++) {
            if (A[u][v] && notVisited[v] && weight[u][v] < key[v]) {
                parent[v] = u;          
                key[v] = weight[u][v];  
            }
        }
    }

    printf("\nArbore parțial de cost minim folosind algoritmul lui Prim:\n");
    printf("Muchie \tPondere\n");
    for (int i = 1; i < n; i++) {
        printf("%d - %d \t%d\n", parent[i], i, weight[i][parent[i]]);
    }
}
int menu() {
    int option;
    printf("\nMeniu:\n");
    printf("1. Adaugare nod\n");
    printf("2. Adaugare arc\n");
    printf("3. Stergere arc\n");
    printf("4. Stergere nod\n");
    printf("5. Afisare matricea de adiacenta\n");
    printf("6. Cautare prin cuprindere (BFS)\n");
    printf("7. Cautare in adancime (DFS)\n");
    printf("8. Arbore parțial de cost minim (Prim)\n");
    printf("0. Iesire\n");
    printf("Alegeti optiunea: ");
    scanf("%d", &option);
    return option;
}

int main() {
    int i, j, x, y, a = 0, n = 0;
    int opt;
    int visited[MAX] = {0};
    initialize();

    do {
        opt = menu();
        switch (opt) {
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
                printf("\nIntroduceți nodul de pornire: ");
                scanf("%d", &x);
                BFS(x, n);
                break;
            case 7:
                printf("\nIntroduceți nodul de pornire: ");
                scanf("%d", &x);
                for (int i = 0; i < MAX; i++) visited[i] = 0;  // Resetăm vectorul visited
                DFS(x, visited, A, n);
                break;
            case 8:
                if (n > 0) {
                    algoritmulPrim(n);
                } else {
                    printf("\nNu există noduri în graf!\n");
                }
                break;
            case 0:
                break;
            default:
                printf("\nOpțiune invalidă.\n");
        }
    } while (opt != 0);

    return 0;
}