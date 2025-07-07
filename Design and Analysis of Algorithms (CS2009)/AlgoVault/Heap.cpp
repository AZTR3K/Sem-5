#include <iostream>
using namespace std;

void HeapInsert(int heapArray[], int value, int index)
{
    heapArray[index] = value;

    while (index > 0)
    {
        int parent = (index - 1) / 2;
        if (heapArray[parent] < heapArray[index])
        {
            swap(heapArray[parent], heapArray[index]);
            index = parent;
        }

        else
            break;  // Heap property satisfied
    }
}

int main()
{
    cout << "Hello";
    return 0;
}
