> # Merge Sort

- A divide and conquer algorithm.

- Divide the array into two halves.

- Recursively sort each half.

- Merge the sorted halves to produce the final sorted array.

## C/C++ Implementation
```cpp
void Merge(int array[], int low, int mid, int high)
{
    int size1 = mid - low + 1;
    int size2 = high - mid;

    int subarray1[size1];
    int subarray2[size2];

    for (int i = 0; i < size1 - 1; i++)
    {
        subarray1[i] = array[low + i];
    }

    for (int j = 0; j < size2 - 1; j++)
    {
        subarray2[j] = array[mid + j + 1];
    }

    int i = 0;
    int j = 0;

    for (int k = low; k < high; k++)
    {
        if (subarray1[i] < subarray2[j])
        {
            array[k] = subarray1[i];
            i++;
        }
        else
        {
            array[k] = subarray2[j];
            j++;
        }
    }
}

void MergeSort(int array[], int low, int high)
{
    if (low < high)
    {
        int mid = (low + high) / 2;
        MergeSort(array, low, mid);
        MergeSort(array, mid + 1, high);

        Merge(array, low, mid, high);
    }
}

```
### Time Complexity:
- O(n log n) -> Best Case.
- O(n log n) -> Average Case.
- O(n log n) -> Worst Case.
