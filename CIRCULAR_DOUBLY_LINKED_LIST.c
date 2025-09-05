#include <stdio.h>
#include <stdlib.h>

typedef struct NODE
{
    struct NODE *previous;
    int data;
    struct NODE *next;
} NODE;

NODE *start = NULL;
int count = 0;

void addEnd(int value)
{
    NODE *node = (NODE *)malloc(sizeof(NODE)), *end;
    if (node == NULL)
    {
        printf("Node is not created\n");
        exit(1);
    }

    node->data = value;
    if(start != NULL)
    {
        end = start->previous;

        node->previous = end;
        node->next = start;

        end->next = node;
        start->previous = node;
    }
    else
    {
        start = node;
        node->previous = node;
        node->next = node;
    }

    count++;
    printf("%d is added at the end of the circular doubly linked list\n", value);
}

void addStart(int value)
{
    NODE *node = (NODE *)malloc(sizeof(NODE)), *end;
    if (node == NULL)
    {
        printf("Node is not created\n");
        exit(1);
    }

    node->data = value;
    if(start != NULL)
    {
        end = start->previous;

        node->previous = end;
        node->next = start;

        start->previous = node;
        start = node;
        end->next = start;
    }
    else
    {
        start = node;
        node->previous = node;
        node->next = node;
    }

    count++;
    printf("%d is added at the start of the circular doubly linked list\n", value);
}

void removeStart()
{
    NODE *node = start, *end;
    int value;
    if (start == NULL)
    {
        printf("Circular doubly Linked list is empty\n");
        return;
    }

    value = node->data;
    end = start->previous;

    if (start != start->next)
    {   
        start = start->next;
        end->next = start;
        start->previous = end;
    }
    else
        start = NULL;
    free(node);
    count--;
    printf("%d is deleted at the start of the circular doubly linked list\n", value);
}

void removeEnd()
{
    NODE *node = start->previous;
    int value;
    if (start == NULL)
    {
        printf("Circular doubly Linked list is empty\n");
        return;
    }

    value = node->data;
    if (start != start->next)
    {
        start->previous = node->previous;
        node->previous->next = start;
    }
    else
        start = NULL;
    free(node);
    count--;
    printf("%d is deleted at the end of the circular doubly linked list\n", value);
}

void insert(int position, int value)
{
    NODE *node, *ptr = start, *end;
    if (position < 0 || position > count)
    {
        printf("Out of Range\n");
        return;
    }

    node = (NODE *)malloc(sizeof(NODE));
    if (node == NULL)
    {
        printf("Node is not created\n");
        exit(1);
    }

    node->data = value;
    if (position == 0)
    {
        if (start != NULL)
        {
            end = start->previous;

            node->previous = end;
            node->next = start;

            start->previous = node;
            start = node;
            end->next = start;
        }
        else
        {
            start = node;
            node->previous = node;
            node->next = node;
        }
    }

    else if (position == count)
    {
        end = start->previous;

        node->previous = end;
        node->next = start;

        end->next = node;
        start->previous = node;
    }

    else
    {
        for (int i = 0; i < position - 1; i++)
            ptr = ptr->next;
        node->next = ptr->next;
        node->previous = ptr;
        ptr->next->previous = node;
        ptr->next = node;
    }
    count++;
    printf("%d is inserted in the index position %d of the circular doubly linked list\n", value, position);
}

void delete_at(int index)
{
    int value;
    NODE *node, *ptr = start, *end;
    if (start == NULL)
    {
        printf("Circular doubly linked list is empty\n");
        return;
    }

    if (index < 0 || index >= count)
    {
        printf("Out of Range\n");
        return;
    }

    if (index == 0)
    {
        node = start;
        value = node->data;
        end = start->previous;

        if (start != start->next)
        {   
            start = start->next;
            end->next = start;
            start->previous = end;
        }
        else
            start = NULL;
        
        free(node);
    }

    else if (index == count - 1)
    {
        node = start->previous;
        value = node->data;
        if (start != start->next)
        {
            start->previous = node->previous;
            node->previous->next = start;
        }
        else
            start = NULL;
        free(node);
    }

    else
    {
        if (index < count / 2)
            for (int i = 0; i < index; i++)
                ptr = ptr->next;
        else
        {
            ptr = start->previous;
            for (int i = count - 1; i > index; i--)
                ptr = ptr->previous;
        }

        node = ptr;
        value = node->data;

        node->previous->next = node->next;
        node->next->previous = node->previous;
        
        free(node);
    }
    count--;
    printf("%d is deleted in the circular doubly linked list at index position %d\n", value, index);
}

void display()
{
    NODE *node = start;
    if (start == NULL)
    {
        printf("Circular linked list is empty\n");
        return;
    }
    while (1)
    {
        printf("%d ", node->data);
        node = node->next;
        if(node == start)
            break;
    }
    printf("\n");
}

void reverse_display()
{
    NODE *node = start->previous;
    if (start == NULL)
    {
        printf("Circular linked list is empty\n");
        return;
    }
    while (1)
    {
        printf("%d ", node->data);
        node = node->previous;
        if(node == start->previous)
            break;
    }
    printf("\n");
}

int main()
{
    int choice, pos, value;
    while (1)
    {
        printf("\n1. Add at Start\n2. Add at End\n3. Delete at Start\n4. Delete at End\n5. Insert\n6. Delete\n7. Display\n8. Reverse Display\n9. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if (choice == 9)
            break;

        switch (choice)
        {
        case 1:
            printf("Enter the element to be added at the start: ");
            scanf("%d", &value);
            addStart(value);
            break;
        case 2:
            printf("Enter the element to be added at the end: ");
            scanf("%d", &value);
            addEnd(value);
            break;
        case 3:
            removeStart();
            break;
        case 4:
            removeEnd();
            break;
        case 5:
            printf("Enter the index position of the element to be inserted: ");
            scanf("%d", &pos);
            printf("Enter the element to be inserted: ");
            scanf("%d", &value);
            insert(pos, value);
            break;
        case 6:
            printf("Enter the index position of the element to be deleted: ");
            scanf("%d", &pos);
            delete_at(pos);
            break;
        case 7:
            display();
            break;
        case 8:
            reverse_display();
            break;
        default:
            printf("Invalid choice!\n");
            break;
        }
    }

    if (start != NULL)
        start->previous->next = NULL;
    while (start)
    {
        NODE *node = start;
        start = start->next;
        free(node);
    }
    printf("Program exited!\n");
    return 0;
}