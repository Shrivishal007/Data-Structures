#include <iostream>
using namespace std;

class Stack
{
    private:
        int *arr, size, top;
    public:
        Stack(int size)
        {
            this -> size = size;
            arr = new int[size];
            top = -1;
        }
    
        bool is_empty()      {return (top == -1);}

        bool is_full()       {return (top == size - 1);}

        void push(int value)
        {
            if(is_full())
                throw runtime_error("Stack array is full");
            arr[++top] = value;
        }

        int pop()
        {
            if(is_empty())
                throw runtime_error("Stack array is empty");
            return arr[top--];
        }

        int peek()
        {
            if(is_empty())
                throw runtime_error("Stack array is empty");
            return arr[top];
        }

        void display()
        {
            if (!is_empty())
                for (int i = top; i >= 0; i--)
                    cout << arr[i] << " ";
            cout << endl;
        }

        int size_of()       {return (top + 1);}

        ~Stack()
        {
            delete[] arr;
        }
};


class Queue
{
    private:
        int *arr, size, front, rear;
    public:
        Queue(int size)
        {
            this -> size = size;
            arr = new int[size];
            front = rear = -1;
        }

        bool is_empty()     {return (front == -1);}

        bool is_full()      {return (rear == size - 1);}

        void enqueue(int value)
        {
            if(is_full())
                throw runtime_error("Queue array is full");
            if(front == -1)
                front++;
            arr[++rear] = value;  
        }

        int dequeue()
        {
            int value; 
            if (is_empty())
                throw runtime_error("Queue array is empty");
            value = arr[front++];
            if (front > rear)
                front = rear = -1;
            return value; 
        }

        int get_front()
        {
            if (is_empty())
                throw runtime_error("Queue array is empty");
            return arr[front];
        }

        int get_rear()
        {
            if (is_empty())
                throw runtime_error("Queue array is empty");
            return arr[rear];    
        }

        void display()
        {
            if(!is_empty())
                for (int i = front; i <= rear; i++)
                    cout << arr[i] << " ";
            cout << endl;
        }

        int size_of()       {return (is_empty())? 0 : (rear - front + 1);}

        ~Queue()
        {
            delete[] arr;
        }
};


class Deque
{
    private:
        int *arr, size, front, rear;
    public:
        Deque(int size)
        {
            this -> size = size;
            arr = new int[size];
            front = rear = -1;
        }

        bool is_empty()     {return (front == -1);}

        bool is_full()      {return ((front == 0 && rear == size - 1) || (front == rear + 1));}

        void insert_front(int value)
        {
            if(is_full())
                throw runtime_error("Deque array is full");

            if(is_empty())
                front = rear = 0;
            else if(front == 0)
                front = size - 1;
            else
                front--;
            arr[front] = value;
        }

        void insert_rear(int value)
        {
            if(is_full())
                throw runtime_error("Deque array is full");

            if(is_empty())
                front = rear = 0;
            else if(rear == size - 1)
                rear = 0;
            else
                rear++;
            arr[rear] = value;
        }

        int delete_front()
        {
            int value;
            if (is_empty())
                throw runtime_error("Deque array is empty");
                
            value = arr[front];
            if(front == rear)
                front = rear = -1;
            else if(front == size - 1)
                front = 0;
            else
                front++;
            return value; 
        }

        int delete_rear()
        {
            int value;
            if (is_empty())
                throw runtime_error("Deque array is empty");

            value = arr[rear];
            if(front == rear)
                front = rear = -1;
            else if(rear == 0)
                rear = size - 1;
            else
                rear--;
            return value; 
        }

        int get_front()
        {
            if (is_empty())
                throw runtime_error("Deque array is empty");
            return arr[front];
        }

        int get_rear()
        {
            if (is_empty())
                throw runtime_error("Deque array is empty");
            return arr[rear];    
        }

        void display()
        {
            int i = front;
            if(!is_empty())   
                while(true)
                {
                    cout << arr[i] << " ";
                    if (i == rear) 
                        break;
                    i = (i + 1) % size;
                }
            cout << endl;
        }

        int size_of()
        {
            if(is_empty())
                return 0;
            if(front <= rear)
                return (rear - front + 1);
            else
                return (size + rear - front + 1);     // (size - (front - rear - 1))
        }

        ~Deque()
        {
            delete[] arr;
        }
};

int main ()
{
    int size, value, res;

    cout << "Enter the size of the stack array to be created: ";
    cin >> size;
    Stack stack(size);

    cout << "Enter the size of the queue array to be created: ";
    cin >> size;
    Queue queue(size);

    cout << "Enter the size of the queue array to be created: ";
    cin >> size;
    Deque deque(size);
    return 0;
}