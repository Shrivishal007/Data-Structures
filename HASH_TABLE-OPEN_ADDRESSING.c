#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    int *array;
    int size;
} HashTable;

HashTable *createHashTable(int size)
{
    HashTable *hashTable = (HashTable *)malloc(sizeof(HashTable));
    if (hashTable == NULL)
    {
        printf("Hash table not created\n");
        exit(1);
    }

    hashTable->size = size;
    hashTable->array = (int *)malloc(hashTable->size * sizeof(int));
    if (hashTable->array == NULL)
    {
        printf("Hash table array not created\n");
        free(hashTable);
        exit(1);
    }

    for (int i = 0; i < size; i++)
        hashTable->array[i] = -1;
    
    printf("Hash table is created with size %d\n", hashTable->size);
    return hashTable;
}

int hash(HashTable *h, int key)
{
    return key % h->size;
}

// int hash2(HashTable *h, int key)
// {
//     return 1 + (key % (h->size - 1));
// }

void insertKey(HashTable *h, int key)
{
    int index = hash(h, key), probe;

    for (int i = 0; i < h->size; i++)
    {
        probe = (index + i) % h->size;      
                                            // probe = (index + i * i) % h->size; for quadratic probing
                                            // probe = (index + i * hash2(h, key)) % h->size; for double hashing
        if (h->array[probe] == -1 || h->array[probe] == -2)
        {
            h->array[probe] = key;
            printf("The key %d is inserted in the hash table at index %d\n", key, probe);
            return;
        }
    }

    printf("Hash table is full - %d not inserted\n", key);
}

int searchKey(HashTable *h, int key)
{
    int index = hash(h, key), probe;

    for (int i = 0; i < h->size; i++)
    {
        probe = (index + i) % h->size;
                                            // probe = (index + i * i) % h->size; for quadratic probing
                                            // probe = (index + i * hash2(h, key)) % h->size; for double hashing
        if (h->array[probe] == -1)
            return 0;

        if (h->array[probe] == key)
            return 1;
    }

    return 0;
}

void deleteKey(HashTable *h, int key)
{
    int index = hash(h, key), probe;

    for (int i = 0; i < h->size; i++)
    {
        probe = (index + i) % h->size;
                                            // probe = (index + i * i) % h->size; for quadratic probing
                                            // probe = (index + i * hash2(h, key)) % h->size; for double hashing
        if (h->array[probe] == -1)
        {
            printf("Key %d is not found\n", key);
            return;
        }

        if (h->array[probe] == key)
        {
            h->array[probe] = -2;
            printf("The key %d is deleted from the hash table\n", key);
            return;
        }
    }

    printf("Key %d is not found\n", key);
}

void display(HashTable *h)
{
    printf("Hash Table\n");
    for (int i = 0; i < h->size; i++)
        printf("%d - %d\n", i, h->array[i]);

    printf("\n");
}

int main()
{
    HashTable *h;
    int choice, size, key, res;

    printf("Enter the size of the hash table: ");
    scanf("%d", &size);
    h = createHashTable(size);

    while (1)
    {
        printf("\n1. Insert Key\n2. Search Key\n3. Delete Key\n4. Display\n5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if (choice == 5)
            break;
        
        switch (choice)
        {
        case 1:
            printf("Enter the key to be inserted into the hash table: ");
            scanf("%d", &key);
            insertKey(h, key);
            break;
        case 2:
            printf("Enter the key to be searched in the hash table: ");
            scanf("%d", &key);
            if (searchKey(h, key))
                printf("The key %d is found in the hash table\n", key);
            else
                printf("The key %d is not found in the hash table\n", key);
            break;
        case 3:
            printf("Enter the key to be deleted from the hash table: ");
            scanf("%d", &key);
            deleteKey(h, key);
            break;
        case 4:
            display(h);
            break;
        default:
            printf("Invalid choice!\n");
            break;
        }
    }

    free(h->array);
    free(h);
    return 0;
}