#include <stdio.h>
#include <stdlib.h>

typedef struct NODE
{
    int key;
    struct NODE *next;
} NODE;

typedef struct 
{
    NODE **array;
    int size;
} HashTable;

NODE *createNode(int key)
{
    NODE *node = (NODE *)malloc(sizeof(NODE));
    if (node == NULL)
    {
        printf("Node not created\n");
        exit(1);
    }

    node->key = key;
    node->next = NULL;
    
    return node;
}

HashTable *createHashTable(int size)
{
    HashTable *hashTable = (HashTable *)malloc(sizeof(HashTable));
    if (hashTable == NULL)
    {
        printf("Hash table not created\n");
        exit(1);
    }

    hashTable->size = size;
    hashTable->array = (NODE **)malloc(hashTable->size * sizeof(NODE *));
    if (hashTable->array == NULL)
    {
        printf("Hash table array not created\n");
        free(hashTable);
        exit(1);
    }

    for (int i = 0; i < size; i++)
        hashTable->array[i] = NULL;
    
    printf("Hash table is created with size %d\n", hashTable->size);
    return hashTable;
}

int hash(HashTable *h, int key)
{
    return key % h->size;
}

void insertKey(HashTable *h, int key)
{
    NODE *node = createNode(key);
    int index = hash(h, key);

    node->next = h->array[index];
    h->array[index] = node;

    printf("The key %d is inserted in the hash table\n", key);
}

int searchKey(HashTable *h, int key)
{
    NODE *node;
    int index = hash(h, key);

    node = h->array[index];
    while (node)
    {
        if (node->key == key)
            return 1;

        node = node->next;
    }

    return 0;
}

void deleteKey(HashTable *h, int key)
{
    NODE *node, *prev;
    int index = hash(h, key);

    node = h->array[index];
    prev = NULL;

    if (node == NULL) 
    {
        printf("Key %d not found\n", key);
        return;
    }

    while (node && node->key != key)
    {
        prev = node;
        node = node->next;
    }

    if (node == NULL) 
    {
        printf("Key %d not found\n", key);
        return;
    }

    if (prev == NULL)
        h->array[index] = node->next;
    else
        prev->next = node->next;

    free(node);
    printf("The key %d is deleted from the hash table\n", key);
}

void display(HashTable *h)
{
    NODE *node;

    printf("Hash Table\n");
    for (int i = 0; i < h->size; i++)
    {
        printf("%d -> ", i);

        node = h->array[i];
        while (node)
        {
            printf("%d -> ", node->key);
            node = node->next;
        }

        printf("NULL\n");
    }

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
    
    for (int i = 0; i < h->size; i++)
    {
        NODE *node = h->array[i];
        while (node)
        {
            NODE *temp = node;
            node = node->next;
            free(temp);
        }
    }

    free(h->array);
    free(h);
    return 0;
}