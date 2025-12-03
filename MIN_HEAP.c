#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct
{
    int *array;
    int max_size;
    int current_size;
} MinHeap;

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

MinHeap *createMinHeap(int size)
{
    MinHeap *m = (MinHeap *)malloc(sizeof(MinHeap));
    if (m == NULL)
    {
        printf("Heap is not created\n");
        exit(1);
    }

    m->max_size = size;
    m->array = (int *)malloc(m->max_size * sizeof(int));
    if (m->array == NULL)
    {
        printf("Array is not created\n");
        free(m);
        exit(1);
    }

    m->current_size = 0;
    printf("Heap is created with size %d\n", m->max_size);
    return m;
}

void insert(MinHeap *m, int value)
{
    int i, parent;
    if (m->current_size >= m->max_size)
    {
        printf("Heap is full\n");
        return;
    }
    i = (m->current_size);
    m->array[(m->current_size)++] = value;
    
    while (i > 0)
    {
        parent = (i - 1) / 2;
        if (m->array[parent] > m->array[i])
        {
            swap(&m->array[i], &m->array[parent]);
            i = parent;
        }
        else
            break;
    }

    printf("%d is inserted into the heap\n", value);
}

void heapify(MinHeap *m, int i)
{
    int smallest = i, left = (2 * i) + 1, right = (2 * i) + 2;
    if (left < m->current_size && m->array[left] < m->array[smallest])
        smallest = left;
    if (right < m->current_size && m->array[right] < m->array[smallest])
        smallest = right;

    if (smallest != i)
    {
        swap(&m->array[i], &m->array[smallest]);
        heapify(m, smallest);
    }
}

void removeElement(MinHeap *m)
{
    int value;
    if (m->current_size == 0)
    {
        printf("Heap is empty\n");
        return;
    }
    value = m->array[0];
    m->array[0] = m->array[--(m->current_size)];
    heapify(m, 0);

    printf("%d is deleted from the heap\n", value);
}

void deleteAt(MinHeap *m, int index)
{
    int value, j, parent;
    if (m->current_size == 0)
    {
        printf("Heap is empty\n");
        return;
    }

    if (index < 0 || index >= m->current_size)
    {
        printf("Out of Range\n");
        return;
    }

    value = m->array[index];
    m->array[index] = m->array[(m->current_size) - 1];
    (m->current_size)--;

    if (index > 0 && m->array[index] < m->array[(index - 1) / 2])
    {
        j = index;
        while (j > 0)
        {
            parent = (j - 1) / 2;
            if (m->array[parent] > m->array[j])
            {
                swap(&m->array[j], &m->array[parent]);
                j = parent;
            }
            else
                break;
        }
    }
    else
        heapify(m, index);

    printf("%d is deleted from the heap at index position %d\n", value, index);
}

int minimum(MinHeap *m)
{
    if (m->current_size == 0)
        return INT_MIN;
    return m->array[0];
}

void display(MinHeap *m, int level, int index, char child)
{
    if (m->current_size == 0)
    {
        printf("Heap is empty\n");
        return;
    }

    if (index >= m->current_size)
        return;

    for (int i = 0; i < level; i++)
        printf("    ");

    if (level == 0)
        printf("Root: %d\n", m->array[index]);
    else
        printf("%c: %d\n", child, m->array[index]);

    display(m, level + 1, 2 * index + 1, 'L');
    display(m, level + 1, 2 * index + 2, 'R');
}

int main()
{
    MinHeap *m;
    int choice, size, value, pos, res;

    printf("Enter the size of the Min heap to be created: ");
    scanf("%d", &size);
    m = createMinHeap(size);

    while (1)
    {
        printf("\n1. Insert\n2. Remove\n3. Delete\n4. Display\n5. Smallest Element\n6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if (choice == 6)
            break;

        switch (choice)
        {
        case 1:
            printf("Enter the element to be inserted into the min heap: ");
            scanf("%d", &value);
            insert(m, value);
            break;
        case 2:
            removeElement(m);
            break;
        case 3:
            printf("Enter the index position of the element to be deleted: ");
            scanf("%d", &pos);
            deleteAt(m, pos);
            break;
        case 4:
            display(m, 0, 0, ' ');
            break;
        case 5:
            res = minimum(m);
            if (res == INT_MIN)
                printf("Heap is empty\n");
            else
                printf("The smallest element in the heap array is %d\n", res);
            break;
        default:
            printf("Invalid choice!\n");
            break;
        }
    }

    free(m->array);
    free(m);
    printf("Program exited!\n");
    return 0;
}