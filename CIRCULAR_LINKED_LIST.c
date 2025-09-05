#include <stdio.h>
#include <stdlib.h>

typedef struct NODE
{
    int data;
    struct NODE *next;
} NODE;

NODE *start = NULL, *end = NULL;
int count = 0;

void addStart(int value)
{
    NODE *node = (NODE *)malloc(sizeof(NODE));
    if (node == NULL)
    {
        printf("Node is not created\n");
        exit(1);
    }

    node->data = value;
    if (start == NULL)
    {
        node->next = node;
        start = end = node;
    } 
    else
    {
        node->next = start;
        start = node;
        end->next = start;
    }
    count++;
    printf("%d is added to the start of the circular linked list\n", value);
}

void addEnd(int value)
{
    NODE *node = malloc(sizeof(NODE));
    if (node == NULL)
    {
        printf("Node is not created\n");
        exit(1);
    }

    node->data = value;

    if (start == NULL)
    {
        node->next = node;
        start = end = node;
    }
    else
    {
        node->next = start;
        end->next = node;
        end = node;
    }
    count++;
    printf("%d is added to the end of the circular linked list\n", value);
}


void removeStart()
{
    if (start == NULL)
    {
        printf("Linked list is empty\n");
        return;
    }
    NODE *node = start;
    int value = node->data;

    if (start != end)
    {
        start = start->next;
        end->next = start;
    }
    else
        start = end = NULL;
    free(node);
    count--;
    printf("%d is deleted from the circular linked list\n", value);
}

void insert(int position, int value)
{
    NODE *node, *ptr = start;
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
        if (start == NULL)
        {
            node->next = node;
            start = end = node;
        } 
        else
        {
            node->next = start;
            start = node;
            end->next = start;
        }
    }

    else if (position == count)
    {
        node->next = start;
        end->next = node;
        end = node;
    }

    else
    {
        for (int i = 0; i < position - 1; i++)
            ptr = ptr->next;
        node->next = ptr->next;
        ptr->next = node;
    }
    count++;
    printf("%d is inserted in the index position %d of the circular linked list\n", value, position);
}

void delete_at(int index)
{
    int value;
    NODE *node, *ptr = start;
    if (start == NULL)
    {
        printf("Linked list is empty\n");
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
        if (start != end)
        {
            start = start->next;
            end->next = start;
        }
        else
            start = end = NULL;
        free(node);
    }

    else
    {
        for (int i = 0; i < index - 1; i++)
            ptr = ptr->next;
        node = ptr->next;
        value = node->data;
        ptr->next = node->next;
        if (node == end)
            end = ptr;
        free(node);
    }
    count--;
    printf("%d is deleted in the linked list at index position %d\n", value, index);
}

void display()
{
    NODE *node = start;
    if (start == NULL)
    {
        printf("Linked list is empty\n");
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

int size_of()
{
    return count;
}

int main()
{
    int choice, pos, value;
    while (1)
    {
        printf("\n1. Add at Start\n2. Add at End\n3. Delete at Start\n4. Insert\n5. Delete\n6. Display\n7. Size of\n8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if (choice == 8)
            break;

        switch (choice)
        {
        case 1:
            printf("Enter the element to be added: ");
            scanf("%d", &value);
            addStart(value);
            break;
        case 2:
            printf("Enter the element to be added: ");
            scanf("%d", &value);
            addEnd(value);
            break;
        case 3:
            removeStart();
            break;
        case 4:
            printf("Enter the index position of the element to be inserted: ");
            scanf("%d", &pos);
            printf("Enter the element to be inserted: ");
            scanf("%d", &value);
            insert(pos, value);
            break;
        case 5:
            printf("Enter the index position of the element to be deleted: ");
            scanf("%d", &pos);
            delete_at(pos);
            break;
        case 6:
            display();
            break;
        case 7:
            printf("The size of the circular linked list is %d\n", size_of());
            break;
        default:
            printf("Invalid choice!\n");
            break;
        }
    }

    if (start != NULL)
        end->next = NULL;
    while (start)
    {
        NODE *node = start;
        start = start->next;
        free(node);
    }
    printf("Program exited!\n");
    return 0;
}