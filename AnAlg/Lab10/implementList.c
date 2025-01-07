#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
    int key;
    struct Node *next;
}Node;

typedef struct Graph{
    int num_nodes;
    Node** adjLists;
}Graph;

Node* createNode(int data){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode -> key = data;
    newNode -> next = NULL;
    return newNode;
}

Graph* createGraph(int numNodes){
    int i;
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph -> num_nodes = numNodes;
    graph -> adjLists = (Node**)malloc(numNodes * sizeof(Node*));
    for(i = 0; i < numNodes; i++){
        graph -> adjLists[i] = NULL;
    }
    return graph;
}

void addEdge(Graph* graph, int u, int v){
    Node* newNode = createNode(v);
    newNode -> next = graph -> adjLists[u];
    graph -> adjLists[u] = newNode;

    newNode = createNode(u);
    newNode -> next = graph -> adjLists[v];
    graph -> adjLists[v] = newNode;
}

void printGraph(Graph* graph){
    int i;
    for(i = 0; i < graph -> num_nodes; i++){ printf("\n");
        Node* temp = graph -> adjLists[i];
        printf("Nodul %d : \n", &i);
        while(temp){
            printf("%d -> ", temp -> key);
            temp = temp -> next;
        }
        printf("NULL");
    }
}
    
void printEdges(Graph* graph, int node){
    if(node < 0 || node > graph -> num_nodes){
        printf("Invalid node\n");
        return;
    }
    printf("\nNodurile adiacente nodului %d :  \tdata : %d \n", node, graph -> adjLists[node] -> key);
    Node* temp = graph -> adjLists[node];
    while(temp){
        printf(" %d -> ", temp -> key);
        temp = temp -> next;
    }
    printf("NULL\n");    
}

void deleteEdge(Graph* graph, int u, int v){
    Node* temp = graph -> adjLists[u];
    Node* prev = NULL;
    while(temp != NULL && temp -> key != v){
        prev = temp;
        temp = temp -> next;
    }
    if(temp == NULL) return;
    if(prev == NULL){
        graph -> adjLists[u] = temp -> next;
    }else{
        prev -> next = temp -> next;
    }
    free(temp);

    temp = graph -> adjLists[v];
    prev = NULL;
    while(temp != NULL && temp -> key != v){
        prev = temp;
        temp = temp -> next;
    }
    if(temp == NULL) return;
    if(prev == NULL){
        graph -> adjLists[v] = temp -> next;
    }else{
        prev -> next = temp -> next;
    }
    free(temp);
}

void deleteNode(Graph* graph, int node){
    if(node < 0 || node >= graph -> num_nodes){
        printf("Invalid node\n");
        return;
    }

    for(int i = 0; i < graph -> num_nodes; i++){
        deleteEdge(graph, node, i);
    }

    Node* temp = graph -> adjLists[node];
    while(temp != NULL){
        Node* next = temp -> next;
        free(temp);
        temp = next;
    }
    graph -> adjLists[node] = NULL;
}

void DFS(Graph* graph, int node, int* visited){
    visited[node] = 1;
    Node* temp = graph -> adjLists[node];
    printf("%d ", node);
    while(temp != NULL){
        if(!visited[temp -> key]){
            DFS(graph, temp -> key, visited);
        }
        temp = temp -> next;
    }
}

void BFS(Graph* graph, int startNode){
    int* visited = (int*)calloc(graph->num_nodes, sizeof(int));
    int* queue = (int*)malloc(graph->num_nodes * sizeof(int));
    int front = 0, rear = 0;
    visited[startNode] = 1;
    queue[rear++] = startNode;

    while(front != rear){
        int currentNode = queue[front++];
        printf("%d ", currentNode);
        Node* temp = graph -> adjLists[currentNode];
        while(temp){
            int adjNode = temp -> key;
            if(!visited[adjNode]){
                visited[adjNode] = 1;
                queue[rear++] = adjNode;
            }
            temp = temp -> next;

        }
    }
    free(queue);
    free(visited);
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


    return 0;
}