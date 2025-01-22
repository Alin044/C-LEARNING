#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    int key;
    struct Node* left;
    struct Node* right;
    int height;
}Node;

int height(Node* node){
    if(node == NULL) return 0;
    return node -> height;
}

int max(int a, int b){
    return (a > b)? a : b;
}

int getBalance(Node* node){
    if(node == NULL) return 0;
    return height(node -> left) - height(node -> right);
}

Node* rightRotate(Node* y){
    Node* x = y -> left;
    Node* T2 = x -> right;

    y -> left = x;
    x -> right = T2;

    y -> height = 1 + max(height(y -> left), height(y -> right));
    x -> height = 1 + max(height(x -> left), height(x -> right));

    return x;
}

Node* leftRotate(Node* x){
    Node* y = x -> right;
    Node* T2 = y -> left;

    y -> left = x;;
    x -> right = T2;

    x -> height = 1 + max(height(x -> left), height(x -> right));
    y -> height = 1 + max(height(y -> left), height(y -> right));

    return y;
}

Node* insertNode(Node* node, int key){
    if(node == NULL) return createNode(key);

    if(key < node -> key) node -> left = insertNode(node -> left, key);
    else if(key > node -> key) node -> right = insertNode(node -> right, key);
    else return node;

    node -> height = 1 + max(height(node -> left), height(node -> right));

    int balance = getBalance(node);

    if(balance > 1 && key < node -> left -> key)
        return rightRotate(node);
    if(balance < -1 && key > node -> right -> key)
        return leftRotate(node);
    if(balance > 1 && key > node -> left ->key){
        node -> left = leftRotate(node -> left);
        return rightRotate(node);
    }
    if(balance < -1 && key < node -> right -> key){
        node -> right = rightRotate(node -> right);
        return leftRotate(node);
    }

    return node;
}

Node* minValueNode(Node* node){
    Node* current = node;
    while(current != NULL){
        current = current -> left;
    }
}

Node* deleteNodeSuprimare(Node* root, int key){
    if(root == NULL) return root;

    if(key < root -> key) root -> left = deleteNodeSuprimare(root -> left, key);
    else if(key > root -> key) root -> right = deleteNodeSuprimare(root -> right, key);
    else{
        if((root -> left == NULL) || (root -> right == NULL)){
            Node* temp = root -> left? root -> left : root -> right;
            if(temp == NULL){
                temp = root;
                root = NULL;
            }else{
                *root = *temp;
            }
            free(temp);
        }else{
            Node* temp = minValueNode(root -> right);
            root -> key = temp -> key;
            root -> right = deleteNodeSuprimare(root -> right, temp -> key);
        }
    }

    if(root == NULL) return root;

    root -> height = 1 + max(height(root -> left), height(root -> right));

    int balance = getBalance(root);

    if(balance > 1 && getBalance(root -> left) >= 0)
        return rightRotate(root);
    if(balance < -1 && getBalance(root -> right) <= 0)
        return leftRotate(root);
    if(balance > 1 && getBalance(root -> left) <= 0){
        root -> left = leftRotate(root -> left);
        return rightRotate(root);
    }
    if(balance < -1 && getBalance(root -> right) >= 0){
        root -> right = rightRotate(root -> right);
        return leftRotate(root);
    }

    return root;
}

void preorder(Node* root){
    if(root == NULL) return ;

    printf("%d\t", root -> key);
    preorder(root -> left);
    preorder(root -> right);
}

void inorder(Node* root){
    if(root == NULL) return;

    inorder(root -> left);
    printf("%d\t", root->key);
    inorder(root -> right);
}

void postorder(Node* root){
    if(root == NULL) return;

    postorder(root -> left);
    postorder(root -> right);
    printf("%d\t", root -> key);
}

Node* createNode(int key){
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode -> key = key;
    newNode -> left = NULL;
    newNode -> right = NULL;
    newNode -> height = 1;
    return newNode;
}

int main(){

    return 0;
}
