#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

typedef struct Node{
    int nume;
    struct Node* next;
}Node;

typedef Node* RefTipNod;

void addEdge(RefTipNod StrAdj[], int src, int dst){
    RefTipNod newNode = (RefTipNod)malloc(sizeof(Node));
    newNode -> nume = dst;
    newNode -> next = StrAdj[src];
    StrAdj[src] = newNode;
}

void printGraph(RefTipNod StrAdj[], int N){
    for(int i = 0; i < N; i++){
    }
}


/*************  ✨ Codeium Command ⭐  *************/
/**
 * Main function to demonstrate graph operations.
 * Initializes variables and adjacency list for the graph.
 * Currently, the function does not perform any operations.
 * Returns 0 to signify successful execution.
 */

/******  15dc6468-32f8-47c1-b336-c3b6d371c450  *******/
int main(){
    int j, x, y, N, A;
    RefTipNod v;
    RefTipNod StrAdj[MAX];


    return 0;
}