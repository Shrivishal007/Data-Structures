#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int *arr;
    int size;
    int front;
    int rear;
} Deque;

Deque *create_deque(int size)
{
    Deque *deque = (Deque *)malloc(sizeof(Deque));
    if (deque == NULL)
    {
        printf("Deque is not created\n");
        exit(1);
    }

    deque->size = size;
    deque->arr = (int *)malloc(deque->size * sizeof(int));
    if (deque->arr == NULL)
    {
        printf("Deque array is not created\n");
        free(deque);
        exit(1);
    }

    deque->front = deque->rear = -1;
    printf("Deque array is created with size %d\n", deque->size);
    return deque;
}

void insert_rear(Deque *deque, int value)
{
    if ((deque->front == 0 && deque->rear == deque->size - 1) || (deque->front == deque->rear + 1))
        printf("Deque array is full, %d is not added\n", value);
    else
    {
        if (deque->front == -1)
            deque->front = deque->rear = 0;
        else if (deque->rear == deque->size - 1)
            deque->rear = 0;
        else
            (deque->rear)++;
        deque->arr[deque->rear] = value;
        printf("%d is added in the rear of deque array\n", deque->arr[deque->rear]);
    }
}

void insert_front(Deque *deque, int value)
{
    if ((deque->front == 0 && deque->rear == deque->size - 1) || (deque->front == deque->rear + 1))
        printf("Deque array is full, %d is not added\n", value);
    else
    {
        if (deque->front == -1)
            deque->front = deque->rear = 0;
        else if(deque->front == 0)
            deque->front = deque->size - 1;
        else
            (deque->front)--;
        deque->arr[deque->front] = value;
        printf("%d is added in the front of deque array\n", deque->arr[deque->front]);
    }
}

int delete_front(Deque *deque)
{
    if (deque->front == -1)
    {
        printf("Deque array is empty\n");
        exit(1);
    }

    int value = deque->arr[deque->front];
    if (deque->front == deque->rear)
        deque->front = deque->rear = -1;
    else if (deque->front == deque->size - 1)
        deque->front = 0;
    else
        (deque->front)++;
    return value;
}

int delete_rear(Deque *deque)
{
    if (deque->front == -1)
    {
        printf("Deque array is empty\n");
        exit(1);
    }

    int value = deque->arr[deque->rear];
    if (deque->front == deque->rear)
        deque->front = deque->rear = -1;
    else if (deque->rear == 0)
        deque->rear = deque->size - 1;
    else
        (deque->rear)--;
    return value;
}

int get_front(Deque *deque)
{
    if (deque->front == -1)
    {
        printf("Deque array is empty\n");
        exit(1);
    }
    return deque->arr[deque->front];
}

int get_rear(Deque *deque)
{
    if (deque->front == -1)
    {
        printf("Deque array is empty\n");
        exit(1);
    }
    return deque->arr[deque->rear];
}

void display(Deque *deque)
{
    if (deque->front == -1)
    {
        printf("Deque array is empty\n");
        return;
    }

    int i = deque->front;
    while (1)
    {
        printf("%d ", deque->arr[i]);
        if (i == deque->rear)
            break;
        i = (i + 1) % deque->size;
    }
    printf("\n");
}

int is_empty(Deque *deque)
{
    return deque->front == -1;
}

int size_of(Deque *deque)
{
    if (deque->front == -1)
        return 0;
    else if (deque->front <= deque-> rear)
        return deque->rear - deque->front + 1;
    else
        return deque->size - (deque->front - deque->rear - 1);
}

int main()
{
    Deque *deque;
    int choice, size, value, res;

    printf("Enter the size of the deque array to be created: ");
    scanf("%d", &size);
    deque = create_deque(size);

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
            printf("%d is deleted in the deque array at the front\n", res);
            break;
        case 4:
            res = delete_rear(deque);
            printf("%d is deleted in the deque array at the rear\n", res);
            break;
        case 5:
            res = get_front(deque);
            printf("%d is at the front of the deque array\n", res);
            break;
        case 6:
            res = get_rear(deque);
            printf("%d is at the back of the deque array\n", res);
            break;
        case 7:
            display(deque);
            break;
        case 8:
            if (is_empty(deque))
                printf("Deque array is empty\n");
            else
                printf("Deque array is not empty\n");
            break;
        case 9:
            res = size_of(deque);
            printf("The size of the deque array is %d\n", res);
            break;
        default:
            printf("Invalid choice!\n");
            break;
        }
    }

    free(deque->arr);
    free(deque);
    printf("Program exited!\n");
    return 0;
}