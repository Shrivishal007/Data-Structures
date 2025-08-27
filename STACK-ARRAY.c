#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int *arr;
    int size;
    int top;
} Stack;

Stack *create_stack(int size)
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    if (stack == NULL)
    {
        printf("Stack is not created\n");
        exit(1);
    }

    stack->size = size;
    stack->arr = (int *)malloc(stack->size * sizeof(int));
    if (stack->arr == NULL)
    {
        printf("Stack array is not created\n");
        free(stack);
        exit(1);
    }

    stack->top = -1;
    printf("Stack array is created with size %d\n", stack->size);
    return stack;
}

void push(Stack *stack, int value)
{
    if (stack->top >= stack->size - 1)
        printf("Stack array is full, %d is not added\n", value);
    else
    {
        stack->arr[++(stack->top)] = value;
        printf("%d is added in the stack array\n", stack->arr[stack->top]);
    }
}

int pop(Stack *stack)
{
    if (stack->top == -1)
    {
        printf("Error: Stack is empty\n");
        exit(1);
    }

    return stack->arr[stack->top--];
}

int peek(Stack *stack)
{
    if (stack->top == -1)
    {
        printf("Error: Stack is empty\n");
        exit(1);
    }

    return stack->arr[stack->top];
}

void display(Stack *stack)
{
    if (stack->top == -1)
    {
        printf("Stack array is empty\n");
        return;
    }
    for (int i = stack->top; i >= 0; i--)
        printf("%d ", stack->arr[i]);
    printf("\n");
}

int is_empty(Stack *stack)
{
    return (stack->top == -1);
}

int size_of(Stack *stack)
{
    return stack->top + 1;
}

int main()
{
    Stack *stack;
    int choice, size, value, res;

    printf("Enter the size of the stack array to be created: ");
    scanf("%d", &size);
    stack = create_stack(size);

    while (1)
    {
        printf("\n1. Push\n2. Pop\n3. Peek\n4. Display\n5. Is empty\n6. Size of\n7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if (choice == 7)
            break;

        switch (choice)
        {
        case 1:
            printf("Enter the element to be pushed: ");
            scanf("%d", &value);
            push(stack, value);
            break;
        case 2:
            res = pop(stack);
            printf("%d is deleted in the stack array\n", res);
            break;
        case 3:
            res = peek(stack);
            printf("%d is on top of the stack array\n", res);
            break;
        case 4:
            display(stack);
            break;
        case 5:
            if (is_empty(stack))
                printf("Stack array is empty\n");
            else
                printf("Stack array is not empty\n");
            break;
        case 6:
            res = size_of(stack);
            printf("The size of the stack array is %d\n", res);
            break;
        default:
            printf("Invalid choice!\n");
            break;
        }
    }

    free(stack->arr);
    free(stack);
    printf("Program exited!\n");
    return 0;
}