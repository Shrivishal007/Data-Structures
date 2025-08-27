#include <stdio.h>
#include <stdlib.h>

int *arr = NULL;
int n = 0, size = 0;

void add_element(int value)
{
    if(n >= size)
    {
        printf("Array is full\n");
        return;
    }
    arr[n++] = value;
    printf("%d is added in the array\n", value);
}

void insert(int position, int value)
{
    if (position < 0 || position > n)
    {
        printf("Out of Range\n");
        return;
    }

    if(n >= size)
    {
        printf("Array is full\n");
        return;
    }
    
    for (int i = n; i > position; i--)
        arr[i] = arr[i-1];
    arr[position] = value;
    n++;
    printf("%d is inserted in the array at index position %d\n", value, position);

}

void delete_element(int index)
{
    int value;
    if (n == 0)
    {
        printf("Array is empty\n");
        return;
    }

    if (index < 0 || index >= n)
    {
        printf("Out of Range\n");
        return;
    }
    value = arr[index];
    for (int i = index; i < n - 1; i++)
        arr[i] = arr[i+1];
    n--;
    printf("%d is deleted in the array at index position %d\n", value, index);
}

void search(int target)
{
    if (n == 0)
    {
        printf("Array is empty\n");
        return;
    }
    int element_found = 0;
    for (int i = 0; i < n; i++)
        if (arr[i] == target)
        {
            printf("Element found at index position %d\n", i);
            element_found = 1;
        }
    if (!element_found)
        printf("Element is not found in the array\n");  
}

void display()
{
    if (n == 0)
    {
        printf("Array is empty\n");
        return;
    }
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");
}

int main ()
{
    int choice, pos, value;
    printf("Enter the size of the array to be created: ");
    scanf("%d", &size);
    if (size < 1)
    {
        printf("Array cannot be created\n");
        return 1;
    }
    arr = (int *)malloc(size * sizeof(int));
    if(arr == NULL)
    {
        printf("Array is not created\n");
        exit(1);
    }
    printf("Array is created with size %d\n", size);

    while (1)
    {
        printf("\n1. Add\n2. Insert\n3. Delete\n4. Search\n5. Display\n6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if (choice == 6)
            break;
        
        switch (choice)
        {
            case 1:
                printf("Enter the element to be added: ");
                scanf("%d", &value);
                add_element(value);
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
                delete_element(pos);
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

    free(arr);
    printf("Program exited!\n");
    return 0;
}