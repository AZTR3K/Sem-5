# Catalan Numbers

## Description

The Catalan numbers are a sequence of natural numbers that appear in many combinatorial problems involving recursively defined structures. The $n$-th Catalan number, denoted as $C_n$, satisfies the recurrence relation:

$$C_n = \sum_{i=0}^{n-1} C_i C_{n-1-i}$$

Common applications include counting:

  * The number of distinct **Binary Search Trees (BSTs)** with $n$ keys.
  * The number of valid expressions containing $n$ pairs of parentheses.
  * The number of ways to triangulate a convex polygon with $n+2$ sides.

**Input:**

  * An integer $n$.

**Output:**

  * The $n$-th Catalan number ($C_n$).

## C/C++ Implementation

```cpp
#include <vector>
using namespace std;

int catalanRecursive(int n)
{
    if (n <= 1)
        return 1;

    int num = 0;

    for (int i = 0; i < n; i++)
        num += catalanRecursive(i) * catalanRecursive(n - i - 1);

    return num;
}

int catalanDynamic(int n)
{
    if (n == 0)
        return 1;

    vector<int> res(n + 1);
    res[0] = 1;
    res[1] = 1;

    for (int i = 2; i <= n; i++)
    {
        int num = 0;
        for (int j = 0; j < i; j++)
        {
            num += res[j] * res[i - j - 1];
        }
        res[i] = num;
    }
    return res[n];
}
```

## Time Complexity

**1. Recursive Solution:**

  * **Time:** Exponential, roughly $O(4^n / n^{1.5})$.
      * This approach is extremely inefficient because it recomputes the same values (overlapping subproblems) repeatedly.
  * **Space:** $O(N)$
      * Due to the recursion stack depth.

**2. Dynamic Programming Solution:**

  * **Time:** $O(N^2)$
      * We use two nested loops: the outer loop runs $N$ times, and the inner loop runs $i$ times. Summing $1 + 2 + ... + N$ results in quadratic time.
  * **Space:** $O(N)$
      * We use a vector of size $N+1$ to store the calculated Catalan numbers.
