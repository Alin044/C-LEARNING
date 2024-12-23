#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

int Values[MAX_SIZE], Keys[MAX_SIZE];
int counter = 0;

void initialize(void);
void insertNode(int key, int value);
void display(void);
int parent(int n);
int firstChild(int n);
int rightSibling(int n);
int getIndex(int n);
int root(void);
void deleteNode(int i);
int deleteTree(int n);

int menu(){
    int option;
        printf("Options Menu:\n");
        printf("1. Insert a new node\n");
        printf("2. Find the parent of a node\n");
        printf("3. Find the first child of a node\n");
        printf("4. Find the right sibling of a node\n");
        printf("5. Show the root of the tree\n");
        printf("6. Remove a node\n");
        printf("7. Display all nodes\n");
        printf("0. Exit program\n");
        printf("Enter your option: ");
        scanf("%d", &option);
    return option;
}

int main() {
    int value, key, parent_node, child, option;

    initialize();
    printf("Tree initialized:\n");
    display();

    do {
       option = menu();
        switch (option) {
            case 1:
                printf("Enter the key for the new node: ");
                scanf("%d", &key);
                printf("Enter the index for the new node: ");
                scanf("%d", &value);
                insertNode(key, value);
                break;

            case 2:
                printf("Enter the node for which you want to find the parent: ");
                scanf("%d", &key);
                parent_node = parent(key);
                if (parent_node != 0)
                    printf("The parent of the specified node is %d.\n", parent_node);
                break;

            case 3:
                printf("Enter the node to find its first child: ");
                scanf("%d", &key);
                printf("The first child of node %d is %d.\n", key, firstChild(key));
                break;

            case 4:
                printf("Enter the node to find its right sibling: ");
                scanf("%d", &key);
                printf("The right sibling of the specified node is %d.\n", rightSibling(key));
                break;

            case 5:
                printf("The root of the tree is: %d\n", root());
                break;

            case 6:
                printf("Specify the node you want to delete: ");
                scanf("%d", &key);  
                deleteTree(key);
                break;

            case 7:
                printf("Displaying all values:\n");
                display();
                break;

            case 0:
                printf("Exiting the program.\n");
                exit(1);

            default:
                printf("Invalid option. Please select a valid option from the menu.\n");
                break;
        }
    } while (option != 0);

    return 0;
}

void initialize() {
    for(int i = 0; i < MAX_SIZE; i++) {
        Values[i] = -1;
        Keys[i] = -1;
    }
}

void insertNode(int key, int value) {
    Values[counter] = value;
    Keys[counter] = key;
    counter++;
}

void display() {
    printf("Tree values array:\n");
    for(int i = 0; i < MAX_SIZE; i++)
        printf("%d ", Values[i]);
    printf("\n");

    printf("Keys array:\n");
    for(int i = 0; i < MAX_SIZE; i++)
        printf("%d ", Keys[i]);
    printf("\n");
}

int parent(int n) {
    if (n == Values[0]) {
        printf("The node is the root of the tree.\n");
        return 0;
    }
    for (int i = 1; i < MAX_SIZE; i++) {
        if (n == Values[i])
            return Values[i - 1];
    }
    return 0;
}

int firstChild(int n) {
    int pos = -1;
    for (int i = 1; i < MAX_SIZE; i++) {
        if (n == Values[i]) {
            pos = i;
            break;
        }
    }
    if (pos == -1) {
        printf("The node has no child.\n");
        return 0;
    }
    return Keys[pos];
}

int rightSibling(int n) {
    int temp = 0, pos = -1;
    for (int i = 1; i < MAX_SIZE; i++) {
        temp++;
        if (n == Values[i]) {
            pos = Keys[i];
            break;
        }
    }
    for (int i = 1; i < MAX_SIZE; i++) {
        if (Values[i] == pos && i != temp)
            return Values[i];
    }
    printf("The node has no right sibling.\n");
    return 0;
}

int getIndex(int n) {
    for (int i = 0; i < MAX_SIZE; i++) {
        if (n == Keys[i])
            return i;
    }
    return -1;
}

int root() {
    return Values[0];
}

void deleteNode(int i) {
    Values[i] = -1;
    Keys[i] = -1;
}

int deleteTree(int n) {
    int child, i = getIndex(n);
    if (i == -1) return 0;

    child = firstChild(n);
    if (child == 0) {
        deleteNode(i);
        return 0;
    }
    while (child != 0) {
        deleteTree(child);
        child = firstChild(n);
    }
    return 0;
}
