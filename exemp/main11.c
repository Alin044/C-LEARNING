#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

typedef struct TipNod{
    int nume;
    struct TipNod* urm;
}TipNod;

typedef TipNod* RefTipNod;

RefTipNod StrAdj[MAX];
bool vizitat[MAX];  

void adaugaArc(int n1, int n2){
    RefTipNod v;

    v = (RefTipNod)malloc(sizeof(TipNod));
    v->nume = n2;
    v->urm = StrAdj[n2];

    v = (RefTipNod)malloc(sizeof(TipNod));
    v->nume = n1;
    v->urm = StrAdj[n1];

}

void initializareGraf(int N){
    for(int i = 1; i <= N; i++){
        StrAdj[i] = NULL;
        vizitat[i] = false;
    }
}

void BFS(int start){
    int coada[MAX], inceput = 0, sfarsit = 0;
    RefTipNod v;

    coada[sfarsit++] = start;
    vizitat[start] = true;

    while(inceput < sfarsit){
        int nodCurent = coada[inceput++];
        printf("%d ", nodCurent);

        v = StrAdj[nodCurent];
        while(v != NULL){
            int vecin = v->nume;
            if(!vizitat[vecin]){
                coada[sfarsit++] = vecin;
                vizitat[vecin] = true;
            }
            v = v->urm;
        }
    }
}

int main(){

    return 0;
}