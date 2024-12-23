#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int vertex;
    struct Node* next;
}AddListNode;

typedef struct Graph{
    int numVertices;
    AddListNode** adjLists;
}Graph;

AddListNode* createNode(int vertex){
    AddListNode* newNode = (AddListNode*)malloc(sizeof(AddListNode));
    newNode -> vertex = vertex;
    newNode -> next = NULL;
    return newNode;
}

Graph* createNodeGraph(int numVertices){
    int i;
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph -> numVertices = numVertices;
    graph -> adjLists = (AddListNode**)malloc(numVertices * sizeof(AddListNode*));

    for(i = 0; i < numVertices; i++){
        graph -> adjLists[i] = NULL;
    }

    return graph;
}
    

int main(){

    return 0;
}