> # Selection Sort

## Description
- Start from the beginning of the array.
- Assume the current element is the minimum (min = i).
- Loop through the rest of the array to find the actual minimum element.
- If a smaller element is found, update the min index.
- After the inner loop ends, swap the current element with the minimum found.
- Repeat for the rest of the array.
- After each outer loop iteration, the smallest unsorted element is placed in its correct sorted position.

## C/C++ Implementation
```cpp
void SelectionSort(int array[], int n)
{
    for (int i = 0; i < n; i++)
    {
        int min = i;

        for (int j = i + 1; j < n; j++)
        {
            if (array[j] < array[i])
                min = j;
        }

        if (min != i)
            swap(array[i], array[min]);
    }
}
```
## Time Complexity:
- O(n<sup>2</sup>) → Best Case.
- O(n<sup>2</sup>) → Average Case.
- O(n<sup>2</sup>) → Worst Case.
