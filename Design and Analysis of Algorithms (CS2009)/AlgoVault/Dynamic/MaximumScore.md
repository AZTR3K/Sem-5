# Maximum Weight Path (Alignment Score)

## Description

This problem involves finding the path with the **maximum accumulated score** in a grid from `(0, 0)` to `(n, m)`.

Unlike standard grid problems where costs are associated with the cells themselves, in this variation, the costs (or scores) are associated with the **transitions** (edges) between cells.

For every cell `(i, j)` in the grid `W`, there are three possible movements, each with a specific weight:

1.  **Right:** Move to `(i, j+1)` with score `W[i][j].right`.
2.  **Down:** Move to `(i+1, j)` with score `W[i][j].down`.
3.  **Diagonal:** Move to `(i+1, j+1)` with score `W[i][j].diag`.

This structure is nearly identical to the **Needleman-Wunsch algorithm** used in bioinformatics for Global Sequence Alignment (where diagonal represents a match/mismatch, and straight moves represent gaps).

**Input:**

  * A 2D grid `W` where each element contains `{right, down, diag}` scores.
  * Target row index `n` and column index `m`.

**Output:**

  * The maximum score possible to reach position `(n, m)` starting from `(0, 0)`.

## C/C++ Implementation

```cpp
#include <algorithm>
#include <vector>
using namespace std;

struct Cell
{
    int right;
    int down;
    int diag;
};

int maximumScoreRecursive(vector<vector<Cell>> &W, int n, int m)
{
    if (n == 0 && m == 0)
        return 0;

    if (n == 0)
        return maximumScoreRecursive(W, n, m - 1) + W[n][m - 1].right;

    if (m == 0)
        return maximumScoreRecursive(W, n - 1, m) + W[n - 1][m].down;

    return max({maximumScoreRecursive(W, n - 1, m - 1) + W[n - 1][m - 1].diag,
                maximumScoreRecursive(W, n - 1, m) + W[n - 1][m].down,
                maximumScoreRecursive(W, n, m - 1) + W[n][m - 1].right});
}

int maximumScoreDynamic(vector<vector<Cell>> &W, int n, int m)
{
    vector<vector<int>> res(n + 1, vector<int>(m + 1));
    res[0][0] = 0;

    for (int j = 1; j <= m; j++)
        res[0][j] = res[0][j - 1] + W[0][j - 1].right;

    for (int i = 1; i <= n; i++)
        res[i][0] = res[i - 1][0] + W[i - 1][0].down;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
            res[i][j] = max({
                res[i - 1][j - 1] + W[i - 1][j - 1].diag, // Diagonal
                res[i - 1][j] + W[i - 1][j].down,         // From Top
                res[i][j - 1] + W[i][j - 1].right         // From Left
            });
    }

    return res[n][m];
}
```

## Time Complexity

**1. Recursive Solution:**

  * **Time:** Exponential, roughly $O(3^{\max(N, M)})$.
      * Each step branches into three sub-problems, leading to massive redundant calculations.
  * **Space:** $O(\max(N, M))$
      * Due to the recursion stack depth.

**2. Dynamic Programming Solution:**

  * **Time:** $O(N \times M)$
      * We iterate through the `(n+1) x (m+1)` grid exactly once.
  * **Space:** $O(N \times M)$
      * Due to the storage required for the `res` 2D vector.
