#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct
{
    int *arr;
    int size;
    int front;
    int rear;
} Queue;

Queue *createQueue(int size)
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    if (queue == NULL)
    {
        printf("Queue is not created\n");
        exit(1);
    }

    queue->size = size;
    queue->arr = (int *)malloc(queue->size * sizeof(int));
    if (queue->arr == NULL)
    {
        printf("Queue array is not created\n");
        free(queue);
        exit(1);
    }

    queue->front = queue->rear = -1;
    printf("Queue array is created with size %d\n", queue->size);
    return queue;
}

void enqueue(Queue *queue, int value)
{
    if (queue->rear == queue->size - 1)
        printf("Queue array is full, %d is not added\n", value);
    else
    {
        if (queue->front == -1)
            (queue->front)++;
        queue->arr[++(queue->rear)] = value;
        printf("%d is added in the queue array\n", queue->arr[queue->rear]);
    }
}

int dequeue(Queue *queue)
{
    if (queue->front == -1)
        return INT_MIN;

    int value = queue->arr[queue->front];
    if (queue->front == queue->rear)
        queue->front = queue->rear = -1;
    else
        (queue->front)++;
    return value;
}

int getFront(Queue *queue)
{
    if (queue->front == -1)
        return INT_MIN;
    return queue->arr[queue->front];
}

int getRear(Queue *queue)
{
    if (queue->front == -1)
        return INT_MIN;
    return queue->arr[queue->rear];
}

void display(Queue *queue)
{
    if (queue->front == -1)
    {
        printf("Queue array is empty\n");
        return;
    }
    for (int i = queue->front; i <= queue->rear; i++)
        printf("%d ", queue->arr[i]);
    printf("\n");
}

int isEmpty(Queue *queue)
{
    return queue->front == -1;
}

int getSize(Queue *queue)
{
    if (queue->front == -1)
        return 0;
    else
        return queue->rear - queue->front + 1;
}

int main()
{
    Queue *queue;
    int choice, size, value, res;

    printf("Enter the size of the queue array to be created: ");
    scanf("%d", &size);
    queue = createQueue(size);

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
            if (res == INT_MIN)
                printf("Queue array is empty\n");
            else
                printf("%d is deleted in the queue array\n", res);
            break;
        case 3:
            res = getFront(queue);
            if (res == INT_MIN)
                printf("Queue array is empty\n");
            else
                printf("%d is at the front of the queue array\n", res);
            break;
        case 4:
            res = getRear(queue);
            if (res == INT_MIN)
                printf("Queue array is empty\n");
            else
                printf("%d is at the back of the queue array\n", res);
            break;
        case 5:
            display(queue);
            break;
        case 6:
            if (isEmpty(queue))
                printf("Queue array is empty\n");
            else
                printf("Queue array is not empty\n");
            break;
        case 7:
            printf("The size of the queue array is %d\n", getSize(queue));
            break;
        default:
            printf("Invalid choice!\n");
            break;
        }
    }

    free(queue->arr);
    free(queue);
    printf("Program exited!\n");
    return 0;
}