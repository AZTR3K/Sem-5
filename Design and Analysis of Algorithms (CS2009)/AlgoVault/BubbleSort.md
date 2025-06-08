 > # Bubble Sort

## Description
- Repeatedly compare adjacent elements in the array.
- If an element is greater than the next one, swap them.
- This process bubbles up the largest element to the end in each pass.
- Wth each outer loop iteration:
    - One less element needs to be checked (since the largest is already sorted).
    - Use a swapped flag to optimize: if no swaps occurred in a full pass, the array is already sorted → early exit.

```cpp
void BubbleSort(int array[], int n)
{
    for (int i = 0; i < n; i++)
    {
        bool swapped = false;
        for (int j = 0; j < n - 1; j++)
        {
            if (array[j] > array[j + 1])
            {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
                swapped = true;
            }
        }

        if (!swapped) break;
    }
}
```
## Time Complexity:
- O(n) -> Best Case.
- O(n<sup>2</sup>) -> Average Case.
- O(n<sup>2</sup>) -> Worst Case.
