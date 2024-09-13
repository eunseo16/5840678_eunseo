#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

typedef struct StackNode {
    TreeNode* treeNode;
    struct StackNode* link;
} StackNode;

typedef struct {
    StackNode* top;
} LinkedStackType;

void init(LinkedStackType* s) {
    s->top = NULL;
}

int is_empty(LinkedStackType* s) {
    return (s->top == NULL);
}

void push(LinkedStackType* s, TreeNode* node) {
    StackNode* temp = (StackNode*)malloc(sizeof(StackNode));
    temp->treeNode = node;
    temp->link = s->top;
    s->top = temp;
    printf("push(%d) ", node->data);
}

TreeNode* pop(LinkedStackType* s) {
    if (is_empty(s)) {
        return NULL;
    }
    StackNode* temp = s->top;
    TreeNode* node = temp->treeNode;
    s->top = temp->link;
    free(temp);
    printf("pop(%d) ", node->data);
    return node;
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
    PlaceNode(root, 1, 9);
    PlaceNode(root->left, 0, 3);
    PlaceNode(root->left, 1, 5);
    PlaceNode(root->right, 0, 10);
    PlaceNode(root->right, 1, 13);
    PlaceNode(root->left->left, 0, 4);
    PlaceNode(root->left->left, 1, 6);
    PlaceNode(root->left->right, 0, 7);
    PlaceNode(root->left->right, 1, 8);
    PlaceNode(root->right->left, 0, 11);
    PlaceNode(root->right->left, 1, 12);
    PlaceNode(root->right->right, 0, 14);
    PlaceNode(root->right->right, 1, 15);
}

void LinkPreOrder(TreeNode* root) {
    LinkedStackType stack;
    init(&stack);

    if (root == NULL) return;

    push(&stack, root);
    while (!is_empty(&stack)) {
        TreeNode* node = pop(&stack);
        printf("visit(%d)\n ", node->data);

        if (node->right != NULL) push(&stack, node->right);
        if (node->left != NULL) push(&stack, node->left);
    }
}


void LinkInOrder(TreeNode* root) {
    LinkedStackType stack;
    init(&stack);
    TreeNode* curr = root;

    while (curr != NULL || !is_empty(&stack)) {

        while (curr != NULL) {
            push(&stack, curr);
            curr = curr->left;
        }

        curr = pop(&stack);
        printf("visit(%d)\n ", curr->data);

        curr = curr->right;
    }
}

void LinkPostOrder(TreeNode* root) {
    LinkedStackType stack1, stack2;
    init(&stack1);
    init(&stack2);

    if (root == NULL) return;

    push(&stack1, root);
    while (!is_empty(&stack1)) {
        TreeNode* node = pop(&stack1);
        push(&stack2, node);


        if (node->left != NULL) push(&stack1, node->left);
        if (node->right != NULL) push(&stack1, node->right);
    }

    while (!is_empty(&stack2)) {
        TreeNode* node = pop(&stack2);
        printf("visit(%d)\n ", node->data);
    }
}

void LinkOrders(TreeNode* root) {
    printf("\nPre_order: ");
    LinkPreOrder(root);
    printf("\nIn_order: ");
    LinkInOrder(root);
    printf("\nPost_order: ");
    LinkPostOrder(root);
    printf("\n");
}

int main() {
    TreeNode* root = (TreeNode*)malloc(sizeof(TreeNode));
    root->data = 1;
    root->left = root->right = NULL;
    GenerateLinkTree(root);

    LinkOrders(root);
    return 0;
}
