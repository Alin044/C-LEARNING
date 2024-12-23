#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Nod {
    int cheie;
    int balance;
    struct _Nod* st;
    struct _Nod* dr;
} Nod;

int _max(int a, int b) { return (a > b) ? a : b; }

int height(Nod* nodCurent) {
    // calculeaza recursiv inaltimea lui nodCurent
}

int balance(Nod* nodCurent) {
    // calculeaza factorul de echilibru pentru nodCurent
}

Nod* rotateLeft(Nod* parinte) {
    // salveaz fiul dreapta
    // face rotatia la stanga schimbând pointerul dr din parinte
    // si pointerul st din fiu dreapta

    // recalcueaza factorul de echilibru pentru parinte
    // recalcueaza factorul de echilibru pentru fiu dreapta

    // returneaza fiu dreapta
}

Nod* rotateRight(Nod* parinte) {
    // salveaz fiul stanga
    // face rotatia la dreapta schimbând pointerul st din parinte
    // si pointerul dr din fiu stanga

    // recalcueaza factorul de echilibru pentru parinte
    // recalcueaza factorul de echilibru pentru fiu stanga

    // returneaza fiu stanga
}

int getBalance(Nod* nod) {
    if (nod == NULL) return 0;

    return nod->balance;
}

Nod* balanceTree(Nod* nodCurent) {
    // recalculeaza factorul de echilibru pentru nodCurent

    // verifica daca nodCurent nu este echilibrat la stanga:
    // - verifica daca e necesară o rotație dreapta => returneaza rezultatul
    // - altfel verifica dacă e necesară o rotație stânga dreapta => returneaza rezultatul


    // verifica daca nodCurent nu este echilibrat la dreapta:
    // - verifica daca e necesară o rotație stanga => returneaza rezultatul
    // - altfel verifica dacă e necesară o rotație dreapta stanga => returneaza rezultatul


    // returneaza nodCurent
    return nodCurent;
}

Nod* insert(Nod* nodCurent, int cheie) {
    if (nodCurent == NULL) {
        Nod* n = (Nod*)malloc(sizeof(Nod));
        n->cheie = cheie;
        n->balance = 0;
        n->st = NULL;
        n->dr = NULL;
        return n;
    } else if (cheie > nodCurent->cheie) {
        nodCurent->dr = insert(nodCurent->dr, cheie);
    } else if (cheie < nodCurent->cheie) {
        nodCurent->st = insert(nodCurent->st, cheie);
    } else {
        return nodCurent;
    }

    return balanceTree(nodCurent);
}

Nod* getPred(Nod* n) {
    if (n == NULL) return NULL;

    while (n->dr != NULL) {
        n = n->dr;
    }

    return n;
}

Nod* delete(Nod* nodCurent, int cheie) {
    if(nodCurent == NULL) { return NULL; }
    if (cheie > nodCurent->cheie) {
        nodCurent->dr = delete (nodCurent->dr, cheie);
    } else if (cheie < nodCurent->cheie) {
        nodCurent->st = delete (nodCurent->st, cheie);
    } else {
        if (nodCurent->st == NULL) {
            Nod* tmp = nodCurent->dr;
            free(nodCurent);
            return tmp;
        }

        if (nodCurent->dr == NULL) {
            Nod* tmp = nodCurent->st;
            free(nodCurent);
            return tmp;
        }

        Nod* pred = getPred(nodCurent->st);
        nodCurent->cheie = pred->cheie;
        nodCurent->st = delete (nodCurent->st, pred->cheie);
    }

    return balanceTree(nodCurent);
}

void printare(Nod*);

int main() {
    Nod* r = NULL;
    int v[] = {1, 2, 10, 5, 4, 3};
    for (int i = 0; i < 6; i++) {
        r = insert(r, v[i]);
        printare(r);
    }
    printf("----delete----\n");
    for (int i = 0; i < 6; i++) {
        r = delete (r, v[i]);
        printare(r);
    }
    return 0;
}

void inorder(Nod* nodCurent) {
    if (nodCurent == NULL) return;

    inorder(nodCurent->st);
    printf("%c %d", nodCurent->cheie, nodCurent->balance);
    inorder(nodCurent->dr);
}

void _printare(char* prefix, Nod* node, int isLeft) {
    if (node == NULL) {
        return;
    }

    printf("%s", prefix);
    printf("%s", isLeft ? "|--" : "|__");

    printf("%d %d\n", node->cheie, node->balance);

    char aux[100] = "";
    sprintf(aux, "%s%s\0", prefix, (isLeft ? "|   " : "    "));
    _printare(aux, node->st, 1);
    _printare(aux, node->dr, 0);
}

void printare(Nod* nod) {
    _printare("", nod, 0);
    printf("--------------\n");
}
