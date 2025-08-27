#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int *arr;
    int size;
    int front;
    int rear;
} Queue;

Queue *create_queue(int size)
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    if (queue == NULL)
    {
        printf("Circular queue is not created\n");
        exit(1);
    }

    queue->size = size;
    queue->arr = (int *)malloc(queue->size * sizeof(int));
    if (queue->arr == NULL)
    {
        printf("Circular queue array is not created\n");
        free(queue);
        exit(1);
    }

    queue->front = queue->rear = -1;
    printf("Circular queue array is created with size %d\n", queue->size);
    return queue;
}

void enqueue(Queue *queue, int value)
{
    if (queue->front == (queue->rear + 1) % queue->size)
        printf("Circular queue array is full, %d is not added\n", value);
    else
    {
        if (queue->front == -1)
            (queue->front)++;
        queue->rear = (queue->rear + 1) % queue->size;
        queue->arr[queue->rear] = value;
        printf("%d is added in the circular queue array\n", queue->arr[queue->rear]);
    }
}

int dequeue(Queue *queue)
{
    if (queue->front == -1)
    {
        printf("Circular queue array is empty\n");
        exit(1);
    }
    int value = queue->arr[queue->front];
    if (queue->front == queue->rear)
        queue->front = queue->rear = -1;
    else
        (queue->front) = (queue->front + 1) % (queue->size);
    return value;
}

int get_front(Queue *queue)
{
    if (queue->front == -1)
    {
        printf("Circular queue array is empty\n");
        exit(1);
    }
    return queue->arr[queue->front];
}

int get_rear(Queue *queue)
{
    if (queue->front == -1)
    {
        printf("Circular queue array is empty\n");
        exit(1);
    }
    return queue->arr[queue->rear];
}

void display(Queue *queue)
{
    int i;
    if (queue->front == -1)
    {
        printf("Circular queue array is empty\n");
        return;
    }
    i = queue->front;
    while (1)
    {
        printf("%d ", queue->arr[i]);
        if (i == queue->rear)
            break;
        i = (i + 1) % queue->size;
    }
    printf("\n");
}

int is_empty(Queue *queue)
{
    return queue->front == -1;
}

int size_of(Queue *queue)
{
    if (queue->front == -1)
        return 0;
    else
        return (queue->rear - queue->front + queue->size) % queue->size + 1;
}

int main()
{
    Queue *queue;
    int choice, size, value, res;

    printf("Enter the size of the queue array to be created: ");
    scanf("%d", &size);
    queue = create_queue(size);

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
            printf("%d is deleted in the queue array\n", res);
            break;
        case 3:
            res = get_front(queue);
            printf("%d is at the front of the queue array\n", res);
            break;
        case 4:
            res = get_rear(queue);
            printf("%d is at the back of the queue array\n", res);
            break;
        case 5:
            display(queue);
            break;
        case 6:
            if (is_empty(queue))
                printf("Queue array is empty\n");
            else
                printf("Queue array is not empty\n");
            break;
        case 7:
            res = size_of(queue);
            printf("The size of the queue array is %d\n", res);
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