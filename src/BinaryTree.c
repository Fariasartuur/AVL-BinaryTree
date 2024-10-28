#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct NODE{
    int num;
    struct NODE *left;
    struct NODE *right;
}NODE;

NODE *create(int num){
    NODE* newNode = (NODE*)malloc(sizeof(NODE));
    newNode->num = num;
    newNode->left = NULL;
    newNode->right = NULL;

    return newNode;
}

NODE *insert(NODE *node, int num){
    if(node == NULL) return create(num);
    
    if(num < node->num) 
        node->left = insert(node->left, num);
    else if(num > node->num) 
        node->right = insert(node->right, num);
    else 
        return node;

    return node;
}

NODE *findMin(NODE *node) {
    while (node->left != NULL) node = node->left;
    return node;
}

NODE *removeNo(NODE *root, int num) {
    if (root == NULL) return NULL;

    if (num < root->num) {
        root->left = removeNo(root->left, num);
    } else if (num > root->num) {
        root->right = removeNo(root->right, num);
    } else {
        if (root->left == NULL) {
            NODE *temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            NODE *temp = root->left;
            free(root);
            return temp;
        } else {
            NODE *temp = findMin(root->right);
            root->num = temp->num;
            root->right = removeNo(root->right, temp->num);
        }
    }
    return root;
}

NODE *search(NODE *node, int num){
    if (node == NULL) return NULL;

    if(num == node->num) return node;

    if(num < node->num)
        return search(node->left, num);
    else
        return search(node->right, num);
    
}

NODE *createTree(){
    int values[16];

    for(int i = 0; i < (sizeof(values)/sizeof(values[0])); i++){
        values[i] = rand() % 50;
    }

    NODE* node = NULL;
    for(int i = 0; i < (sizeof(values)/sizeof(values[0])); i++){
        node = insert(node, values[i]);
    }

    return node;
}

void inOrder(NODE* node){
    if(node == NULL) return;

    inOrder(node->left);
    printf("%d ", node->num);
    inOrder(node->right);
}

void preOrder(NODE* node){
    if(node == NULL) return;

    printf("%d ", node->num);
    preOrder(node->left);
    preOrder(node->right);
}

void postOrder(NODE* node){
    if(node == NULL) return;

    postOrder(node->left);
    postOrder(node->right);
    printf("%d ", node->num);
}

void printTree(NODE* tree){
    printf("\nPrinting In Order\n");
    inOrder(tree);
    printf("\n\n");
        
    printf("Printing in Pre Order\n");
    preOrder(tree);
    printf("\n\n");

    printf("Printing in Post Order\n");
    postOrder(tree);
    printf("\n\n");
}

int main(int argc, char const *argv[])
{
    srand(time(NULL));

    NODE* tree = createTree();

    int num = 2;

    printTree(tree);

    if(search(tree, num) != NULL){
        printf("Number %d found.\n", num);
        removeNo(tree, num);
        printf("Number %d removed.\n", num);
    } else{
        printf("Number %d not found.\n", num);
    }

    printTree(tree);

    return 0;
}
