# Subset Sum Problem

## Description

The Subset Sum problem is a decision problem: given a set of non-negative integers and a target value `sum`, determine if any subset of the given numbers adds up exactly to that `sum`.

It is a special case of the Knapsack problem and is NP-Complete.

**Input:**

  * A vector of integers `arr`.
  * An integer `sum` (target value).

**Output:**

  * `true` if a subset exists that sums to the target, `false` otherwise.

## C/C++ Implementation

```cpp
#include <vector>
using namespace std;

bool isSubsetSumRecursive(vector<int> &arr, int n, int sum)
{
    if (n == 0)
        return false;

    if (sum == 0)
        return true;

    if (arr[n - 1] > sum)
        return isSubsetSumRecursive(arr, n - 1, sum);

    return isSubsetSumRecursive(arr, n - 1, sum)
           || isSubsetSumRecursive(arr, n - 1, sum - arr[n - 1]);
}

bool isSubsetSumDynamic(vector<int> &arr, int sum)
{
    int n = arr.size();
    vector<vector<bool>> res(n + 1, vector<bool>(sum + 1));

    for (int j = 0; j <= sum; j++)
        res[0][j] = false;

    for (int i = 0; i <= n; i++)
        res[i][0] = true;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= sum; j++)
        {
            if (arr[i - 1] > j)
                res[i][j] = res[i - 1][j];
            else
                res[i][j] = res[i - 1][j] || res[i - 1][j - arr[i - 1]];
        }
    }
    return res[n][sum];
}
```

## Time Complexity

**1. Recursive Solution:**

  * **Time:** Exponential, $O(2^N)$.
      * In the worst case, we try every possible subset.
  * **Space:** $O(N)$.
      * Due to recursion stack depth.

**2. Dynamic Programming Solution:**

  * **Time:** $O(N \times \text{sum})$.
      * This is **pseudo-polynomial**. It depends on the numeric value of `sum`, not just the number of elements $N$. If `sum` is very large ($2^N$), this is worse than exponential.
  * **Space:** $O(N \times \text{sum})$.
      * Due to the 2D boolean table.
