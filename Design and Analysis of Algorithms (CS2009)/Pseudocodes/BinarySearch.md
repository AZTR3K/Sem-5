# BinarySearch
- Works on a sorted array.
- Set initial boundaries i (start) and j (end).
- Calculate the middle index mid = (i + j) / 2.
- Compare the target with array[mid].

## Decision Steps
- If i > j:
- → The target is not present → return -1.

- If array[mid] == target:
- → Target found → return mid.

- If array[mid] > target:
- → Recurse on the left half of the array.

- If array[mid] < target:
- → Recurse on the right half of the array.

## Python Implementation
```python
def BinarySearch(array, i, j, target):
    if i > j:
        return -1  # Not found

    mid = (i + j) // 2

    if array[mid] == target:
        return mid

    elif array[mid] > target:
        return BinarySearch(array, i, mid - 1, target)  # Search left half

    else:
        return BinarySearch(array, mid + 1, j, target)  # Search right half

```
