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

### Heapify
- Builds a heap from an unsorted array using heapify() from bottom to top.
- Starts at the last non-leaf node: index n/2 - 1.
- Each call to heapify() takes up to O(log n) time.
- Total time complexity of building the heap is O(n) — better than inserting one by one.
- Commonly used in heap sort and priority queues.

## C/C++ Implementation
```cpp
void heapify(int array[], int n, int i)
{
    int largest = i;          // Assume current node is largest
    int left = 2 * i + 1;     // Left child
    int right = 2 * i + 2;    // Right child

    // Compare with left child
    if (left < n && array[left] > array[largest])
        largest = left;

    // Compare with right child
    if (right < n && array[right] > array[largest])
        largest = right;

    // If largest is not the root, swap and recurse
    if (largest != i)
    {
        swap(array[i], array[largest]);
        heapify(array, n, largest);  // Recursively heapify the subtree
    }
}

// Max heap
void buildHeap(int array[], int n)
{
    // Start from last non-leaf node and move to root
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(array, n, i);
}
```
