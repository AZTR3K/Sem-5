# Binary Knapsack Problem (0/1 Knapsack)

## Description

Given a set of $N$ items, each with a specific **weight** and **value**, the objective is to determine the maximum value that can be included in a knapsack of capacity $M$.

This is a "0/1" problem because you cannot split an item; you must either take the item (1) or leave it (0) entirely.

**Input:**

  * A set of item weights: $W = \{w_1, w_2, ..., w_n\}$
  * A set of item values: $V = \{v_1, v_2, ..., v_n\}$
  * A maximum knapsack capacity: $M$

**Output:**

  * The maximum total value possible such that the sum of the weights is less than or equal to $M$.

## C/C++ Implementation

```cpp
#include <vector>
using namespace std;

vector<int> weights = {2, 1, 3, 4, 5};
vector<int> values = {20, 15, 12, 20, 18};

int binaryKnapsackRecursive(int n, int m)
{
    if (n == 0 || m == 0)
        return 0;

    if (m < weights[n - 1])
        return binaryKnapsackRecursive(n - 1, m);
    else
        return max(binaryKnapsackRecursive(n - 1, m),
                   binaryKnapsackRecursive(n - 1, m - weights[n - 1])
                       + values[n - 1]);
}

int binaryKnapsackDynamic(int n, int m)
{
    vector<vector<int>> resultant(n + 1, vector<int>(m + 1));

    for (int i = 0; i <= n; i++)
        resultant[i][0] = 0;

    for (int j = 0; j <= m; j++)
        resultant[0][j] = 0;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (j < weights[i - 1])
                resultant[i][j] = resultant[i - 1][j];
            else
                resultant[i][j]
                    = max(resultant[i - 1][j],
                          resultant[i - 1][j - weights[i - 1]] + values[i - 1]);
        }
    }

    return resultant[n][m];
}
```

## Time Complexity

**1. Recursive Solution:**

  * **Time:** $O(2^N)$
      * Without memoization, the recursive tree grows exponentially because it recalculates subproblems repeatedly.
  * **Space:** $O(N)$
      * Due to the recursion stack depth.

**2. Dynamic Programming Solution:**

  * **Time:** $O(N \times M)$
      * We fill a table of size $(N+1) \times (M+1)$, performing constant time operations for each cell. This is **pseudo-polynomial** time (depends on the magnitude of capacity $M$).
  * **Space:** $O(N \times M)$
      * Due to the storage required for the `resultant` 2D vector.
