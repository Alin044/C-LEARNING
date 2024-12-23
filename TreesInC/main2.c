#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int data;
    struct Node *firstChild;
    struct Node *nextSibling;
}node;

node* createNode(int data){
    node* newNode = (node*)malloc(sizeof(node));
    if(newNode != NULL){
        newNode -> data = data;
        newNode -> firstChild = NULL;
        newNode -> nextSibling = NULL;
    }
    return newNode;
}

void insertChild(node* parent, int childData){
    if(parent == NULL) return;

    node* child = createNode(childData);
    if(parent -> firstChild == NULL){
        parent -> firstChild = child;
    }else{
        child -> nextSibling = parent -> firstChild;
        parent -> firstChild = child;
    }
}

node* findNode(node* root, int key){
    if(root == NULL) return NULL;

    if(root -> data == key) return root;

    node* result = findNode(root -> firstChild, key);
    if(result != NULL) return result;

    return findNode(root -> nextSibling, key);
}

void deleteTree(node* root){
    if(root == NULL) return;

    deleteTree(root -> firstChild);
    deleteTree(root -> nextSibling);

    printf("Deleting node with data: %d\n", root->data);
    free(root);
}

void preorderTraversal(node* root){
    if(root == NULL) return;

    printf("%d ", root -> data);
    preorderTraversal(root -> firstChild);
    preorderTraversal(root -> nextSibling);
}

void postorderTraversal(node* root){
    if(root == NULL) return;

    postorderTraversal(root -> firstChild);
    printf("%d ", root -> data);
    postorderTraversal(root -> nextSibling);
}

int countLeaves(node* root){
    int count = 0;
    if(root == NULL) return 0;

    if(root -> firstChild == NULL) return 1;

    node* child = root -> firstChild;
    while(child != NULL){
        count += countLeaves(child);
        child = child -> nextSibling;
    }
    return count;
}

int findDepth(node* root, int value, int depth){
    int childDepth;
    if(root == NULL) return -1;

    if(root -> data == value) return depth;

    node* child = root -> firstChild;   
    while(child != NULL){
        childDepth = findDepth(child, value, depth + 1);
        if(childDepth!= -1) return childDepth;
        child = child -> nextSibling;
    }
} 

int getHeight(node* root){
    if(root == NULL) return -1;

    int maxHeight = -2;
    node* child = root -> firstChild;

    while(child != NULL){
        int childHeight = getHeight(child);
        if(childHeight > maxHeight) maxHeight = childHeight;
        child = child -> nextSibling;
    }
    return maxHeight + 1;
}
int countNodes(node* root){
    if(root == NULL) return 0;

    int count = 1;
    node* child = root -> firstChild;
    while(child != NULL){
        count += countNodes(child);
        child = child -> nextSibling;
    }
    return count;
}


int main(){
    node* root = createNode(1);

    insertChild(root, 2);
    insertChild(root, 3);
    insertChild(root, 4);

    node* node2 = findNode(root, 2);
    if(node2 != NULL){
        insertChild(node2, 5);
        insertChild(node2, 6);
    }

    node* node3 = findNode(root, 3);
    if(node3 != NULL){
        insertChild(node3, 7);
        insertChild(node3, 8);
    }

    printf("Preorder traversal: ");
    preorderTraversal(root);
    printf("\n");

    printf("Postorder traversal: ");
    postorderTraversal(root);
    printf("\n");

    deleteTree(root);

    return 0;
}
