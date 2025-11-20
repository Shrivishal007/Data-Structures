#include <stdio.h>
#include <stdlib.h>

typedef struct NODE
{
    struct NODE *prev;
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
        end = start->prev;

        node->prev = end;
        node->next = start;

        end->next = node;
        start->prev = node;
    }
    else
    {
        start = node;
        node->prev = node;
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
        end = start->prev;

        node->prev = end;
        node->next = start;

        start->prev = node;
        start = node;
        end->next = start;
    }
    else
    {
        start = node;
        node->prev = node;
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
    end = start->prev;

    if (start != start->next)
    {   
        start = start->next;
        end->next = start;
        start->prev = end;
    }
    else
        start = NULL;
    free(node);
    count--;
    printf("%d is deleted at the start of the circular doubly linked list\n", value);
}

void removeEnd()
{
    if (start == NULL)
    {
        printf("Circular doubly Linked list is empty\n");
        return;
    }

    NODE *node = start->prev;
    int value = node->data;
    if (start != start->next)
    {
        start->prev = node->prev;
        node->prev->next = start;
    }
    else
        start = NULL;
    free(node);
    count--;
    printf("%d is deleted at the end of the circular doubly linked list\n", value);
}

void insertAt(int position, int value)
{
    NODE *node, *ptr = start;
    if (position < 0 || position > count)
    {
        printf("Out of Range\n");
        return;
    }
    if (position == 0)
    {
        addStart(value);
        return;
    }

    else if (position == count)
    {
        addEnd(value);
        return;
    }

    else
    {
        node = (NODE *)malloc(sizeof(NODE));
        if (node == NULL)
        {
            printf("Node is not created\n");
            exit(1);
        }

        node->data = value;
        for (int i = 0; i < position - 1; i++)
            ptr = ptr->next;
        node->next = ptr->next;
        node->prev = ptr;
        ptr->next->prev = node;
        ptr->next = node;
        count++;
    }
    
    printf("%d is inserted in the index position %d of the circular doubly linked list\n", value, position);
}

void deleteAt(int index)
{
    int value;
    NODE *node, *ptr = start;
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
        removeStart();
        return;
    }

    else if (index == count - 1)
    {
        removeEnd();
        return;
    }

    else
    {
        if (index < count / 2)
            for (int i = 0; i < index; i++)
                ptr = ptr->next;
        else
        {
            ptr = start->prev;
            for (int i = count - 1; i > index; i--)
                ptr = ptr->prev;
        }

        node = ptr;
        value = node->data;

        node->prev->next = node->next;
        node->next->prev = node->prev;
        
        free(node);
        count--;
    }
    
    printf("%d is deleted in the circular doubly linked list at index position %d\n", value, index);
}

void display()
{
    if (start == NULL)
    {
        printf("Circular doubly linked list is empty\n");
        return;
    }

    NODE *node = start;
    do
    {
        printf("%d ", node->data);
        node = node->next;
    } while (node != start);
    printf("\n");
}

void reverseDisplay()
{
    if (start == NULL)
    {
        printf("Circular doubly linked list is empty\n");
        return;
    }

    NODE *node = start->prev;
    do
    {
        printf("%d ", node->data);
        node = node->prev;
    } while (node != start->prev);
    printf("\n");
}

int main()
{
    int choice, position, value;
    while (1)
    {
        printf("\n1. Add at Start\n2. Add at End\n3. Delete at Start\n4. Delete at End\n5. Insert\n6. Delete\n7. Display\n8. Reverse Display\n9. Size of\n10. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if (choice == 10)
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
            scanf("%d", &position);
            printf("Enter the element to be inserted: ");
            scanf("%d", &value);
            insertAt(position, value);
            break;
        case 6:
            printf("Enter the index position of the element to be deleted: ");
            scanf("%d", &position);
            deleteAt(position);
            break;
        case 7:
            display();
            break;
        case 8:
            reverseDisplay();
            break;
        case 9:
            printf("The size of the circular doubly linked list is %d\n", count);
            break;
        default:
            printf("Invalid choice!\n");
            break;
        }
    }

    if (start != NULL)
    {
        NODE *current = start;
        current->prev->next = NULL;

        while (current)
        {
            NODE *temp = current;
            current = current->next;
            free(temp);
        }
    }    
    printf("Program exited!\n");
    return 0;
}