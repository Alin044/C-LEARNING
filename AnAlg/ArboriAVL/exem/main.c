#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    int height;
};

int max(int x, int y){
    return (x > y)? x : y;
}
int height(struct Node* N){
    if(N == NULL) return 0;
    return N->height;
}

struct Node* newNode(int key){
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

struct Node *rightRotate(struct Node* y){
    struct Node* x = y->left;
    struct Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    //mai trebui de studiat cu calcularea inaltimii
    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));

    return x;
}

struct Node *leftRotate(struct Node* x){
    struct Node* y = x -> right;
    struct Node* T2 = y -> left;

    y->left = x;
    x->right = T2;

    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return y;
}

int getBalance(struct Node *N){
    if(N == NULL) 
        return 0;
    return height(N->left) - height(N->right);
}

struct Node* insert(struct Node* node, int key){

    //Parcurgerea nodului
    if(node == NULL)
        return newNode(key);
    
    if(key < node->key)
        node->left = insert(node->left, key);
    else if(key > node->key)
        node->right = insert(node->right, key);
    else{
        return node;
    }

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    //Left Left Case
    if(balance > 1 && key > node->right->key){
        return rightRotate(node);
    }
    //Right Right Case
    if(balance < -1 && key > node->right->key){
        return leftRotate(node);
    }
    //Left Right Case
    if(balance > 1 && key > node->left->key){
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    //Right Left Case
    if(balance < -1 && key < node->right->key){
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

void preOrder(struct Node *root){
    if(root != NULL){
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void inOrder(struct Node *root){
    if(root != NULL){
        inOrder(root->left);
        printf("%d ", root->key);
        inOrder(root->right);
    }
}

void postOrder(struct Node* root){
    if(root != NULL){
        postOrder(root->left);
        postOrder(root->right);
        printf("%d ", root->key);
    }
}

struct Node* keyMinima(struct Node* node){

    struct Node* current = node;

    while(current && current -> left != NULL){
        current = current->left;
    }
    return current;

    //gaseste nodul cu keia minima
}

struct Node* deleteNodeSuprimare(struct Node* root, int key){
    if(root == NULL) return NULL;

    if(key < root->key)
        root->left = deleteNodeSuprimare(root->left, key);
    else if(key > root->key)
        root->right = deleteNodeSuprimare(root->right, key);
    else{
        //Nod cu un singur copil sau cu 2 copii
        if((root->left == NULL) || (root->right == NULL)){
            struct Node* temp = root->left ? root->left : root->right;

            if(temp == NULL){
                temp = root;
                root = NULL;
            }else{
                *root = *temp;
            }
            free(temp);
        }else{
            //In cazul in care Nodul are 2 copii
            struct Node* temp = keyMinima(root->right);

            root->key = temp->key;

            root->right = deleteNodeSuprimare(root->right, temp->key);
        }
    }
    if(root == NULL) return root;
    //De studian inaltimea
    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

       //Left Left Case
    if(balance > 1 && getBalance(root->left) >= 0){
        return rightRotate(root);
    }
    //Right Right Case
    if(balance < -1 && getBalance(root->right) <= 0){
        return leftRotate(root);
    }
    //Left Right Case
    if(balance > 1 && getBalance(root->left) < 0){
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    //Right Left Case
    if(balance < -1 && getBalance(root->right) > 0){
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

int main(){
    struct Node *root = NULL;
    int keyToDelete;
    int temp[9];
    int count = 0, i;

    FILE* inf = fopen("INPUT.DAT", "r");
    if(inf == NULL){
        perror("Eroare la deschiderea fisierului");
        return EXIT_FAILURE;
    }

    while(fscanf(inf, "%d", &temp[count]) == 1){
        printf("%d citit din INPUT.DAT \n", temp[count]);
        count++;
    }
    fclose(inf);
    printf("File closed correctly\n");

    for(i = 0; i < count; i++){
        root = insert(root, temp[i]);
    }
    // root = insert(root, 10);
    // root = insert(root, 20);
    // root = insert(root, 30);
    // root = insert(root, 50);
    // root = insert(root, 50);
    // root = insert(root, 25);

    printf("Preorder traversal of the contructed AVL tree \n");
    preOrder(root);
    printf("\n");
    inOrder(root);
    
    printf("\nIntroduceti keia nodului pe care doriti sa o stergeti: ");
    scanf("%d", &keyToDelete);
    root = deleteNodeSuprimare(root, keyToDelete);
    preOrder(root);
    return 0;
}



