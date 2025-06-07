```python

BinarySearch(array, i, j, target)
    if (i > j)
        return - 1  # Not found

    mid = (i + j) / 2

    if (array[mid] == target)
        return mid

    else if (array[mid] > target)
        return BinarySearch(array, i, mid - 1, target) # Search the left half

    else
        return BinarySearch(array, mid + 1, j, target) # Search the right half
```
