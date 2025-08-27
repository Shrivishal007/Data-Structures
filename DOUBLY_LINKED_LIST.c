#include <stdio.h>
#include <stdlib.h>

typedef struct NODE
{
    int data;
    struct NODE *previous;   
    struct NODE *next;   
} NODE;

NODE *head = NULL, *tail = NULL;
int count = 0;

void addRear(int value)
{
    NODE *node = (NODE *)malloc(sizeof(NODE));
    if (node == NULL)
    {
        printf("Node is not created\n");
        exit(1);
    }

    node -> data = value;
    node -> previous = tail;
    node -> next = NULL;
    if(head == NULL)
        head = node;
    else
        tail -> next = node;
    tail = node;
    count++;
    printf("%d is added at the rear in to the doubly linked list\n", value);
}

void addFront(int value)
{
    NODE *node = (NODE *)malloc(sizeof(NODE));
    if (node == NULL)
    {
        printf("Node is not created\n");
        exit(1);
    }

    node -> data = value;
    node -> next = head;
    node -> previous = NULL;
    if(head == NULL)
        tail = node;
    else
        head -> previous = node;
    head = node;
    count++;
    printf("%d is added at the front in to the doubly linked list\n", value);
}

void insert(int position, int value)
{
    NODE *node, *ptr = head;
    if(position < 0 || position > count)
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

    node -> data = value;
    if (position == 0)
    {
        node -> previous = NULL;
        node -> next = head;

        if(head != NULL)
            head -> previous = node;

        head = node;
        if(tail == NULL)
            tail = node;
    }

    else if(position == count)
    {
        node -> next = NULL;
        node -> previous = tail;

        if(tail != NULL)
            tail -> next = node;

        tail = node;
    }

    else
    {
        if (position < count / 2)
            for(int i = 0; i < position; i++)
                ptr = ptr -> next;
        else
        {
            ptr = tail;
            for (int i = count - 1; i > position; i--)
                ptr = ptr->previous;
        }

        node -> next = ptr;
        node -> previous = ptr -> previous;

        ptr -> previous -> next = node;
        ptr -> previous = node;
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
        value = node -> data;
        head = head -> next;

        if(head != NULL)
            head -> previous = NULL;
        else
            tail = NULL;

        free(node);
    }

    else if (index == count - 1)
    {
        node = tail;
        value = node -> data;
        tail = tail -> previous;

        if(tail != NULL)
            tail -> next = NULL;
        else
            head = NULL;

        free(node);
    }

    else
    {
        if (index < count / 2)
            for(int i = 0; i < index; i++)
                ptr = ptr -> next;
        else
        {
            ptr = tail;
            for (int i = count - 1; i > index; i--)
                ptr = ptr->previous;
        }

        node = ptr;
        value = node -> data;

        node -> previous -> next = node -> next;
        node -> next -> previous = node -> previous;

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
        printf("Doubly linked list is empty\n");
        return;
    }
    while(node != NULL)
    {
        printf("%d ", node -> data);
        node = node -> next;
    }
    printf("\n");
}

void reverse_display()
{
    NODE *node = tail;
    if (head == NULL)
    {
        printf("Doubly linked list is empty\n");
        return;
    }
    while(node != NULL)
    {
        printf("%d ", node -> data);
        node = node -> previous;
    }
    printf("\n");
}

int main()
{
    int choice, pos, value;
    while (1)
    {
        printf("\n1. Add at Front\n2. Add at Rear\n3.Insert\n4. Delete\n5. Display\n6. Reverse Display\n7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if (choice == 7)
            break;
            
        switch (choice)
        {
            case 1:
                printf("Enter the element to be added at the front: ");
                scanf("%d", &value);
                addFront(value);
                break;
            case 2:
                printf("Enter the element to be added at the rear: ");
                scanf("%d", &value);
                addRear(value);
                break;
            case 3:
                printf("Enter the index position of the element to be inserted: ");
                scanf("%d", &pos);
                printf("Enter the element to be inserted: ");
                scanf("%d", &value);
                insert(pos, value);
                break;
            case 4:
                printf("Enter the index position of the element to be deleted: ");
                scanf("%d", &pos);
                delete(pos);
                break;
            case 5:
                display();
                break;
            case 6:
                reverse_display();
                break;
            default:
                printf("Invalid choice!\n");
                break;
        }
    }

    while(head != NULL)
    {
        NODE *node = head;
        head = head -> next;
        free(node);
    }
    printf("Program exited!\n");
    return 0;
}