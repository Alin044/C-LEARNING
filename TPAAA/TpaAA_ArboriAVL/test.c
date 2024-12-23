#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int key;
    struct Node *left;
    struct Node *right;
    struct Node *parent;
    int balance;
} TipNod, *TipArbore;

// Function prototypes
TipNod* Tata(TipNod* N, TipArbore A);
TipNod* PrimulFiu(TipNod* N, TipArbore A);
TipNod* FrateDreapta(TipNod* N, TipArbore A);
int Cheie(TipNod* N, TipArbore A);
TipNod* Radacina(TipArbore A);
TipArbore Initializeaza();
TipArbore Insereaza(TipNod* N, TipArbore A);
TipArbore Suprima(TipNod* N, TipArbore A);
void Inordine(TipArbore A);
void Preordine(TipArbore A);
void Postordine(TipArbore A);
void ProcesareNod(TipNod* N);

// Helper functions
TipNod* newNode(int key);
TipNod* rightRotate(TipNod* y);
TipNod* leftRotate(TipNod* x);
int getBalance(TipNod* N);
void updateBalance(TipNod* N);
TipNod* insert(TipArbore A, int key);
TipNod* minValueNode(TipNod* node);
TipNod* deleteNode(TipArbore A, int key);

// 1. Tata
TipNod* Tata(TipNod* N, TipArbore A) {
    if (N == NULL || N == A) return NULL;
    return N->parent;
}

// 2. PrimulFiu
TipNod* PrimulFiu(TipNod* N, TipArbore A) {
    if (N == NULL) return NULL;
    return N->left;
}

// 3. FrateDreapta
TipNod* FrateDreapta(TipNod* N, TipArbore A) {
    TipNod* parent = Tata(N, A);
    if (parent == NULL) return NULL;
    if (parent->left == N) return parent->right;
    return NULL;
}

// 4. Cheie
int Cheie(TipNod* N, TipArbore A) {
    if (N == NULL) return -1; // Assuming -1 is an invalid key
    return N->key;
}

// 6. Radacina
TipNod* Radacina(TipArbore A) {
    return A;
}

// 7. Initializeaza
TipArbore Initializeaza() {
    return NULL;
}

// 8. Insereaza
TipArbore Insereaza(TipNod* N, TipArbore A) {
    return insert(A, N->key);
}

// 9. Suprima
TipArbore Suprima(TipNod* N, TipArbore A) {
    return deleteNode(A, N->key);
}

// 10. Inordine
void Inordine(TipArbore A) {
    if (A != NULL) {
        Inordine(A->left);
        ProcesareNod(A);
        Inordine(A->right);
    }
}

// 11. Preordine
void Preordine(TipArbore A) {
    if (A != NULL) {
        ProcesareNod(A);
        Preordine(A->left);
        Preordine(A->right);
    }
}

// 12. Postordine
void Postordine(TipArbore A) {
    if (A != NULL) {
        Postordine(A->left);
        Postordine(A->right);
        ProcesareNod(A);
    }
}

void ProcesareNod(TipNod* N) {
    printf("%d ", N->key);
}

TipNod* newNode(int key) {
    TipNod* node = (TipNod*)malloc(sizeof(TipNod));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->parent = NULL;
    node->balance = 0;
    return node;
}

TipNod* rightRotate(TipNod* y) {
    TipNod* x = y->left;
    TipNod* T2 = x->right;

    x->right = y;
    y->left = T2;

    if (T2 != NULL) T2->parent = y;
    x->parent = y->parent;
    y->parent = x;

    updateBalance(y);
    updateBalance(x);

    return x;
}

TipNod* leftRotate(TipNod* x) {
    TipNod* y = x->right;
    TipNod* T2 = y->left;

    y->left = x;
    x->right = T2;

    if (T2 != NULL) T2->parent = x;
    y->parent = x->parent;
    x->parent = y;

    updateBalance(x);
    updateBalance(y);

    return y;
}

int getBalance(TipNod* N) {
    if (N == NULL) return 0;
    return N->balance;
}

void updateBalance(TipNod* N) {
    if (N == NULL) return;
    N->balance = getBalance(N->left) - getBalance(N->right);
}

TipNod* insert(TipArbore A, int key) {
    if (A == NULL) return newNode(key);

    if (key < A->key) {
        A->left = insert(A->left, key);
        A->left->parent = A;
    } else if (key > A->key) {
        A->right = insert(A->right, key);
        A->right->parent = A;
    } else {
        return A; // Duplicate keys not allowed
    }

    updateBalance(A);

    int balance = getBalance(A);

    // Left Left Case
    if (balance > 1 && key < A->left->key)
        return rightRotate(A);

    // Right Right Case
    if (balance < -1 && key > A->right->key)
        return leftRotate(A);

    // Left Right Case
    if (balance > 1 && key > A->left->key) {
        A->left = leftRotate(A->left);
        return rightRotate(A);
    }

    // Right Left Case
    if (balance < -1 && key < A->right->key) {
        A->right = rightRotate(A->right);
        return leftRotate(A);
    }

    return A;
}

TipNod* minValueNode(TipNod* node) {
    TipNod* current = node;
    while (current->left != NULL)
        current = current->left;
    return current;
}

TipNod* deleteNode(TipArbore A, int key) {
    if (A == NULL) return A;

    if (key < A->key) {
        A->left = deleteNode(A->left, key);
    } else if (key > A->key) {
        A->right = deleteNode(A->right, key);
    } else {
        if ((A->left == NULL) || (A->right == NULL)) {
            TipNod* temp = A->left ? A->left : A->right;
            if (temp == NULL) {
                temp = A;
                A = NULL;
            } else {
                *A = *temp;
            }
            free(temp);
        } else {
            TipNod* temp = minValueNode(A->right);
            A->key = temp->key;
            A->right = deleteNode(A->right, temp->key);
        }
    }

    if (A == NULL) return A;

    updateBalance(A);

    int balance = getBalance(A);

    // Left Left Case
    if (balance > 1 && getBalance(A->left) >= 0)
        return rightRotate(A);

    // Left Right Case
    if (balance > 1 && getBalance(A->left) < 0) {
        A->left = leftRotate(A->left);
        return rightRotate(A);
    }

    // Right Right Case
    if (balance < -1 && getBalance(A->right) <= 0)
        return leftRotate(A);

    // Right Left Case
    if (balance < -1 && getBalance(A->right) > 0) {
        A->right = rightRotate(A->right);
        return leftRotate(A);
    }

    return A;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Usage: %s <k>\n", argv[0]);
        return 1;
    }

    unsigned int k = atoi(argv[1]);

    FILE* input = fopen("INPUT.DAT", "rb");
    if (input == NULL) {
        printf("Error opening INPUT.DAT\n");
        return 1;
    }

    TipArbore A = Initializeaza();
    int value;

    while (fread(&value, sizeof(int), 1, input) == 1) {
        A = Insereaza(newNode(value), A);
    }

    fclose(input);

    // Suppress first k nodes in postorder
    for (unsigned int i = 0; i < k; i++) {
        TipNod* node = minValueNode(A);
        A = Suprima(node, A);
    }

    FILE* output = fopen("AVL.DAT", "w");
    if (output == NULL) {
        printf("Error opening AVL.DAT\n");
        return 1;
    }

    fprintf(output, "Preorder: ");
    Preordine(A);
    fprintf(output, "\n");

    fprintf(output, "Inorder: ");
    Inordine(A);
    fprintf(output, "\n");

    fprintf(output, "Postorder: ");
    Postordine(A);
    fprintf(output, "\n");

    fclose(output);

    return 0;
}