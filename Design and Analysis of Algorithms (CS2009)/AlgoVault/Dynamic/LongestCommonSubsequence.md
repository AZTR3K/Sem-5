# Longest Common Subsequence (LCS)

## Description

The Longest Common Subsequence (LCS) problem is a fundamental computer science problem. Given two sequences (strings) `stringA` and `stringB`, the goal is to find the length of the longest subsequence present in both of them.

A **subsequence** is a sequence that appears in the same relative order, but not necessarily contiguously. For example, "abc" is a subsequence of "aebdc".

**Input:**

  * String `stringA` of length $N$.
  * String `stringB` of length $M$.

**Output:**

  * The length of the longest subsequence common to both strings.

## C/C++ Implementation

```cpp
#include <string>
#include <vector>
using namespace std;

int longestCommonSubsequenceRecursive(string stringA, string stringB, int n, int m)
{
    if (n == 0 || m == 0)
        return 0;

    if (stringA[n - 1] == stringB[m - 1])
        return 1 + longestCommonSubsequenceRecursive(stringA, stringB, n - 1, m - 1);

    else
        return max(longestCommonSubsequenceRecursive(stringA, stringB, n, m - 1),
                   longestCommonSubsequenceRecursive(stringA, stringB, n - 1, m));
}

int longestCommonSubsequenceDynamic(string stringA, string stringB, int n, int m)
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
            if (stringA[i - 1] == stringB[j - 1])
                resultant[i][j] = 1 + resultant[i - 1][j - 1];
            else
                resultant[i][j] = max(resultant[i - 1][j], resultant[i][j - 1]);
        }
    }

    return resultant[n][m];
}
```

## Time Complexity

**1. Recursive Solution:**

  * **Time:** Exponential, roughly $O(2^n)$ (assuming $N \approx M$).
      * In the worst case (e.g., mismatching strings), the recursion branches twice at every step, exploring all possible subsequences.
  * **Space:** $O(N)$
      * Due to the recursion stack depth.

**2. Dynamic Programming Solution:**

  * **Time:** $O(N \times M)$
      * We fill a table of size $(N+1) \times (M+1)$ exactly once, performing constant work per cell.
  * **Space:** $O(N \times M)$
      * Due to the storage required for the `resultant` 2D vector.
