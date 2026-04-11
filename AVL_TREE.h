#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <iostream>
#include <algorithm>
#include <iomanip>

template <typename T>
class AVL_TREE
{
private:
    class NODE
    {
    public:
        T data;
        NODE *left;
        NODE *right;
        int height;

        NODE(T data) : data(data), left(nullptr), right(nullptr), height(0) {}
    } *root;

    int getHeight(NODE *node)
    {
        return node? node->height : -1;
    }

    int BF(NODE *node)
    {
        return node? getHeight(node->left) - getHeight(node->right) : 0;
    }

    NODE *rotateRight(NODE *node)
    {
        NODE *middle = node->left;
        node->left = middle->right;
        middle->right = node;

        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        middle->height = 1 + std::max(getHeight(middle->left), getHeight(middle->right));

        return middle;
    }

    NODE *rotateLeft(NODE *node)
    {
        NODE *middle = node->right;
        node->right = middle->left;
        middle->left = node;

        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
        middle->height = 1 + std::max(getHeight(middle->left), getHeight(middle->right));

        return middle;
    }

    NODE *insertNode(NODE *root, T data)
    {
        if (root == nullptr)
            return new NODE(data);

        if (data < root->data)
            root->left = insertNode(root->left, data);
        else if (data > root->data)
            root->right = insertNode(root->right, data);
        else
            return root;

        root->height = 1 + std::max(getHeight(root->left), getHeight(root->right));
        int bf = BF(root);

        if (bf > 1 && data < root->left->data)
            return rotateRight(root);
        if (bf < -1 && data > root->right->data)
            return rotateLeft(root);
        if (bf > 1 && data > root->left->data)
        {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
        if (bf < -1 && data < root->right->data)
        {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }

        return root;
    }

    bool searchNode(NODE *root, T data)
    {
        if (root == nullptr)
            return false;
        if (root->data == data)
            return true;
        if (data < root->data)
            return searchNode(root->left, data);
        else
            return searchNode(root->right, data);
    }

    NODE *removeNode(NODE *root, T data)
    {
        if (root == nullptr)
            return nullptr;

        if (data < root->data)
            root->left = removeNode(root->left, data);
        else if (data > root->data)
            root->right = removeNode(root->right, data);
        else
        {
            if (root->left == nullptr)
            {
                NODE *temp = root->right;
                delete root;
                return temp;
            }

            else if (root->right == nullptr)
            {
                NODE *temp = root->left;
                delete root;
                return temp;
            }

            else
            {
                NODE *temp = root->right;
                while(temp->left)
                    temp = temp->left;
                root->data = temp->data;
                root->right = removeNode(root->right, temp->data);
            }
        }

        if (root == nullptr)
            return nullptr;

        root->height = 1 + std::max(getHeight(root->left), getHeight(root->right));
        int bf = BF(root);

        if (bf > 1 && BF(root->left) >= 0)
            return rotateRight(root);
        if (bf < -1 && BF(root->right) <= 0)
            return rotateLeft(root);
        if (bf > 1 && BF(root->left) < 0)
        {
            root->left = rotateLeft(root->left);
            return rotateRight(root);
        }
        if (bf < -1 && BF(root->right) > 0)
        {
            root->right = rotateRight(root->right);
            return rotateLeft(root);
        }

        return root;
    }

    void printTree(NODE *root, int level = 0, char child = ' ')
    {
        if (root == nullptr)
            return;

        printTree(root->right, level + 1, 'R');
        for(int i = 0; i < level; i++)
            std::cout << std::setw(4) << " ";
        if (child != ' ')
            std::cout << child << ":";
        std::cout << root->data << std::endl;
        printTree(root->left, level + 1, 'L');
    }

    NODE *copyTree(NODE *root)
    {
        if (root == nullptr)
            return nullptr;

        NODE* node = new NODE(root->data);
        node->height = root->height;
        node->left  = copyTree(root->left);
        node->right = copyTree(root->right);
        return node;
    }

    void deleteTree(NODE *root)
    {
        if(root == nullptr)
            return;

        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
    }

public:
    AVL_TREE() : root(nullptr) {}

    AVL_TREE(const AVL_TREE &other)
    {
        root = copyTree(other.root);
    }

    AVL_TREE& operator =(const AVL_TREE &other)
    {
        if (this != &other)
        {
            deleteTree(root);
            root = copyTree(other.root);
        }

        return *this;
    }

    AVL_TREE(AVL_TREE &&other) noexcept
    {
        root = other.root;
        other.root = nullptr;
    }

    AVL_TREE& operator =(AVL_TREE &&other) noexcept
    {
        if (this != &other)
        {
            deleteTree(root);
            root = other.root;
            other.root = nullptr;
        }

        return *this;
    }

    ~AVL_TREE()
    {
        deleteTree(root);
    }

    bool insert(const T &key)
    {
        if (!searchNode(root, key))
        {
            root = insertNode(root, key);
            return true;
        }
        else
            return false;
    }

    bool deleteNode(const T &key)
    {
        if (searchNode(root, key))
        {
            root = removeNode(root, key);
            return true;
        }
        else
            return false;
    }

    void print()
    {
        if (root == nullptr)
            std::cout << "The AVL tree is empty" << std::endl;
        else
            printTree(root);
    }
};

#endif