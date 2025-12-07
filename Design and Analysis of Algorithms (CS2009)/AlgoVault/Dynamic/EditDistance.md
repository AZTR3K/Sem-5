# Edit Distance (Levenshtein Distance)

## Description

The Edit Distance problem (specifically Levenshtein Distance) measures the similarity between two strings. The goal is to find the **minimum number of operations** required to convert string `s1` into string `s2`.

The allowed operations are:

1.  **Insertion** of a character.
2.  **Removal** (Deletion) of a character.
3.  **Replacement** (Substitution) of a character.

**Input:**

  * String `s1` of length `n`.
  * String `s2` of length `m`.

**Output:**

  * The minimum integer cost (number of edits) to transform `s1` to `s2`.

## C/C++ Implementation

```cpp
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

int editDistanceRecursive(string s1, string s2, int n, int m)
{
    // If s1 empty, it will take m insertions to match s2
    if (n == 0)
        return m;

    // If s2 empty, it will take n removals to make s1 empty as well
    if (m == 0)
        return n;

    // Pattern match
    if (s1[n - 1] == s2[m - 1])
        return editDistanceRecursive(s1, s2, n - 1, m - 1);
    else
        return 1
                + min({editDistanceRecursive(s1, s2, n, m - 1),     // Insertion
                       editDistanceRecursive(s1, s2, n - 1, m - 1), // Replacement
                       editDistanceRecursive(s1, s2, n - 1, m)});   // Removal
}

int editDistanceDynamic(string s1, string s2, int n, int m)
{
    vector<vector<int>> resultant(n + 1, vector<int>(m + 1));

    for (int i = 0; i <= n; i++)
        resultant[i][0] = i;

    for (int j = 0; j <= m; j++)
        resultant[0][j] = j;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (s1[i - 1] == s2[j - 1])
                resultant[i][j] = resultant[i - 1][j - 1];
            else
                resultant[i][j]
                    = 1 + min({resultant[i][j - 1], resultant[i - 1][j - 1], resultant[i - 1][j]});
        }
    }
    return resultant[n][m];
}
```

## Time Complexity

**1. Recursive Solution:**

  * **Time:** Exponential, approximately $O(3^M)$ (where $M$ is the length of the strings).
      * In the worst case (where no characters match), the algorithm branches into 3 sub-problems at every step.
  * **Space:** $O(M)$
      * Due to the recursion stack depth.

**2. Dynamic Programming Solution:**

  * **Time:** $O(N \times M)$
      * We fill a table of size $(N+1) \times (M+1)$ exactly once.
  * **Space:** $O(N \times M)$
      * Due to the storage required for the `resultant` 2D vector.
