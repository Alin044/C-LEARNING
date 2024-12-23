#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    int balance;
};

int calcBalance(struct Node* node){
    int balance;
    int leftBalance = (node -> left)? node -> left -> balance : 0;
    int rightBalance = (node -> right)? node -> right -> balance : 0;
    balance = leftBalance - rightBalance;
    return balance;
}
int max(int x, int y){
    return (x > y)? x : y;
}

struct Node* newNode(int key){
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->balance = 0;
    return node;
}

struct Node *rightRotate(struct Node* y){
    struct Node* x = y->left;
    struct Node* T2 = x->right;

    x->right = y;
    y->left = T2;

    //mai trebui de studiat cu calcularea inaltimii
    y->balance = calcBalance(y);
    x->balance = calcBalance(x);

    return x;
}

struct Node *leftRotate(struct Node* x){
    struct Node* y = x -> right;
    struct Node* T2 = y -> left;

    y->left = x;
    x->right = T2;

    x->balance = calcBalance(x);
    y->balance = calcBalance(y);

    return y;
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

    node->balance = calcBalance(node);

    //Left Left Case
    if(node->balance > 1 && key > node->right->key){
        return rightRotate(node);
    }
    //Right Right Case
    if(node->balance < -1 && key > node->right->key){
        return leftRotate(node);
    }
    //Left Right Case
    if(node->balance > 1 && key > node->left->key){
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    //Right Left Case
    if(node->balance < -1 && key < node->right->key){
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
    root->balance = calcBalance(root);

       //Left Left Case
    if(root->balance > 1 && calcBalance(root->left) >= 0){
        return rightRotate(root);
    }
    //Right Right Case
    if(root->balance < -1 && calcBalance(root->right) <= 0){
        return leftRotate(root);
    }
    //Left Right Case
    if(root->balance > 1 && calcBalance(root->left) < 0){
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    //Right Left Case
    if(root->balance < -1 && calcBalance(root->right) > 0){
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return root;
}

struct Node* deleteInPostorder(struct Node* root, int* k){
    if(root == NULL) return NULL;

    root->left = deleteInPostorder(root->left, k);
    root->right = deleteInPostorder(root->right, k);  
    if( *k > 0){
        int key = root->key;
        root = deleteNodeSuprimare(root, key);
        (*k)--;
    }  
    return root;
}
int isNumber(char *str){
    while(*str){
        if(!isdigit(*str)) return 0;
        str++;
    }
    return 1;
}
int menu(int k){
    int opt;
    
    printf("\n1. Sterge %d noduri in postordine", k);
    printf("\n2. Afiseaza arborele in preordine");
    printf("\n3. Afiseaza arborele in inordine");
    printf("\n4. Afiseaza arborele in postordine");
    printf("\n5. Sterge un nod");
    printf("\n6. Adauga un nod");
    printf("\n0. Exit");
    printf("\nSelect an option: ");
    scanf("%d", &opt);

    return opt;
}
int main(int argc, char *argv[]){
    struct Node *root = NULL;
    int keyToDelete, keyToAdd;
    int temp[9];
    int count = 0, i;
    int k = 4;
    int opt;

//----------------input for k --------------
    if(argc < 2){
        printf("Usage: %s <integer>\n", argv[0]);
        return EXIT_FAILURE;
    }
    if(!isNumber(argv[1])){
        printf("Invalid input, must be a number\n");
        return EXIT_FAILURE;
    }
    k = atoi(argv[1]);
//-------------------------------------------


//----------------input for nodes --------------
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
//-----------------------------------------------

    do{
        opt = menu(k);
        switch(opt){
            case 1: 
                printf("\nNode Before deletion: \n");
                preOrder(root);
                printf("\n");
                root = deleteInPostorder(root, &k);
                preOrder(root);
                break;
            case 2:
                printf("\nAfiseara arborelui AVL in preordine: \n");
                preOrder(root);
                break;
            case 3:
                printf("\nAfisarea arborelui AVL in inordine: \n");
                inOrder(root);
                break;
            case 4:
                printf("\nAfisarea arborelui AVL in postordine: \n");
                postOrder(root);
                break;
            case 5:
                printf("\nIntroduceti keia nodului pe care doriti sa il stergeti: ");
                scanf("%d", &keyToDelete);
                root = deleteNodeSuprimare(root, keyToDelete);
                printf("\n");
                preOrder(root);
                break;
            case 6:
                printf("\nIntroduceti keia nodului pe care doriti sa il adaugati: ");
                scanf("%d", &keyToAdd);
                root = insert(root, keyToAdd);
                preOrder(root);
                break;
            case 0:
                break;
            default: printf("\n....Alegeti o optiune valabila!!!\n ");
                break;
        }

    }while(opt);

    printf("\nProgramul s-a incheiat...\n");
    return 0;

}
    // root = insert(root, 10);
    // root = insert(root, 20);
    // root = insert(root, 30);
    // root = insert(root, 50);
    // root = insert(root, 50);
    // root = insert(root, 25);



    // printf("Preorder traversal of the contructed AVL tree \n");
    // preOrder(root);
    // printf("\n");
    // inOrder(root);
    // printf("\nIntroduceti keia nodului pe care doriti sa o stergeti: ");
    // scanf("%d", &keyToDelete);
    // root = deleteNodeSuprimare(root, keyToDelete);
    // preOrder(root);
    // printf("Deleted %d nodes in postorder\n", k);
    // deleteInPostorder(root, &k);
    // preOrder(root);