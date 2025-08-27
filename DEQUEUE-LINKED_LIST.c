#include <stdio.h>
#include <stdlib.h>

typedef struct NODE
{
    int data;
    struct NODE *previous;
    struct NODE *next;
} NODE;

typedef struct
{
    int size;
    NODE *front;
    NODE *rear;
} Deque;

Deque *create_deque()
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

void insert_rear(Deque *deque, int value)
{
    NODE *newNode = (NODE *)malloc(sizeof(NODE));
    if (newNode == NULL)
    {
        printf("Node is not created\n");
        exit(1);
    }

    newNode->data = value;
    newNode->previous = deque->rear;
    newNode->next = NULL;
    if (deque->front == NULL)
        deque->front = newNode;
    else
        deque->rear->next = newNode;
    deque->rear = newNode;
    (deque->size)++;
    printf("%d is added in the rear of deque linked list\n", deque->rear->data);
}

void insert_front(Deque *deque, int value)
{
    NODE *newNode = (NODE *)malloc(sizeof(NODE));
    if (newNode == NULL)
    {
        printf("Node is not created\n");
        exit(1);
    }

    newNode->data = value;
    newNode->next = deque->front;
    newNode->previous = NULL;
    if (deque->front == NULL)
        deque->rear = newNode;
    else
        deque->front->previous = newNode;
    deque->front = newNode;
    (deque->size)++;
    printf("%d is added in the front of deque linked list\n", deque->front->data);
}

int delete_front(Deque *deque)
{
    if (deque->front == NULL)
    {
        printf("Deque linked list is empty\n");
        exit(1);
    }

    NODE *node = deque->front;
    int value = node->data;
    if (deque->front == deque->rear)
        deque->front = deque->rear = NULL;
    else
    {
        deque->front = deque->front->next;
        deque->front->previous = NULL;
    }
    (deque->size)--;
    free(node);
    return value;
}

int delete_rear(Deque *deque)
{
    if (deque->front == NULL)
    {
        printf("Deque linked list is empty\n");
        exit(1);
    }

    NODE *node = deque->rear;
    int value = node->data;
    if (deque->front == deque->rear)
        deque->front = deque->rear = NULL;
    else
    {
        deque->rear = deque->rear->previous;
        deque->rear->next = NULL;
    }
    (deque->size)--;
    free(node);
    return value;
}

int get_front(Deque *deque)
{
    if (deque->front == NULL)
    {
        printf("Deque linked list is empty\n");
        exit(1);
    }
    return deque->front->data;
}

int get_rear(Deque *deque)
{
    if (deque->front == NULL)
    {
        printf("Deque linked list is empty\n");
        exit(1);
    }
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
    while (node != NULL)
    {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

int is_empty(Deque *deque)
{
    return deque->front == NULL;
}

int size_of(Deque *deque)
{
    return deque->size;
}

int main()
{
    Deque *deque = create_deque();
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
            insert_front(deque, value);
            break;
        case 2:
            printf("Enter the element to be inserted at rear: ");
            scanf("%d", &value);
            insert_rear(deque, value);
            break;
        case 3:
            res = delete_front(deque);
            printf("%d is deleted in the deque linked list at the front\n", res);
            break;
        case 4:
            res = delete_rear(deque);
            printf("%d is deleted in the deque linked list at the rear\n", res);
            break;
        case 5:
            res = get_front(deque);
            printf("%d is at the front of the deque linked list\n", res);
            break;
        case 6:
            res = get_rear(deque);
            printf("%d is at the back of the deque linked list\n", res);
            break;
        case 7:
            display(deque);
            break;
        case 8:
            if (is_empty(deque))
                printf("Deque linked list is empty\n");
            else
                printf("Deque linked list is not empty\n");
            break;
        case 9:
            res = size_of(deque);
            printf("The size of the deque linked list is %d\n", res);
            break;
        default:
            printf("Invalid choice!\n");
            break;
        }
    }

    while (deque->front != NULL)
    {
        NODE *node = deque->front;
        deque->front = deque->front->next;
        free(node);
    }
    free(deque);
    printf("Program exited!\n");
    return 0;
}