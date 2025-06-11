> # Heap Construction

## Description
### One by one insertion
- Inserting a key into empty heap takes O(1) time.
- Inserting a key in an already constructed heap in worst case takes log n comparisons and swappings.
- There are total n elements so O(n log n) time.

## C/C++ Implementation
```cpp
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
            break; // Heap property satisfied
    }
}
```


