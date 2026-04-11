#include <iostream>
#include "LEFTIST_HEAP.h"
using namespace std;

int main()
{
    LEFTIST_HEAP<int> heap, heap1;
    int choice, value, n;
    while (true)
    {
        cout << "\n1. Insert\n2. Delete\n3. Minimum Element\n4. Display\n5. Merge with another heap\n6. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        if (choice == 6)
            break;

        switch (choice)
        {
        case 1:
            cout << "Enter the element to be inserted into the Leftist heap: ";
            cin >> value;
            heap.insert(value);
            cout << value << " is inserted" << endl;
            break;
        case 2:
            try
            {
                cout << heap.deleteMinimum() << " is deleted" << endl;
            }
            catch(const exception &e)
            {
                cout << e.what() << endl;
            }
            break;
        case 3:
            try
            {
                cout << "Minimum Element: " << heap.findMinimum() << endl;
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
            cout << "Enter number of elements to insert into second heap: ";
            cin >> n;
            for(int i = 0; i < n; i++)
            {
                cout << "Enter element[" << i+1 << "]: ";
                cin >> value;
                heap1.insert(value);
            }

            heap.mergeWith(heap1);
            break;
        default:
            cout << "Invalid choice!" <<endl;
            break;
        }
    }

    cout << "Program exited!" << endl;
    return 0;
}