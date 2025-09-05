#include <stdio.h>
#include <stdlib.h>

typedef struct NODE
{
    int data;
    struct NODE *next;
} NODE;

NODE *head = NULL, *tail = NULL;
int count = 0;

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
    head = node;
    if (tail == NULL)
        tail = node;
    count++;
    printf("%d is added to the linked list\n", value);
}

void addTail(int value)
{
    NODE *node = (NODE *)malloc(sizeof(NODE));
    if (node == NULL)
    {
        printf("Node is not created\n");
        exit(1);
    }

    node->data = value;
    node->next = NULL;
    if (tail != NULL)
        tail->next = node;
    tail = node;
    if (head == NULL)
        head = node;
    count++;
    printf("%d is added to the linked list\n", value);
}

void removeHead()
{
    if (head == NULL)
    {
        printf("Linked list is empty\n");
        return;
    }
    NODE *node = head;
    int value = node->data;
    head = head->next;
    if (head == NULL)
        tail = NULL;
    free(node);
    count--;
    printf("%d is deleted from the linked list\n", value);
}

void insert(int position, int value)
{
    NODE *node, *ptr = head;
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
        node->next = head;
        head = node;
        if (tail == NULL)
            tail = node;
    }

    else if (position == count)
    {
        node->next = NULL;
        tail->next = node;
        tail = node;
    }

    else
    {
        for (int i = 0; i < position - 1; i++)
            ptr = ptr->next;
        node->next = ptr->next;
        ptr->next = node;
    }
    count++;
    printf("%d is inserted in the index position %d of the linked list\n", value, position);
}

void delete_at(int index)
{
    int value;
    NODE *node, *ptr = head;
    if (head == NULL)
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
        node = head;
        value = node->data;
        head = head->next;
        if (head == NULL)
            tail = NULL;
        free(node);
    }

    else
    {
        for (int i = 0; i < index - 1; i++)
            ptr = ptr->next;
        node = ptr->next;
        value = node->data;
        ptr->next = node->next;
        if (node == tail)
            tail = ptr;
        free(node);
    }
    count--;
    printf("%d is deleted in the linked list at index position %d\n", value, index);
}

void display()
{
    NODE *node = head;
    if (head == NULL)
    {
        printf("Linked list is empty\n");
        return;
    }
    while (node)
    {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}

int main()
{
    int choice, pos, value;
    while (1)
    {
        printf("\n1. Add at Head\n2. Add at Tail\n3. Delete at Head\n4. Insert\n5. Delete\n6. Display\n7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if (choice == 7)
            break;

        switch (choice)
        {
        case 1:
            printf("Enter the element to be added: ");
            scanf("%d", &value);
            addHead(value);
            break;
        case 2:
            printf("Enter the element to be added: ");
            scanf("%d", &value);
            addTail(value);
            break;
        case 3:
            removeHead();
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
