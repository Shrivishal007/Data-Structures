#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct NODE
{
    struct NODE *prev;
    int data;
    struct NODE *next;
} NODE;

typedef struct
{
    int size;
    NODE *front;
    NODE *rear;
} Deque;

Deque *createDeque()
{
    Deque *deque = (Deque *)malloc(sizeof(Deque));
    if (deque == NULL)
    {
        printf("Deque is not created\n");
        exit(1);
    }

    deque->size = 0;
    deque->front = deque->rear = NULL;
    return deque;
}

void insertRear(Deque *deque, int value)
{
    NODE *node = (NODE *)malloc(sizeof(NODE));
    if (node == NULL)
    {
        printf("Node is not created\n");
        exit(1);
    }

    node->data = value;
    node->prev = deque->rear;
    node->next = NULL;
    if (deque->front == NULL)
        deque->front = node;
    else
        deque->rear->next = node;
    deque->rear = node;
    (deque->size)++;
    printf("%d is added in the rear of deque linked list\n", deque->rear->data);
}

void insertFront(Deque *deque, int value)
{
    NODE *node = (NODE *)malloc(sizeof(NODE));
    if (node == NULL)
    {
        printf("Node is not created\n");
        exit(1);
    }

    node->data = value;
    node->next = deque->front;
    node->prev = NULL;
    if (deque->front == NULL)
        deque->rear = node;
    else
        deque->front->prev = node;
    deque->front = node;
    (deque->size)++;
    printf("%d is added in the front of deque linked list\n", deque->front->data);
}

int deleteFront(Deque *deque)
{
    if (deque->front == NULL)
        return INT_MIN;

    NODE *node = deque->front;
    int value = node->data;
    if (deque->front == deque->rear)
        deque->front = deque->rear = NULL;
    else
    {
        deque->front = deque->front->next;
        deque->front->prev = NULL;
    }
    (deque->size)--;
    free(node);
    return value;
}

int deleteRear(Deque *deque)
{
    if (deque->front == NULL)
        return INT_MIN;

    NODE *node = deque->rear;
    int value = node->data;
    if (deque->front == deque->rear)
        deque->front = deque->rear = NULL;
    else
    {
        deque->rear = deque->rear->prev;
        deque->rear->next = NULL;
    }
    (deque->size)--;
    free(node);
    return value;
}

int getFront(Deque *deque)
{
    if (deque->front == NULL)
        return INT_MIN;
    return deque->front->data;
}

int getRear(Deque *deque)
{
    if (deque->front == NULL)
        return INT_MIN;
    return deque->rear->data;
}

void display(Deque *deque)
{
    if (deque->front == NULL)
    {
        printf("Deque linked list is empty\n");
        return;
    }

    NODE *node = deque->front;
    while (node)
    {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

int isEmpty(Deque *deque)
{
    return deque->front == NULL;
}

int getSize(Deque *deque)
{
    return deque->size;
}

int main()
{
    Deque *deque = createDeque();
    int choice, value, res;

    while (1)
    {
        printf("\n1. Insert at Front\n2. Insert at Rear\n3. Delete at Front\n4. Delete at Rear\n5. Front\n6. Rear\n7. Display\n8. Is empty\n9. Size of\n10. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if (choice == 10)
            break;

        switch (choice)
        {
        case 1:
            printf("Enter the element to be inserted at front: ");
            scanf("%d", &value);
            insertFront(deque, value);
            break;
        case 2:
            printf("Enter the element to be inserted at rear: ");
            scanf("%d", &value);
            insertRear(deque, value);
            break;
        case 3:
            res = deleteFront(deque);
            if (res == INT_MIN)
                printf("Deque linked list is empty\n");
            else
                printf("%d is deleted in the deque linked list at the front\n", res);
            break;
        case 4:
            res = deleteRear(deque);
            if (res == INT_MIN)
                printf("Deque linked list is empty\n");
            else
                printf("%d is deleted in the deque linked list at the rear\n", res);
            break;
        case 5:
            res = getFront(deque);
            if (res == INT_MIN)
                printf("Deque linked list is empty\n");
            else
                printf("%d is at the front of the deque linked list\n", res);
            break;
        case 6:
            res = getRear(deque);
            if (res == INT_MIN)
                printf("Deque linked list is empty\n");
            else
                printf("%d is at the back of the deque linked list\n", res);
            break;
        case 7:
            display(deque);
            break;
        case 8:
            if (isEmpty(deque))
                printf("Deque linked list is empty\n");
            else
                printf("Deque linked list is not empty\n");
            break;
        case 9:
            printf("The size of the deque linked list is %d\n", getSize(deque));
            break;
        default:
            printf("Invalid choice!\n");
            break;
        }
    }

    while (deque->front)
    {
        NODE *node = deque->front;
        deque->front = deque->front->next;
        free(node);
    }
    free(deque);
    printf("Program exited!\n");
    return 0;
}