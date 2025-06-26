// List Merge and Insert Program

#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* create_node(int value) {
    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) {
        printf("Memory allocation failed\n");
        exit(1);
    }
    new_node->data = value;
    new_node->next = NULL;
    return new_node;
}

void append(Node** head, int value) {
    Node* new_node = create_node(value);
    if (*head == NULL) {
        *head = new_node;
        return;
    }

    Node* temp = *head;
    while (temp->next != NULL)
        temp = temp->next;

    temp->next = new_node;
}

void insert(Node** head, int value) {
    Node* new_node = create_node(value);

    if (*head == NULL || (*head)->data >= value) {
        new_node->next = *head;
        *head = new_node;
        return;
    }

    Node* current = *head;
    while (current->next != NULL && current->next->data < value)
        current = current->next;

    new_node->next = current->next;
    current->next = new_node;
}

void print_list(Node* head) {
    int count = 0;
    Node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        count++;
        if (count % 10 == 0)
            printf("\n");
        temp = temp->next;
    }
    if (count % 10 != 0)
        printf("\n");
}

void free_list(Node* head) {
    Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

int main() {
    Node* L1 = NULL;
    Node* L2 = NULL;
    int n1, n2, value;

    printf("Input size of L1: ");
    scanf_s("%d", &n1);
    printf("Input %d integers in order:\n", n1);
    for (int i = 0; i < n1; i++) {
        scanf_s("%d", &value);
        append(&L1, value);
    }

    printf("Input size of L2: ");
    scanf_s("%d", &n2);
    printf("Input %d random integers:\n", n2);
    for (int i = 0; i < n2; i++) {
        scanf_s("%d", &value);
        append(&L2, value);
    }

    Node* temp = L2;
    while (temp != NULL) {
        insert(&L1, temp->data);
        temp = temp->next;
    }

    printf("Modified list L1:\n");
    print_list(L1);

    free_list(L1);
    free_list(L2);

    return 0;
}