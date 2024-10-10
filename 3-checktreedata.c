#include <stdio.h>
#include <stdlib.h>

// Ʈ�� ��� ����ü ����
typedef struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// ť ��� ����ü ����
typedef struct QueueNode {
    TreeNode* treeNode;
    struct QueueNode* next;
} QueueNode;

// ť ����ü ����
typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
} Queue;

// ť �ʱ�ȭ
void InitQueue(Queue* queue) {
    queue->front = queue->rear = NULL;
}

// ť�� ������� Ȯ��
int IsQueueEmpty(Queue* queue) {
    return (queue->front == NULL);
}

// ť�� ��� �߰�
void Enqueue(Queue* queue, TreeNode* node) {
    QueueNode* newQueueNode = (QueueNode*)malloc(sizeof(QueueNode));
    newQueueNode->treeNode = node;
    newQueueNode->next = NULL;
    if (queue->rear != NULL) {
        queue->rear->next = newQueueNode;
    }
    queue->rear = newQueueNode;
    if (queue->front == NULL) {
        queue->front = newQueueNode;
    }
}

// ť���� ��� ����
TreeNode* Dequeue(Queue* queue) {
    if (IsQueueEmpty(queue)) {
        return NULL;
    }
    QueueNode* temp = queue->front;
    TreeNode* node = temp->treeNode;
    queue->front = queue->front->next;
    if (queue->front == NULL) {
        queue->rear = NULL;
    }
    free(temp);
    return node;
}

// Ʈ�� ��带 �����ϴ� �Լ�
TreeNode* CreateNode(int data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// ��带 ��ġ�ϴ� �Լ�
void PlaceNode(TreeNode* node, int direction, int data) {
    if (direction == 0) {
        node->left = CreateNode(data);
    }
    else if (direction == 1) {
        node->right = CreateNode(data);
    }
}

// Ʈ���� �����ϴ� �Լ�
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

// ��� ����� ���� �ݺ������� ���ϴ� �Լ�
int GetSumOfNodes(TreeNode* root) {
    if (root == NULL) return 0;

    int sum = 0;
    Queue queue;
    InitQueue(&queue);
    Enqueue(&queue, root);

    while (!IsQueueEmpty(&queue)) {
        TreeNode* currentNode = Dequeue(&queue);
        sum += currentNode->data;

        if (currentNode->left != NULL) {
            Enqueue(&queue, currentNode->left);
        }
        if (currentNode->right != NULL) {
            Enqueue(&queue, currentNode->right);
        }
    }

    return sum;
}

// ����� ������ �ݺ������� ���ϴ� �Լ�
int GetNumberOfNodes(TreeNode* root) {
    if (root == NULL) return 0;

    int count = 0;
    Queue queue;
    InitQueue(&queue);
    Enqueue(&queue, root);

    while (!IsQueueEmpty(&queue)) {
        TreeNode* currentNode = Dequeue(&queue);
        count++;

        if (currentNode->left != NULL) {
            Enqueue(&queue, currentNode->left);
        }
        if (currentNode->right != NULL) {
            Enqueue(&queue, currentNode->right);
        }
    }

    return count;
}

// Ʈ���� ���̸� �ݺ������� ���ϴ� �Լ� (���� ������ Ʈ�� ��ȸ)
int GetHeightOfTree(TreeNode* root) {
    if (root == NULL) return 0;

    int height = 0;
    Queue queue;
    InitQueue(&queue);
    Enqueue(&queue, root);

    while (!IsQueueEmpty(&queue)) {
        int levelSize = 0;  // ���� ������ �ִ� ��� ��
        QueueNode* temp = queue.front;

        while (temp) {
            levelSize++;
            temp = temp->next;
        }

        for (int i = 0; i < levelSize; i++) {
            TreeNode* currentNode = Dequeue(&queue);

            if (currentNode->left != NULL) {
                Enqueue(&queue, currentNode->left);
            }
            if (currentNode->right != NULL) {
                Enqueue(&queue, currentNode->right);
            }
        }
        height++;
    }

    return height;
}

// �� ����� ������ �ݺ������� ���ϴ� �Լ�
int GetNumberOfLeafNodes(TreeNode* root) {
    if (root == NULL) return 0;

    int leafCount = 0;
    Queue queue;
    InitQueue(&queue);
    Enqueue(&queue, root);

    while (!IsQueueEmpty(&queue)) {
        TreeNode* currentNode = Dequeue(&queue);

        if (currentNode->left == NULL && currentNode->right == NULL) {
            leafCount++;
        }

        if (currentNode->left != NULL) {
            Enqueue(&queue, currentNode->left);
        }
        if (currentNode->right != NULL) {
            Enqueue(&queue, currentNode->right);
        }
    }

    return leafCount;
}

int main() {
    TreeNode* root = CreateNode(1);
    root->data = 1;
    GenerateLinkTree(root);


    printf("Sum of nodes: %d\n", GetSumOfNodes(root));
    printf("Number of nodes: %d\n", GetNumberOfNodes(root));
    printf("Height of Tree: %d\n", GetHeightOfTree(root));
    printf("Number of leaf nodes: %d\n", GetNumberOfLeafNodes(root));

    return 0;
}