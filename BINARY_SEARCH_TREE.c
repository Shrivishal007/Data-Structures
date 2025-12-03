#include <stdio.h>
#include <stdlib.h>

typedef struct NODE
{
    int data;
    struct NODE *left, *right;
} NODE;

NODE *createNode(int data)
{
    NODE *node = (NODE *)malloc(sizeof(NODE));
    if (node == NULL)
    {
        printf("Node is not created\n");
        exit(1);
    }

    node->data = data;
    node->left = node->right = NULL;
    return node;
}

NODE *insert(NODE *root, int data)
{
    if (root == NULL)
        return createNode(data);

    if (data < root->data)
        root->left = insert(root->left, data);
    else
        root->right = insert(root->right, data);

    return root;
}

int search(NODE *root, int value)
{
    if (root == NULL)
        return 0;
    if (root->data == value)
        return 1;
    if (value < root->data)
        return search(root->left, value);
    else
        return search(root->right, value);
}

NODE *removeNode(NODE *root, int data)
{
    if (root == NULL)
        return NULL;

    if (data < root->data)
        root->left = removeNode(root->left, data);
    else if (data > root->data)
        root->right = removeNode(root->right, data);
    else
    {
        if (root->left == NULL && root->right == NULL)
        {
            free(root);
            return NULL;
        }

        else if (root->left == NULL)
        {
            NODE *temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL)
        {
            NODE *temp = root->left;
            free(root);
            return temp;
        }

        else
        {
            NODE *temp = root->right;
            while (temp->left)
                temp = temp->left;

            root->data = temp->data;
            root->right = removeNode(root->right, temp->data);
        }
    }

    return root;
}

void printTree(NODE *root, int level, char child)
{
    if (root == NULL)
        return;

    for (int i = 0; i < level; i++)
        printf("    ");

    if (level == 0)
        printf("Root: %d\n", root->data);
    else
        printf("%c: %d\n", child, root->data);

    printTree(root->left, level + 1, 'L');
    printTree(root->right, level + 1, 'R');
}

int height(NODE *root)
{
    int left, right;
    if (root == NULL)
        return 0;

    left = height(root->left);
    right = height(root->right);

    return (left > right) ? left + 1 : right + 1;
}

void preorder(NODE *root)
{
    if (root == NULL)
        return;

    printf("%d ", root->data);
    preorder(root->left);
    preorder(root->right);
}

void inorder(NODE *root)
{
    if (root == NULL)
        return;

    inorder(root->left);
    printf("%d ", root->data);
    inorder(root->right);
}

void postorder(NODE *root)
{
    if (root == NULL)
        return;

    postorder(root->left);
    postorder(root->right);
    printf("%d ", root->data);
}

void deleteTree(NODE *root)
{
    if (root == NULL)
        return;

    deleteTree(root->left);
    deleteTree(root->right);
    free(root);
}

int main()
{
    NODE *root = NULL;
    int choice, value, res;
    while (1)
    {
        printf("\n1. Insert\n2. Delete\n3. Display\n4. Pre-Order\n5. In-Order\n6. Post-Order\n7. Height\n8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        if (choice == 8)
            break;

        switch (choice)
        {
        case 1:
            printf("Enter the element to be inserted into the tree: ");
            scanf("%d", &value);
            root = insert(root, value);
            printf("%d is inserted\n", value);
            break;
        case 2:
            printf("Enter the element to be deleted from the tree: ");
            scanf("%d", &value);
            if (search(root, value))
            {
                root = removeNode(root, value);
                printf("%d is deleted\n", value);
            }
            else
                printf("Element not found\n");
            break;
        case 3:
            if (root == NULL)
                printf("The binary search tree is empty");
            else
                printTree(root, 0, ' ');
            printf("\n");
            break;
        case 4:
            printf("Pre-Order Traversal: ");
            if (root == NULL)
                printf("The binary search tree is empty");
            else
                preorder(root);
            printf("\n");
            break;
        case 5:
            printf("In-Order Traversal: ");
            if (root == NULL)
                printf("The binary search tree is empty");
            else
                inorder(root);
            printf("\n");
            break;
        case 6:
            printf("Post-Order Traversal: ");
            if (root == NULL)
                printf("The binary search tree is empty");
            else
                postorder(root);
            printf("\n");
            break;
        case 7:
            res = height(root);
            if (res == 0)
                printf("The binary search tree is empty\n");
            else if (res == 1)
                printf("The tree has only root node\n");
            else
                printf("The height of the tree is %d\n", res);
            break;
        default:
            printf("Invalid choice!\n");
            break;
        }
    }

    deleteTree(root);
    printf("Program exited!\n");
    return 0;
}