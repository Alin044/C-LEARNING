#include <stdio.h>
#include <stdlib.h>

struct Node{
    int key;
    struct Node *left;
    struct Node *right;
    int height;
};

int max(int a, int b){
    return (a > b) ? a : b;
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
    return (node);
}

struct Node* rightRotate(struct Node* y){
    struct Node* x = y->left;
    struct Node* T2 = x->right; 

    //The rotation
    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;

    return x;
}

struct Node* leftRotate(struct Node* x){
    struct Node* y = x->right;
    struct Node* T2 = y->left;

    //the rotation
    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;

    return y;
}

int getBalance(struct Node* N){
    if(N == NULL) return 0;
    return height(N->left) - height(N->right);
}

struct Node* insert(struct Node* node, int key){
    int balance;
    if(node == NULL) return newNode(key);

    if(key < node->key){
        node->left = insert(node->left, key);
    }else if(key > node->key){
        node->right = insert(node->right, key);
    }else return node;

    node->height = 1 + max(height(node->left), height(node->right));

    balance = getBalance(node);
    //Daca nodul devine nebalansat, avem 4 cazuri: 
    //1. stinga stinga
    if(balance > 1  && key < node->left->key){
        return rightRotate(node);
    }

    //2. stinga dreapta
    if(balance < -1 && key > node->right->key){
        return leftRotate(node);
    }

    //3. stinga dreata
    if(balance > 1 && key < node->left->key){
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    //4. dreapta stinga
    if(balance < -1 && key < node->right->key){
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}



int main(){

    return 0;
}

// Sa se implementeze in limbajul C tipul de date abstract arbore AVL cu operatorii de mai jos, utilizand pentru reprezentarea datelor modelul pointeri spre fii:
// 1. Tata(N: TipNod, A:TipArbore): TipNod; - operator care returnează tatăl (părintele) nodului N din  arborele A. Dacă N este chiar rădăcina lui A se returnează "nodul vid";
// 2. PrimulFiu(N: TipNod, A: TipArbore): TipNod; - operator care returnează cel mai din stânga fiu al nodului N din arborele A. Dacă N este un nod terminal, operatorul returnează "nodul vid".
// 3. FrateDreapta(N: TipNod, A:TipArbore): TipNod; operator care returnează nodul care este fratele din dreapta al nodului N din arborele A. Acest nod sedefineşte ca fiind nodul M care are acelaşi părinte T ca şi N şi care în reprezentarea arborelui apare imediat în dreapta lui N în ordonarea de la stânga la dreapta a fiilor lui T.
// 4. Cheie(N: TipNod, A: TipArbore): TipCheie; - operator care returnează cheia nodului N din arborele A.
// 6. Radacina(A: TipArbore): TipNod; - operator care returnează nodul care este rădăcina arborelui A sau “nodul vid” dacă A este un arbore vid.
// 7. Initializeaza(A: TipArbore): TipArbore; - crează arborele A vid.
// 8. Insereaza(N: TipNod, A: TipArbore); - operator care realizează inserţia nodului N în arborele A.
// 9. Suprima(N: TipNod, A: TipArbore); - operator care realizează suprimarea nodului N şi a
// descendenţilor săi din arborele A.
// 10. Inordine(A: TipArbore); - procedură care parcurge nodurile arborelui A în “inordine” şi aplică fiecărui nod procedura de prelucrare ProcesareNod.
// 11. Preordine(A: TipArbore); - procedură care parcurge nodurile arborelui A în “preordine” şi aplică fiecărui nod procedura de prelucrare ProcesareNod.
// 12. Postordine(A: TipArbore); - procedură care parcurge nodurile arborelui A în “postordine” şi aplică fiecărui nod procedura de prelucrare ProcesareNod. Functia ProcesareNod scrie (afiseaza) cheia nodului primit ca parametru.
// Programul va primi la intrare un fisier binar oarecare INPUT.DAT. Se vor transcrie in fisierul text AVL.DAT  pe cate o linie valorile numerice de la cele trei afisari in adancime (preordine, inordine respectiv postordine) dupa ce in prealabil au fost suprimate primele k noduri in POSTordine: . k se va transmite ca parametru in linia de comanda, ca numar intreg pozitiv. (unsigned int)
// Se va rescrie codul din avl.c de la zero, folosind factorul de echilibru balance in locul lui height !.