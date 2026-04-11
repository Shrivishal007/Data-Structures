#ifndef SKEW_HEAP_H
#define SKEW_HEAP_H

#include <iostream>
#include <algorithm>
#include <iomanip>
#include <stdexcept>

template <typename T>
class SKEW_HEAP
{
private:
    class NODE
    {
    public:
        T data;
        NODE *left;
        NODE *right;

        NODE(T data) : data(data), left(nullptr), right(nullptr) {}
    } *root;

    NODE *merge(NODE *h1, NODE *h2)
    {
        if (h1 == nullptr)
            return h2;
        if (h2 == nullptr)
            return h1;

        if (h1->data > h2->data)
            std::swap(h1, h2);

        h1->right = merge(h1->right, h2);
        std::swap(h1->left, h1->right);

        return h1;
    }

    void printHeap(NODE *root, int level = 0, char child = ' ')
    {
        if (root == nullptr)
            return;

        printHeap(root->right, level + 1, 'R');
        for(int i = 0; i < level; i++)
            std::cout << std::setw(4) << " ";
        if (child != ' ')
            std::cout << child << ":";
        std::cout << root->data << std::endl;
        printHeap(root->left, level + 1, 'L');
    }

    NODE *copyHeap(NODE *root)
    {
        if (root == nullptr)
            return nullptr;

        NODE* node = new NODE(root->data);
        node->left  = copyHeap(root->left);
        node->right = copyHeap(root->right);
        return node;
    }

    void deleteHeap(NODE *root)
    {
        if(root == nullptr)
            return;

        deleteHeap(root->left);
        deleteHeap(root->right);
        delete root;
    }

public:
    SKEW_HEAP() : root(nullptr) {}

    SKEW_HEAP(const SKEW_HEAP &other)
    {
        root = copyHeap(other.root);
    }

    SKEW_HEAP& operator =(const SKEW_HEAP &other)
    {
        if (this != &other)
        {
            deleteHeap(root);
            root = copyHeap(other.root);
        }

        return *this;
    }

    SKEW_HEAP(SKEW_HEAP &&other) noexcept
    {
        root = other.root;
        other.root = nullptr;
    }

    SKEW_HEAP& operator =(SKEW_HEAP &&other) noexcept
    {
        if (this != &other)
        {
            deleteHeap(root);
            root = other.root;
            other.root = nullptr;
        }

        return *this;
    }

    ~SKEW_HEAP()
    {
        deleteHeap(root);
    }

    void insert(const T &key)
    {
        NODE *newNode = new NODE(key);
        root = merge(root, newNode);
    }

    T findMinimum()
    {
        if (root == nullptr)
            throw std::runtime_error("Heap is empty");

        return root->data;
    }

    T deleteMinimum()
    {
        if (root == nullptr)
            throw std::runtime_error("Heap is empty");

        NODE *temp = root;
        T key = temp->data;

        root = merge(root->left, root->right);
        delete temp;
        return key;
    }

    void mergeWith(SKEW_HEAP &other)
    {
        if (this == &other)
            return;

        root = merge(root, other.root);
        other.root = nullptr;
    }

    void print()
    {
        if (root == nullptr)
            std::cout << "The Skew Heap is empty" << std::endl;
        else
            printHeap(root);
    }
};

#endif