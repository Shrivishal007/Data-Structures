#ifndef BINOMIAL_HEAP_H
#define BINOMIAL_HEAP_H

#include <iostream>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <string.h>
#include <vector>
#include <stdexcept>

template <typename T>
class BINOMIAL_HEAP
{
private:
    class NODE
    {
    public:
        T data;
        int degree;
        NODE *parent;
        NODE *left_child;
        NODE *right_sibling;

        NODE(T data) : data(data), parent(nullptr), left_child(nullptr), right_sibling(nullptr), degree(0) {}
    } *head;

    NODE *mergeTrees(NODE *t1, NODE *t2)
    {
        if (t1->data > t2->data)
            std::swap(t1, t2);

        t2->parent = t1;
        t2->right_sibling = t1->left_child;
        t1->left_child = t2;
        t1->degree++;

        return t1;
    }

    // NODE *mergeHeaps(NODE *h1, NODE *h2)
    // {
    //     if (h1 == nullptr)
    //         return h2;
    //     if (h2 == nullptr)
    //         return h1;

    //     if (h1->degree <= h2->degree)
    //     {
    //         h1->right_sibling = mergeHeaps(h1->right_sibling, h2);
    //         return h1;
    //     }
    //     else
    //     {
    //         h2->right_sibling = mergeHeaps(h2->right_sibling, h1);
    //         return h2;
    //     }
    // }
    
    NODE* mergeHeaps(NODE* h1, NODE* h2)
    {
        if (h1 == nullptr) 
            return h2;
        if (h2 == nullptr) 
            return h1;

        NODE *head = nullptr, *tail = nullptr;
        if (h1->degree <= h2->degree)
        {
            head = tail = h1;
            h1 = h1->right_sibling;
        }
        else
        {
            head = tail = h2;
            h2 = h2->right_sibling;
        }

        while (h1 != nullptr && h2 != nullptr)
        {
            if (h1->degree <= h2->degree)
            {
                tail->right_sibling = h1;
                h1 = h1->right_sibling;
            }
            else
            {
                tail->right_sibling = h2;
                h2 = h2->right_sibling;
            }

            tail = tail->right_sibling;
        }

        if (h1 != nullptr)
            tail->right_sibling = h1;
        else if (h2 != nullptr)
            tail->right_sibling = h2;

        return head;
    }

    NODE *unionHeaps(NODE *head1, NODE *head2)
    {
        NODE *head = mergeHeaps(head1, head2);

        if (head == nullptr)
            return nullptr;

        NODE *prev = nullptr, *curr = head, *next = head->right_sibling;

        while (next)
        {
            if ((curr->degree != next->degree) || (next->right_sibling && curr->degree == next->right_sibling->degree))
            {
                prev = curr;
                curr = next;
            }
            else
            {
                if (curr->data <= next->data)
                {
                    curr->right_sibling = next->right_sibling;
                    curr = mergeTrees(curr, next);
                }
                else
                {
                    if (prev == nullptr)
                        head = next;
                    else
                        prev->right_sibling = next;

                    curr = mergeTrees(next, curr);
                }
            }

            next = curr->right_sibling;
        }

        return head;
    }

    NODE *searchNode(NODE *head, T data)
    {
        if (head == nullptr)
            return nullptr;

        if (head->data == data)
            return head;

        NODE *temp = searchNode(head->left_child, data);
        if (temp != nullptr)
            return temp;

        return searchNode(head->right_sibling, data);
    }

    void printTree(NODE *root, std::string prefix = "", bool is_last = true)
    {
        if (root == nullptr)
            return;

        std::cout << prefix << (is_last ? "└── " : "├── ") << root->data << std::endl;

        std::string child_prefix = prefix + (is_last ? "    " : "│   ");

        NODE* child = root->left_child;
        while (child != nullptr)
        {
            bool last = (child->right_sibling == nullptr);
            printTree(child, child_prefix, last);
            child = child->right_sibling;
        }
    }

    void printHeap(NODE *head)
    {
        while (head != nullptr)
        {
            std::cout << "B" << head->degree << ":" << std::endl;
            printTree(head);
            std::cout << std::endl;
            head = head->right_sibling;
        }
    }

    NODE *copyHeap(NODE *head, NODE *parent = nullptr)
    {
        if (head == nullptr)
            return nullptr;

        NODE *node = new NODE(head->data);
        node->degree = head->degree;
        node->parent = parent;
        node->left_child = copyHeap(head->left_child, node);
        node->right_sibling = copyHeap(head->right_sibling, parent);

        return node;
    }

    void deleteHeap(NODE *head)
    {
        if (head == nullptr)
            return;

        deleteHeap(head->left_child);
        deleteHeap(head->right_sibling);
        delete head;
    }

public:
    BINOMIAL_HEAP() : head(nullptr) {}

    BINOMIAL_HEAP(const BINOMIAL_HEAP &other)
    {
        head = copyHeap(other.head);
    }

    BINOMIAL_HEAP& operator =(const BINOMIAL_HEAP &other)
    {
        if (this != &other)
        {
            deleteHeap(head);
            head = copyHeap(other.head);
        }

        return *this;
    }

    BINOMIAL_HEAP(BINOMIAL_HEAP &&other) noexcept
    {
        head = other.head;
        other.head = nullptr;
    }

    BINOMIAL_HEAP& operator =(BINOMIAL_HEAP &&other) noexcept
    {
        if (this != &other)
        {
            deleteHeap(head);
            head = other.head;
            other.head = nullptr;
        }

        return *this;
    }

    ~BINOMIAL_HEAP()
    {
        deleteHeap(head);
    }

    void insert(T key)
    {
        BINOMIAL_HEAP<T> temp;

        temp.head = new NODE(key);
        head = unionHeaps(head, temp.head);
        temp.head = nullptr;
    }

    T findMinimum()
    {
        if (head == nullptr)
            throw std::runtime_error("Heap is empty");

        T min = head->data;
        NODE *temp = head->right_sibling;

        while (temp)
        {
            if (temp->data < min)
                min = temp->data;
            temp = temp->right_sibling;
        }

        return min;
    }

    T deleteMinimum()
    {
        if (head == nullptr)
            throw std::runtime_error("Heap is empty");

        T min = head->data;
        NODE *minimum = head, *curr = head, *prev = nullptr, *prev_minimum = nullptr;

        while(curr)
        {
            if (curr->data < min)
            {
                min = curr->data;
                minimum = curr;
                prev_minimum = prev;
            }

            prev = curr;
            curr = curr->right_sibling;
        }

        if (prev_minimum == nullptr)
            head = head->right_sibling;
        else
            prev_minimum->right_sibling = minimum->right_sibling;

        NODE *newHead = nullptr, *child = minimum->left_child, *next = nullptr;
        while (child)
        {
            next = child->right_sibling;
            child->right_sibling = newHead;
            child->parent = nullptr;
            newHead = child;
            child = next;
        }

        head = unionHeaps(head, newHead);
        delete minimum;

        return min;
    }

    void decreaseValue(T old_key, T new_key)
    {
        if (head == nullptr)
            throw std::runtime_error("Heap is empty");

        if (new_key > old_key)
            throw std::runtime_error("Value is greater than the key");

        NODE *temp = searchNode(head, old_key);

        if (temp == nullptr)
            throw std::runtime_error("Key is not found");

        temp->data = new_key;
        NODE *parent = temp->parent;
        while (parent && temp->data < parent->data)
        {
            std::swap(temp->data, parent->data);
            temp = parent;
            parent = temp->parent;
        }
    }

    bool deleteNode(T key)
    {
        NODE *node = searchNode(head, key);
        if (node == nullptr)
            return false;
        
        decreaseValue(key, std::numeric_limits<T>::lowest());
        deleteMinimum();
        return true;
    }

    void print()
    {
        if (head == nullptr)
            std::cout << "The Binomial Heap is empty" << std::endl;
        else
            printHeap(head);
    }
};

#endif