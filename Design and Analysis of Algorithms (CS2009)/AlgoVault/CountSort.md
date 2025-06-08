> # Count Sort

## Description
- Suitable for sorting non-negative integers within a known range `0` to `k-1`.
- Create a frequency array of size `k`, initialized to `0`.
- Traverse the input array and count the occurrences of each element.
- Reconstruct the sorted array by placing each number `j` as many times as it appeared (tracked in the frequency array).
- Efficient for small ranges of integers, but not suitable for large or negative ranges.

## C/C++ Implementation
```cpp
void CountSort(int array[], int k, int n)
{
    int* freqArray = new int[k]();

    for (int i = 0; i < n; i++)
    {
        freqArray[array[i]] += 1;
    }

    int i = 0;
    for (int j = 0; j < k; j++)
    {
        for (int l = 0; l < freqArray[j]; l++)
        {
            array[i] = j;
            i++;
        }
    }

    delete[] freqArray;
    freqArray = nullptr;
}
```

## Time Complexity:
- O(n + k) → Best Case.
- O(n + k) → Average Case.
- O(n + k) → Worst Case.

