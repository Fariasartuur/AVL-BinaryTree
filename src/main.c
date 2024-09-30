#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct NODE {
  int data;
  int depth;
  int height;
  struct NODE *left;
  struct NODE *right;
} NODE;

NODE *create(int data) {
  NODE *newnode = (NODE *)malloc(sizeof(NODE));
  if (newnode != NULL) {
    newnode->data = data;
    newnode->depth = 0;
    newnode->height = 0;
    newnode->left = NULL;
    newnode->right = NULL;
    return newnode;
  }
  printf("Error inserting %d. There is no memory available.\n", data);
  return NULL;
}

void updateDepthHeight(NODE* root, NODE* subTree){
    if(subTree == NULL) return;

      subTree->depth = root->depth + 1;

    if(root->height <= subTree->height)
        root->height = subTree->height + 1;
}

NODE *insert(NODE *root, int num) {
  if (root == NULL) {
    return create(num);
  }
  if (num < root->data) {
    root->left = insert(root->left, num);
    updateDepthHeight(root, root->left);
  } else {
    root->right = insert(root->right, num);
    updateDepthHeight(root, root->right);
  }
  return root;
}

NODE *createTree() {
  int values[16];

  for (int i = 0; i < 16; i++) {
    values[i] = rand() % 50;
  }

  NODE *root = NULL;
  for (int i = 0; i < 16; i++) {
    root = insert(root, values[i]);
  }
  return root;
}

NODE *search(NODE *root, int num) {
  if (root == NULL) {
    return NULL;
  }

  if (root->data == num) {
    return root;
  }

  if (num < root->data) {
    return search(root->left, num);
  } else {
    return search(root->right, num);
  }
}

NODE *findMinimum(NODE *root) {
  while (root->left != NULL) {
    root = root->left;
  }
  return root;
}

NODE *removeNo(NODE *root, int num) {
  if (root == NULL) {
    return NULL;
  }

  if (num < root->data) {
    root->left = removeNo(root->left, num);
  } else if (num > root->data) {
    root->right = removeNo(root->right, num);
  } else {
    if (root->left == NULL && root->right == NULL) {
      free(root);
      return NULL;
    }

    else if (root->left == NULL) {
      NODE *temp = root->right;
      free(root);
      return temp;
    } else if (root->right == NULL) {
      NODE *temp = root->left;
      free(root);
      return temp;
    } else {
      NODE *MINIMUM_NODE = findMinimum(root->right);
      root->data = MINIMUM_NODE->data;
      root->right = removeNo(root->right, MINIMUM_NODE->data);
    }
  }
  return root;
}

void inOrder(NODE *root) {
  if (root == NULL) {
    return;
  }

  inOrder(root->left);
  printf("%d ", root->data);
  inOrder(root->right);
}

void preOrder(NODE *root) {
  if (root == NULL) {
    return;
  }

  printf("%d ", root->data);
  preOrder(root->left);
  preOrder(root->right);
}

void postOrder(NODE *root) {
  if (root == NULL) {
    return;
  }

  postOrder(root->left);
  postOrder(root->right);
  printf("%d ", root->data);
}

int main() {

  srand(time(NULL));

  NODE *root = createTree();

  printf("InOrder\n");
  inOrder(root);
  printf("\n\nPreOrder\n");
  preOrder(root);
  printf("\n\nPostOrder\n");
  postOrder(root);

  return 0;
}