#include <stdio.h>
#include <stdlib.h>

typedef struct NODE
{
    int data;
    struct NODE *next;
} NODE;

typedef struct
{
    NODE *front;
    NODE *rear;
    int size;
} Queue;

Queue *create_queue()
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    if (queue == NULL)
    {
        printf("Queue is not created\n");
        exit(1);
    }

    queue->front = queue->rear = NULL;
    queue->size = 0;
    return queue;
}

void enqueue(Queue *queue, int value)
{
    NODE *newNode = (NODE *)malloc(sizeof(NODE));
    if (newNode == NULL)
    {
        printf("Node is not created\n");
        exit(1);
    }

    newNode->data = value;
    newNode->next = NULL;

    if (queue->front == NULL)
        queue->front = newNode;
    else
        queue->rear->next = newNode;
    queue->rear = newNode;
    (queue->size)++;
    printf("%d is added in the queue linked list\n", queue->rear->data);
}

int dequeue(Queue *queue)
{
    NODE *node;
    int value;
    if (queue->front == NULL)
    {
        printf("Queue linked list is empty\n");
        exit(1);
    }

    node = queue->front;
    value = node->data;
    if (queue->front == queue->rear)
        queue->front = queue->rear = NULL;
    else
        queue->front = queue->front->next;
    (queue->size)--;
    free(node);
    return value;
}

int get_front(Queue *queue)
{
    if (queue->front == NULL)
    {
        printf("Queue linked list is empty\n");
        exit(1);
    }
    return queue->front->data;
}

int get_rear(Queue *queue)
{
    if (queue->front == NULL)
    {
        printf("Queue linked list is empty\n");
        exit(1);
    }
    return queue->rear->data;
}

void display(Queue *queue)
{
    NODE *node;
    if (queue->front == NULL)
    {
        printf("Queue linked list is empty\n");
        return;
    }

    node = queue->front;
    while (node != NULL)
    {
        printf("%d ", node->data);
        node = node->next;
    }    
    printf("\n");
}

int is_empty(Queue *queue)
{
    return queue->front == NULL;
}

int size_of(Queue *queue)
{
    return queue->size;
}

int main()
{
    Queue *queue = create_queue();
    int choice, value, res;

    while (1)
    {
        printf("\n1. Enqueue\n2. Dequeue\n3. Front\n4. Rear\n5. Display\n6. Is empty\n7. Size of\n8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if (choice == 8)
            break;

        switch (choice)
        {
        case 1:
            printf("Enter the element to be inserted: ");
            scanf("%d", &value);
            enqueue(queue, value);
            break;
        case 2:
            res = dequeue(queue);
            printf("%d is deleted in the queue linked list\n", res);
            break;
        case 3:
            res = get_front(queue);
            printf("%d is at the front of the queue linked list\n", res);
            break;
        case 4:
            res = get_rear(queue);
            printf("%d is at the back of the queue linked list\n", res);
            break;
        case 5:
            display(queue);
            break;
        case 6:
            if (is_empty(queue))
                printf("Queue linked list is empty\n");
            else
                printf("Queue linked list is not empty\n");
            break;
        case 7:
            res = size_of(queue);
            printf("The size of the queue linked list is %d\n", res);
            break;
        default:
            printf("Invalid choice!\n");
            break;
        }
    }

    while (queue->front != NULL)
    {
        NODE *node = queue->front;
        queue->front = queue->front->next;
        free(node);
    }
    free(queue);
    printf("Program exited!\n");
    return 0;
}