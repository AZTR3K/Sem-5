> # Quick Sort

- Choose a **pivot** `v`.
- Move pointer `p` forward until an element > `v`.
- Move pointer `q` backward until an element < `v`.
- This partitions elements so greater ones go right, smaller ones go left.
- Check if `p` and `q` have crossed each other.
- If not crossed, swap the elements at `p` and `q`.
- Else, swap the pivot `v` with element at `q`.

- You are done with the first partition.
- All elements < `v` are on its left.
- All elements > `v` are on its right.
- Now apply Quick Sort recursively on both halves.

## C/C++ Implementation
```cpp
int partition(int array[], int low, int high)
{
    int pivot = array[low];
    int p = low + 1;
    int q = high;

    while(p <= q)
    {
        while(array[p] < pivot && p <= high)
            p++;

        while(array[q] >= pivot && q >= low)
            q--;

        if(p < q)
            swap(array[p], array[q]);

    }

    swap(array[low], array[q]);
    return q;
}

void QuickSort(int array[], int low, int high)
{
    if(low < high)
    {
        int pivotIndex = partition(array, low, high);

        QuickSort(array, low, pivotIndex - 1);
        QuickSort(array, pivotIndex + 1, high);
    }
}
```
### Time Complexity:
- O(n log n) -> Best Case.
- O(n log n) -> Average Case.
- O(n<sup>2</sup>) -> Worst Case.
