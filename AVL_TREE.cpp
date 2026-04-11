#include <iostream>
#include "AVL_TREE.h"

using namespace std;

int main()
{
    AVL_TREE<int> tree;
    int choice, value;
    while (true)
    {
        cout << "\n1. Insert\n2. Delete\n3. Display\n4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        if (choice == 4)
            break;

        switch (choice)
        {
        case 1:
            cout << "Enter the element to be inserted into the AVL tree: ";
            cin >> value;
            if (tree.insert(value))
                cout << value << " is inserted" << endl;
            else
                cout << "Duplicate keys are not allowed" << endl;
            break;
        case 2:
            cout << "Enter the element to be deleted from the tree: ";
            cin >> value;
            if (tree.deleteNode(value))
                cout << value << " is deleted" << endl;
            else
                cout << "Element is not found" << endl;
            break;
        case 3:
            tree.print();
            break;
        default:
            cout << "Invalid choice!" <<endl;
            break;
        }
    }

    cout << "Program exited!" << endl;
    return 0;
}