#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

typedef struct Node node;

node* createNode(int item){
    node* newNode = (node*)malloc(sizeof(node));
    newNode -> data = item;
    newNode -> left = newNode -> right = NULL;
    return newNode;
}


int main(){
    node* firstNode = createNode(2);
    node* secondNode = createNode(3);
    node* thirdNode = createNode(4);
    node* fourthNode = createNode(5);

    firstNode -> left = secondNode;
    firstNode -> right = thirdNode;
    secondNode -> left = fourthNode;

    return 0;
}