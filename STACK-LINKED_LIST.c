#include <stdio.h>
#include <stdlib.h>

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

Stack *create_stack()
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
    {
        printf("Error: Stack is empty\n");
        exit(1);
    }

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
    {
        printf("Error: Stack is empty\n");
        exit(1);
    }

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

int is_empty(Stack *stack)
{
    return (stack->top == NULL);
}

int size_of(Stack *stack)
{
    return stack->size;
}

int main()
{
    Stack *stack = create_stack();
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
            printf("%d is deleted in the stack linked list\n", res);
            break;
        case 3:
            res = peek(stack);
            printf("%d is on top of the stack linked list\n", res);
            break;
        case 4:
            display(stack);
            break;
        case 5:
            if (is_empty(stack))
                printf("Stack is empty\n");
            else
                printf("Stack is not empty\n");
            break;
        case 6:
            res = size_of(stack);
            printf("The size of the stack linked list is %d\n", res);
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