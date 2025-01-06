#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct Graph {
    int numNodes;      // Numărul actual de noduri
    Node** adjLists;   // Listele de adiacență
    int* visited;      // Marcăm nodurile adăugate (1 = adăugat, 0 = nu)
    int maxNodes;      // Capacitatea maximă a grafului
} Graph;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int initialCapacity) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numNodes = 0;
    graph->maxNodes = initialCapacity;
    graph->adjLists = (Node**)malloc(initialCapacity * sizeof(Node*));
    graph->visited = (int*)calloc(initialCapacity, sizeof(int)); // Inițial, toate nodurile sunt neadăugate

    for (int i = 0; i < initialCapacity; i++) {
        graph->adjLists[i] = NULL;
    }
    return graph;
}

void ensureCapacity(Graph* graph, int node) {
    // Extindem capacitatea dacă nodul depășește limita
    if (node >= graph->maxNodes) {
        int newCapacity = graph->maxNodes * 2;
        if (node >= newCapacity) {
            newCapacity = node + 1;
        }
        graph->adjLists = (Node**)realloc(graph->adjLists, newCapacity * sizeof(Node*));
        graph->visited = (int*)realloc(graph->visited, newCapacity * sizeof(int));
        
        for (int i = graph->maxNodes; i < newCapacity; i++) {
            graph->adjLists[i] = NULL;
            graph->visited[i] = 0; // Marcăm noile poziții ca neadăugate
        }

        graph->maxNodes = newCapacity;
    }
}

void addEdge(Graph* graph, int u, int v) {
    // Extindem capacitatea grafului dacă e necesar
    ensureCapacity(graph, u);
    ensureCapacity(graph, v);

    // Dacă nodurile nu sunt deja adăugate, le marcăm și creștem numNodes
    if (graph->visited[u] == 0) {
        graph->visited[u] = 1;
        graph->numNodes++;
    }
    if (graph->visited[v] == 0) {
        graph->visited[v] = 1;
        graph->numNodes++;
    }

    // Adăugăm muchia în listele de adiacență
    Node* newNode = createNode(v);
    newNode->next = graph->adjLists[u];
    graph->adjLists[u] = newNode;

    // Pentru grafuri neorientate
    newNode = createNode(u);
    newNode->next = graph->adjLists[v];
    graph->adjLists[v] = newNode;
}

void printGraph(Graph* graph) {
    printf("Graful are %d noduri:\n", graph->numNodes);
    for (int i = 0; i < graph->maxNodes; i++) {
        if (graph->visited[i]) {
            Node* temp = graph->adjLists[i];
            printf("Nodul %d: ", i);
            while (temp) {
                printf("%d -> ", temp->data);
                temp = temp->next;
            }
            printf("NULL\n");
        }
    }
}

int main() {
    Graph* graph = createGraph(5); // Inițial, capacitatea este 5 noduri

    int u, v;
    char choice;

    printf("Introduceți muchii (u v). Tastați 'n' pentru a opri:\n");
    while (1) {
        printf("Introduceți muchia: ");
        if (scanf("%d %d", &u, &v) != 2) {
            break;
        }

        addEdge(graph, u, v);

        printf("Doriți să adăugați altă muchie? (y/n): ");
        scanf(" %c", &choice);
        if (choice == 'n' || choice == 'N') {
            break;
        }
    }

    // Afișarea grafului
    printGraph(graph);

    return 0;
}
