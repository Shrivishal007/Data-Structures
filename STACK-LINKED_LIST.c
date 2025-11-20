#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct NODE
{
    int data;
    struct NODE *next;
} NODE;

typedef struct
{
    NODE *top;
    int size;
} Stack;

Stack *createStack()
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    if (stack == NULL)
    {
        printf("Stack is not created\n");
        exit(1);
    }

    stack->top = NULL;
    stack->size = 0;
    return stack;
}

void push(Stack *stack, int value)
{
    NODE *stackNode = (NODE *)malloc(sizeof(NODE));
    if (stackNode == NULL)
    {
        printf("Node is not created\n");
        exit(1);
    }

    stackNode->data = value;
    stackNode->next = stack->top;
    stack->top = stackNode;
    (stack->size)++;
    printf("%d is added in the stack linked list\n", stack->top->data);
}

int pop(Stack *stack)
{
    if (stack->top == NULL)
        return INT_MIN;

    NODE *node = stack->top;
    int value = node->data;
    stack->top = stack->top->next;
    free(node);
    (stack->size)--;
    return value;
}

int peek(Stack *stack)
{
    if (stack->top == NULL)
        return INT_MIN;
    return stack->top->data;
}

void display(Stack *stack)
{
    NODE *node = stack->top;
    if (stack->top == NULL)
    {
        printf("Stack linked list is empty\n");
        return;
    }
    while (node)
    {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

int isEmpty(Stack *stack)
{
    return (stack->top == NULL);
}

int getSize(Stack *stack)
{
    return stack->size;
}

int main()
{
    Stack *stack = createStack();
    int choice, value, res;

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
            if (res == INT_MIN)
                printf("Error: Stack is empty\n");
            else
                printf("%d is deleted in the stack linked list\n", res);
            break;
        case 3:
            res = peek(stack);
            if (res == INT_MIN)
                printf("Error: Stack is empty\n");
            else
                printf("%d is on top of the stack linked list\n", res);
            break;
        case 4:
            display(stack);
            break;
        case 5:
            if (isEmpty(stack))
                printf("Stack is empty\n");
            else
                printf("Stack is not empty\n");
            break;
        case 6:
            printf("The size of the stack linked list is %d\n", getSize(stack));
            break;
        default:
            printf("Invalid choice!\n");
            break;
        }
    }

    while (stack->top)
    {
        NODE *node = stack->top;
        stack->top = stack->top->next;
        free(node);
    }
    free(stack);
    printf("Program exited!\n");
    return 0;
}