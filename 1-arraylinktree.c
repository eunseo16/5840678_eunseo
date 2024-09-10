#include <stdio.h>
#include <stdlib.h>

#define SIZE 15

typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

void GenerateArrayTree(int* tree) {
    int list[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };

    for (int i = 0; i < SIZE; i++) {
        tree[i] = list[i];
    }

    printf("Array Tree: ");
    for (int i = 0; i < SIZE; i++) {
        printf("%d ", tree[i]);
    }
    printf("\n");
}

void ArrayPreOrder(int* tree, int index, int size) {
    if (index >= size || tree[index] == -1) return;
    printf("%d ", tree[index]);
    ArrayPreOrder(tree, 2 * index + 1, size);
    ArrayPreOrder(tree, 2 * index + 2, size);
}

void ArrayInOrder(int* tree, int index, int size) {
    if (index >= size || tree[index] == -1) return;
    ArrayInOrder(tree, 2 * index + 1, size);
    printf("%d ", tree[index]);
    ArrayInOrder(tree, 2 * index + 2, size);
}

void ArrayPostOrder(int* tree, int index, int size) {
    if (index >= size || tree[index] == -1) return;
    ArrayPostOrder(tree, 2 * index + 1, size);
    ArrayPostOrder(tree, 2 * index + 2, size);
    printf("%d ", tree[index]);
}

void ArrayOrders(int* tree) {
    printf("Array PreOrder: ");
    ArrayPreOrder(tree, 0, SIZE);
    printf("\nArray InOrder: ");
    ArrayInOrder(tree, 0, SIZE);
    printf("\nArray PostOrder: ");
    ArrayPostOrder(tree, 0, SIZE);
    printf("\n");
}

void PlaceNode(TreeNode* node, int direction, int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;

    if (direction == 0) {
        node->left = newNode;
    }
    else {
        node->right = newNode;
    }
}

void GenerateLinkTree(TreeNode* root) {
    PlaceNode(root, 0, 2);
    PlaceNode(root, 1, 3); 

    PlaceNode(root->left, 0, 4); 
    PlaceNode(root->left, 1, 5); 

    PlaceNode(root->right, 0, 6);
    PlaceNode(root->right, 1, 7); 

    PlaceNode(root->left->left, 0, 8);
    PlaceNode(root->left->left, 1, 9);

    PlaceNode(root->left->right, 0, 10);
    PlaceNode(root->left->right, 1, 11); 

    PlaceNode(root->right->left, 0, 12);
    PlaceNode(root->right->left, 1, 13); 

    PlaceNode(root->right->right, 0, 14);
    PlaceNode(root->right->right, 1, 15);
}

void LinkPreOrder(TreeNode* root) {
    if (root == NULL) return;
    printf("%d ", root->data);
    LinkPreOrder(root->left);
    LinkPreOrder(root->right);
}

void LinkInOrder(TreeNode* root) {
    if (root == NULL) return;
    LinkInOrder(root->left);
    printf("%d ", root->data);
    LinkInOrder(root->right);
}

void LinkPostOrder(TreeNode* root) {
    if (root == NULL) return;
    LinkPostOrder(root->left);
    LinkPostOrder(root->right);
    printf("%d ", root->data);
}

void LinkOrders(TreeNode* root) {
    printf("Link PreOrder: ");
    LinkPreOrder(root);
    printf("\nLink InOrder: ");
    LinkInOrder(root);
    printf("\nLink PostOrder: ");
    LinkPostOrder(root);
    printf("\n");
}

int main() {
    int arr[SIZE];
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    root->data = 1;
    root->left = NULL;
    root->right = NULL;

    GenerateArrayTree(arr);
    GenerateLinkTree(root);

    ArrayOrders(arr);
    LinkOrders(root);


    return 0;
}