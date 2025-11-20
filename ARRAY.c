#include <stdio.h>
#include <stdlib.h>

int *array = NULL;
int current_size = 0, max_size = 0;

void addElement(int value)
{
    if(current_size >= max_size)
    {
        printf("Array is full\n");
        return;
    }
    array[current_size++] = value;
    printf("%d is added to the array\n", value);
}

void removeElement()
{
    int value;
    if (current_size == 0)
    {
        printf("Array is empty\n");
        return;
    }
    value = array[current_size-1];
    current_size--;
    printf("%d is deleted from the array\n", value);
}

void insertElement(int position, int value)
{
    if (position < 0 || position > current_size)
    {
        printf("Out of Range\n");
        return;
    }

    if(current_size >= max_size)
    {
        printf("Array is full\n");
        return;
    }
    
    for (int i = current_size; i > position; i--)
        array[i] = array[i-1];
    array[position] = value;
    current_size++;
    printf("%d is inserted to the array at index position %d\n", value, position);

}

void deleteAt(int index)
{
    int value;
    if (current_size == 0)
    {
        printf("Array is empty\n");
        return;
    }

    if (index < 0 || index >= current_size)
    {
        printf("Out of Range\n");
        return;
    }
    value = array[index];
    for (int i = index; i < current_size - 1; i++)
        array[i] = array[i+1];
    current_size--;
    printf("%d is deleted from the array at index position %d\n", value, index);
}

void display()
{
    if (current_size == 0)
    {
        printf("Array is empty\n");
        return;
    }
    for (int i = 0; i < current_size; i++)
        printf("%d ", array[i]);
    printf("\n");
}

int main ()
{
    int choice, position, value;
    printf("Enter the size of the array to be created: ");
    scanf("%d", &max_size);
    if (max_size < 1)
    {
        printf("Array cannot be created\n");
        return 1;
    }
    array = (int *)malloc(max_size * sizeof(int));
    if(array == NULL)
    {
        printf("Array is not created\n");
        exit(1);
    }
    printf("Array is created with size %d\n", max_size);

    while (1)
    {
        printf("\n1. Add\n2. Remove\n3. Insert\n4. Delete\n5. Display\n6. Size of\n7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if (choice == 7)
            break;
        
        switch (choice)
        {
            case 1:
                printf("Enter the element to be added: ");
                scanf("%d", &value);
                addElement(value);
                break;
            case 2:
                removeElement();
                break;
            case 3:
                printf("Enter the index position of the element to be inserted: ");
                scanf("%d", &position);
                printf("Enter the element to be inserted: ");
                scanf("%d", &value);
                insertElement(position, value);
                break;
            case 4:
                printf("Enter the index position of the element to be deleted: ");
                scanf("%d", &position);
                deleteAt(position);
                break;
            case 5:
                display();
                break;
            case 6:
                printf("The size of the array is %d\n", current_size);
                break;
            default:
                printf("Invalid choice!\n");
                break;
        }
    }

    free(array);
    printf("Program exited!\n");
    return 0;
}