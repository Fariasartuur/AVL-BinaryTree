#include <stdio.h>
#include <malloc.h>

typedef struct BNode{
    int num;
    struct BNode* left;
    struct BNode* right;
} BNode;

BNode* Create(int num){
    BNode* newnode = (BNode*)malloc(sizeof(BNode));
    newnode->num = num;
    newnode->left = NULL;
    newnode->right = NULL;

    return newnode;
}

BNode* Insert(BNode* no, int num){
    if(no == NULL) return Create(num);

    if(num > no->num) no->right = Insert(no->right, num);
    else no->left = Insert(no->left, num);
    
    return no;
}

void InOrder(BNode* no){
    if(no == NULL) return;
    
    InOrder(no->left);
    printf("%d\n", no->num);
    InOrder(no->right);
}

void PreOrder(BNode* no){
    if(no == NULL) return;
    
    printf("%d\n", no->num);
    PreOrder(no->left);
    PreOrder(no->right);
}

void PostOrder(BNode* no){
    if(no == NULL) return;
    
    PostOrder(no->left);
    PostOrder(no->right);
    printf("%d\n", no->num);
}

void BinaryTree(){

    BNode* no = NULL;
    
    no = Insert(no, 15);
    no = Insert(no, 13);
    no = Insert(no, 12);
    no = Insert(no, 42);
    no = Insert(no, 15);
    no = Insert(no, 7);
    no = Insert(no, 16);
    no = Insert(no, 35);
    no = Insert(no, 10);
    no = Insert(no, 17);
    no = Insert(no, 62);

    InOrder(no);
    printf("InOrder\n");
    PreOrder(no);
    printf("PreOrder\n");
    PostOrder(no);
    printf("PostOrder\n");

}

int main(){

    BinaryTree();

    return 0;
}