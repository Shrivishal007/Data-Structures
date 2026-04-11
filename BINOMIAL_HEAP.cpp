#include <iostream>
#include "BINOMIAL_HEAP.h"

using namespace std;

int main()
{
    system("chcp 65001");
    BINOMIAL_HEAP<int> heap;
    int choice, value, key;
    while (true)
    {
        cout << "\n1. Insert\n2. Minimum Element\n3. Delete Minimum\n4. Display\n5. Decrease Value\n6. Delete Element\n7. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        if (choice == 7)
            break;

        switch (choice)
        {
        case 1:
            cout << "Enter the element to be inserted into the Binomial heap: ";
            cin >> value;
            heap.insert(value);
            cout << value << " is inserted" << endl;
            break;
        case 2:
            try
            {
                cout << "Minimum Element: " << heap.findMinimum() << endl;
            }
            catch(const exception &e)
            {
                cout << e.what() << endl;
            }
            break;
        case 3:
            try
            {
                cout << heap.deleteMinimum() << " is deleted" << endl;
            }
            catch(const exception &e)
            {
                cout << e.what() << endl;
            }
            break;
        case 4:
            heap.print();
            break;
        case 5:
            cout << "Enter the key in the heap to be replaced: ";
            cin >> key;
            cout << "Enter the value to replace: ";
            cin >> value;

            try
            {
                heap.decreaseValue(key, value);
                cout << key << " is decreased with " << value << endl;
            }
            catch(const exception& e)
            {
                cout << e.what() << endl;
            }
            break;
        case 6:
            cout << "Enter the element to be deleted from the tree: ";
            cin >> value;
            if (heap.deleteNode(value))
                cout << value << " is deleted" << endl;
            else
                cout << "Element is not found" << endl;
            break;
        default:
            cout << "Invalid choice!" <<endl;
            break;
        }
    }

    cout << "Program exited!" << endl;
    return 0;
}