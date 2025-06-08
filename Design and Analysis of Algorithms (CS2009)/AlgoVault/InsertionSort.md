# Insertion Sort

## Description
- Start from the **second element** (index 1) and treat it as the key.
- Compare the key with all elements before it.
- **Shift elements** greater than the key to the right.
- Insert the key into its correct **sorted position** in the left subarray.
- Repeat for each element until the entire array is sorted.

- This algorithm builds the sorted array one element at a time.
- Efficient for **small or nearly sorted arrays**.
- In-place and **stable** sorting algorithm.

## C/C++ Implementation
```cpp
void InsertionSort(int array[], int n)
{
    for (int i = 1; i < n; i++)
    {
        int key = array[i];
        int j = i - 1;

        while (j >= 0 && array[j] > key)
        {
            array[j + 1] = array[j];
            j--;
        }

        array[j + 1] = key;
    }
}
```
## Time Complexity:
- O(n) -> Best Case.
- O(n<sup>2</sup>) → Average Case.
- O(n<sup>2</sup>) → Worst Case.
