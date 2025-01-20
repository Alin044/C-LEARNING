#include <stdio.h>
#define MAXN 100
#define MAGIC -31337
#define BLACK -1
#define WHITE 1
#define GRAY 0

struct ponderi {
	int pondere;
	struct ponderi *pnext;
};

struct node {
	int key;
	struct nod *next;
	struct ponderi *p;
};


struct node * noduri[MAXN];
int culoare[MAXN];

struct queue {
	struct node *nod;
	struct queue *next, *prev;
} *qhead, *qtail;

/*
 * comentarii utile despre functia descrisa de prototip:
 *
 * primeste la intrare keyX de cautat
 *
 * RETURN: indexul nodului cu cheia cautata
 * 	   -1 in caz de eroare sau daca nodul nu este gasit
 */
int _IndicaIndexNod(int);  // prototipul functiei, sau semnatura.. se scrie la inceput..

int _isQueueEmpty(void) {
	if (qhead == qtail == NULL) return 1; //true
	else return false;
}

void _initQueue(void) {
	struct queue *q, *aux;
	if (qhead != NULL) {
		q = qhead->next;
		free(qhead);
		while (q != NULL) {
			aux = q;
			q=q->next;
			free(aux);
		}
	}
	qhead=NULL;
	qtail=NULL;
}

void _destoryQueue(void) {
	_initQueue();
}

struct queue * _addQueue(struct node *nod) {
	struct queue *crt;

	crt = (struct queue *) malloc(sizeof(struct queue));
	if (crt == NULL) {
		perror("malloc()");
		return NULL; 
	}

	crt->nod = nod;
	crt->next = qhead;
	crt->prev = NULL;

	if (qhead == NULL) qtail = crt;
	qhead=crt;
	return qhead;
}

struct node * _extractQueue(void) {
	struct node *n;
	struct queue *aux;
	
	n = qtail->nod;
	aux = qtail;
	qtail = qtail->prev;
	free(aux);
	if (qtail!=NULL) {
		qtail->next = NULL;
	}
	return n;
}


// NOD1 -> NOD3 -> NOD15 -> NOD2;
//
//
//NOD3->NOD7->NOD8;
//
//NOD15->NOD1;
//NOD2->NOD1;



void Cuprindere(void) {
	int i,s;
	struct node *nod;
	int u, v;

	_initQueue();
	for (i=0;i<MAXN;i++) culoare[i] = WHITE;
	s = 0;
	if (noduri[s] != NULL) _addQueue(noduri[s]);
	
	while (!_isQueueEmpty()) {
		nod = _extractQueue(); // un nod extras de va colora in NEGRU
				       // numai dupa ce terminam explorarea arcelor sale
		u = _IndicaIndexNod(nod->key);		
		nod = noduri[u]->next;
		while (nod!=NULL) {  // exploram toate arcele prin "cuprinderea" nodului
			v = _IndicaIndexNod(nod->key);
			if (culoare[v] == WHITE) {
				culoare[v] = GRAY;
				printf("Nodul cu cheia %d s-a colorat in GRI.\n", 
				    noduri[v]->key);
				_addQueue(noduri[v]);
			}
			nod=nod->next; // THANKS!!
		}
		culoare[u] = BLACK;
		printf("Nodul cu cheia %d s-a colorat in NEGRU.\n", noduri[u]->key);
	}
}


void InitGraf(void) {
	int i;
	struct node *crt, *aux;

	for (i=0;i<MAXN;i++) {
		if (noduri[i] != NULL) {
			crt = noduri[i]->next;
			free(noduri[i]);
			while (crt!=NULL) {
				aux=crt;
				crt = crt->next;
				free(aux);
			}
		}	
		noduri[i] = NULL;
	}
}

void suprimaNod(int keyX) {
	struct node *crt, *aux;
	int i, j;

	i = _IndicaIndexNod(keyX);	
	if (i == -1) {
		printf("Nu am gasit nodul de sters\n");
		return;
	}

	for (j=0; j<MAXN; j++) {
		if (j == i) continue; // sare peste nodul de sters
		crt = noduri[j];
		while (crt!=NULL) {
			aux = crt;
			if (crt->key == keyX) {
				aux->next = crt->next;
				free(crt); //contorArce--
			} else crt = crt->next;
		}	
	}
	// am terminat de sters toate arcele care trec prin keyX
	
	// urmeaza sa sterg nodul si lista lui proprie de adiacenta
	crt = noduri[i];
	while (crt!=NULL) {
		aux = crt;
		free(aux);
		crt = crt->next;
	}
	noduri[i] = NULL;
	//contor--

}

int GrafVid(void) {
	int i;

	for (i=0;i<MAXN;i++) {
		if (noduri[i] != NULL) return 0; // false, nu e vid
	}

	return 1; // true, graful e vid
}

int GrafPlin(void) {
	int i, contor=0;
	int contorArce=0;
	struct node *crt;

	for (i=0;i<MAXN;i++) {
		if (noduri[i] != NULL) contor++;
	}

	if (contor < MAXN) return 0; // false, nu e plin, incap noduri noi
	
	for (i=0;i<MAXN;i++) {
		if (noduri[i]!=NULL) crt = noduri[i]->next;
		else continue;
		while (crt!=NULL) {
			contorArce++;
			crt=crt->next;
		}	
	}

	if (contorArce == MAXN*(MAXN-1)) return 1;// true, graful e plin si la arce
	else return 0; // false
}

int CheieElemGraf(int index) {
	if ((index >= 0) && (index < MAXN) && (noduri[index]!=NULL)) return noduri[index]->key;
	else {
		printf("Nodul precizat nu exista in graf\n");
		return MAGIC; // semnalizez o situatie de exceptie
	}
}

int CautaCheieGraf(int keyX) {
	int i;

	for (i=0;i<MAXN;i++) {
		if (noduri[i] != NULL) {
			if (noduri[i]->key == keyX) return 1; //true
		}
	}

	return 0; //false
}

struct node * IndicaNod(int keyX) {
	int i;

	for (i=0;i<MAXN;i++) {
		if (noduri[i] != NULL) {
			if (noduri[i]->key == keyX) return noduri[i];
		}
	}
}

int _IndicaIndexNod(int keyX) {
	int i;

	for (i=0;i<MAXN;i++) {
		if (noduri[i] != NULL) {
			if (noduri[i]->key == keyX) return i;
		}
	}

	return -1; // nodul nu a fost gasit
}

int IndicaArc(int keyA, int keyB) {
	int i, contorKey=0;
	int index=-1;	
	struct node *crt;
	int flag_found=0;

	for (i=0;i<MAXN;i++) {
		if (noduri[i] != NULL) {
			if (noduri[i]->key == keyA) { index=i; break; }
		}
	}

	if (index != -1) {
		crt = noduri[index]->next;
		while (crt != NULL) {
			contorKey++;
			if (crt->key == keyB) {flag_found=1; break;}
			crt = crt->next;
		}	
		if (flag_found) return contorKey;
		else return MAGIC;
	} else return MAGIC;
}

int ArcVid(int contorKey) {
	if (contorKey == MAGIC) return 1; //true, arcul e vid
	else return 0; //false
}
