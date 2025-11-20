#include <stdio.h>
#include <stdlib.h>

typedef struct NODE
{
    struct NODE *prev;
    int data;
    struct NODE *next;
} NODE;

NODE *head = NULL, *tail = NULL;
int count = 0;

void addTail(int value)
{
    NODE *node = (NODE *)malloc(sizeof(NODE));
    if (node == NULL)
    {
        printf("Node is not created\n");
        exit(1);
    }

    node->data = value;
    node->prev = tail;
    node->next = NULL;
    if (head == NULL)
        head = node;
    else
        tail->next = node;
    tail = node;
    count++;
    printf("%d is added at the tail of the doubly linked list\n", value);
}

void addHead(int value)
{
    NODE *node = (NODE *)malloc(sizeof(NODE));
    if (node == NULL)
    {
        printf("Node is not created\n");
        exit(1);
    }

    node->data = value;
    node->next = head;
    node->prev = NULL;
    if (head == NULL)
        tail = node;
    else
        head->prev = node;
    head = node;
    count++;
    printf("%d is added at the head of the doubly linked list\n", value);
}

void removeHead()
{
    NODE *node = head;
    int value;
    if (head == NULL)
    {
        printf("Doubly Linked list is empty\n");
        return;
    }

    value = node->data;
    head = head->next;
    if (head != NULL)
        head->prev = NULL;
    else
        tail = NULL;
    free(node);
    count--;
    printf("%d is deleted at the head of the doubly linked list\n", value);
}

void removeTail()
{
    NODE *node = tail;
    int value;
    if (head == NULL)
    {
        printf("Doubly Linked list is empty\n");
        return;
    }

    value = node->data;
    tail = tail->prev;
    if (tail != NULL)
        tail->next = NULL;
    else
        head = NULL;
    free(node);
    count--;
    printf("%d is deleted at the tail of the doubly linked list\n", value);
}

void insertAt(int position, int value)
{
    NODE *node, *ptr = head;
    if (position < 0 || position > count)
    {
        printf("Out of Range\n");
        return;
    }

    if (position == 0)
    {
        addHead(value);
        return;
    }

    else if (position == count)
    {
        addTail(value);
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
        if (position < count / 2)
            for (int i = 0; i < position; i++)
                ptr = ptr->next;
        else
        {
            ptr = tail;
            for (int i = count - 1; i > position; i--)
                ptr = ptr->prev;
        }

        node->next = ptr;
        node->prev = ptr->prev;

        ptr->prev->next = node;
        ptr->prev = node;
        count++;
    }

    printf("%d is inserted in the index position %d of the doubly linked list\n", value, position);
}

void deleteAt(int index)
{
    int value;
    NODE *node, *ptr = head;
    if (head == NULL)
    {
        printf("Doubly Linked list is empty\n");
        return;
    }

    if (index < 0 || index >= count)
    {
        printf("Out of Range\n");
        return;
    }

    if (index == 0)
    {
        removeHead();
        return;
    }

    else if (index == count - 1)
    {
        removeTail();
        return;
    }

    else
    {
        if (index < count / 2)
            for (int i = 0; i < index; i++)
                ptr = ptr->next;
        else
        {
            ptr = tail;
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
    
    printf("%d is deleted in the doubly linked list at index position %d\n", value, index);
}

void display()
{
    NODE *node = head;
    if (head == NULL)
    {
        printf("Doubly linked list is empty\n");
        return;
    }
    while (node)
    {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

void reverseDisplay()
{
    NODE *node = tail;
    if (head == NULL)
    {
        printf("Doubly linked list is empty\n");
        return;
    }
    while (node)
    {
        printf("%d ", node->data);
        node = node->prev;
    }
    printf("\n");
}

int main()
{
    int choice, position, value;
    while (1)
    {
        printf("\n1. Add at Front\n2. Add at Rear\n3. Delete at Front\n4. Delete at Rear\n5. Insert\n6. Delete\n7. Display\n8. Reverse Display\n9. Size of\n10. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if (choice == 10)
            break;

        switch (choice)
        {
        case 1:
            printf("Enter the element to be added at the head: ");
            scanf("%d", &value);
            addHead(value);
            break;
        case 2:
            printf("Enter the element to be added at the tail: ");
            scanf("%d", &value);
            addTail(value);
            break;
        case 3:
            removeHead();
            break;
        case 4:
            removeTail();
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
            printf("The size of the doubly linked list is %d\n", count);
            break;
        default:
            printf("Invalid choice!\n");
            break;
        }
    }

    while (head)
    {
        NODE *node = head;
        head = head->next;
        free(node);
    }
    printf("Program exited!\n");
    return 0;
}