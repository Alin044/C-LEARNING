#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct treeNode {
	struct treeNode *leftPtr, *rightPtr;
	int data;
};

typedef struct treeNode TreeNode;
typedef TreeNode *TreeNodePtr;

void insertNode(TreeNodePtr *treePtr, int value);
void inOrder(TreeNodePtr treePtr);

int main (int argc, char *argv[]) {
	unsigned int i;
	int item;
	int k;
	TreeNodePtr rootPtr=NULL;

	//k = atoi(argv[1]);
	srand(time(NULL));

	for (i=0;i<100;i++) {
		item = rand() % 100;
		insertNode(&rootPtr, item);
	}

	inOrder(rootPtr);

	printf("\n");
}

void insertNode(TreeNodePtr *treePtr, int value)
{
	if (*treePtr == NULL) {
		*treePtr = malloc(sizeof(TreeNode));
		if (*treePtr != NULL) {
			(*treePtr)->data = value;
			(*treePtr)->leftPtr = NULL;
			(*treePtr)->rightPtr = NULL;
		}
		else { printf("Problem with malloc()... we are doomed..\n"); }
	} else { // tree is not empty
		if (value < (*treePtr)->data) {
			insertNode( &((*treePtr)->leftPtr), value);
		}
		else if (value > (*treePtr)->data) {
			insertNode( &((*treePtr)->rightPtr), value);
		}
		else { printf("duplicate\n"); } // nu se insereaza noduri duplicate
	}
}

void inOrder (TreeNodePtr treePtr) {
	if (treePtr != NULL) {
		inOrder(treePtr->leftPtr);
		printf("%3d", treePtr->data);
		inOrder(treePtr->rightPtr);
	}
}


