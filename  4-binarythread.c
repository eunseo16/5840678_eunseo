
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* left, * right;
} TreeNode;

typedef struct ThreadNode {
    int data;
    struct ThreadNode* left, * right;
    int is_thread;
} ThreadNode;

void BinaryTreeInOrder(TreeNode* root) {
    if (root != NULL) {
        BinaryTreeInOrder(root->left);
        printf("%d ", root->data);
        BinaryTreeInOrder(root->right);
    }
}

ThreadNode* find_successor(ThreadNode* p) {
    ThreadNode* q = p->right;
    if (q == NULL || p->is_thread) return q;
    while (q->left != NULL) q = q->left;
    return q;
}

void ThreadTreeInOrder(ThreadNode* t) {
    ThreadNode* q = t;
    while (q->left != NULL) q = q->left;
    while (q != NULL) {
        printf("%d ", q->data);
        q = find_successor(q);
    }
}

TreeNode* insert_tree_node(TreeNode* node, int data) {
    if (node == NULL) {
        TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));
        temp->data = data;
        temp->left = temp->right = NULL;
        return temp;
    }
    if (data < node->data) {
        node->left = insert_tree_node(node->left, data);
    }
    else {
        node->right = insert_tree_node(node->right, data);
    }
    return node;
}

ThreadNode* insert_thread_node(ThreadNode* node, int data) {
    if (node == NULL) {
        ThreadNode* temp = (ThreadNode*)malloc(sizeof(ThreadNode));
        temp->data = data;
        temp->left = temp->right = NULL;
        temp->is_thread = 0;
        return temp;
    }
    if (data < node->data) {
        node->left = insert_thread_node(node->left, data);
    }
    else {
        node->right = insert_thread_node(node->right, data);
    }
    return node;
}

TreeNode* GenerateBinaryTree(int inputData[], int size) {
    TreeNode* root = NULL;
    for (int i = 0; i < size; i++) {
        root = insert_tree_node(root, inputData[i]);
    }
    return root;
}

void create_thread(ThreadNode* node, ThreadNode** prev) {
    if (node == NULL) return;
    create_thread(node->left, prev);

    if (*prev != NULL && (*prev)->right == NULL) {
        (*prev)->right = node;
        (*prev)->is_thread = 1;
    }

    *prev = node;
    create_thread(node->right, prev);
}

ThreadNode* GenerateThreadTree(int inputData[], int size) {
    ThreadNode* root = NULL;
    for (int i = 0; i < size; i++) {
        root = insert_thread_node(root, inputData[i]);
    }

    ThreadNode* prev = NULL;
    create_thread(root, &prev);
    return root;
}

void free_tree(TreeNode* root) {
    if (root == NULL) return;
    free_tree(root->left);
    free_tree(root->right);
    free(root);
}

void free_thread_tree(ThreadNode* root) {
    if (root == NULL) return;
    free_thread_tree(root->left);
    if (!root->is_thread) free_thread_tree(root->right);
    free(root);
}

int main() {
    int inputData[] = { 4, 1, 9, 13, 15, 3, 6, 14, 7, 10, 12, 2, 5, 8, 11 };
    int size = sizeof(inputData) / sizeof(inputData[0]);

    TreeNode* root = GenerateBinaryTree(inputData, size);
    printf("Binary tree inorder: ");
    BinaryTreeInOrder(root);
    printf("\n");

    ThreadNode* troot = GenerateThreadTree(inputData, size);
    printf("Thread tree inorder: ");
    ThreadTreeInOrder(troot);
    printf("\n");

    free_tree(root);
    free_thread_tree(troot);

    return 0;
}
