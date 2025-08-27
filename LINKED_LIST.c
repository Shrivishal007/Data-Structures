#include <stdio.h>
#include <stdlib.h>

typedef struct NODE
{
    int data;
    struct NODE *next;
} NODE;

NODE *head = NULL, *tail = NULL;
int count = 0;

void add(int value)
{
    NODE *node = (NODE *)malloc(sizeof(NODE));
    if (node == NULL)
    {
        printf("Node is not created\n");
        exit(1);
    }

    node->data = value;
    node->next = NULL;
    if (head == NULL)
        head = node;
    else
        tail->next = node;
    tail = node;
    count++;
    printf("%d is added in to the linked list\n", value);
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
        tail->next = node;
        node->next = NULL;
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
    printf("%d is added in the index position %d of the linked list\n", value, position);
}

void delete(int index)
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

void search(int target)
{
    if (head == NULL)
    {
        printf("Linked list is empty\n");
        return;
    }
    NODE *node = head;
    int i = 0, element_found = 0;
    while (node != NULL)
    {
        if (node->data == target)
        {
            printf("Element found at position %d\n", i);
            element_found = 1;
        }

        node = node->next;
        i++;
    }

    if (!element_found)
        printf("Element is not found in the linked list\n");
}

void display()
{
    NODE *node = head;
    if (head == NULL)
    {
        printf("Linked list is empty\n");
        return;
    }
    while (node != NULL)
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
        printf("\n1. Add\n 2.Insert\n3. Delete\n4. Search\n5. Display\n6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if (choice == 6)
            break;

        switch (choice)
        {
        case 1:
            printf("Enter the element to be added: ");
            scanf("%d", &value);
            add(value);
            break;
        case 2:
            printf("Enter the index position of the element to be inserted: ");
            scanf("%d", &pos);
            printf("Enter the element to be inserted: ");
            scanf("%d", &value);
            insert(pos, value);
            break;
        case 3:
            printf("Enter the index position of the element to be deleted: ");
            scanf("%d", &pos);
            delete(pos);
            break;
        case 4:
            printf("Enter the value to be searched: ");
            scanf("%d", &value);
            search(value);
            break;
        case 5:
            display();
            break;
        default:
            printf("Invalid choice!\n");
            break;
        }
    }

    while (head != NULL)
    {
        NODE *node = head;
        head = head->next;
        free(node);
    }
    printf("Program exited!\n");
    return 0;
}