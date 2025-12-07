# Fibonacci Sequence

## Description

The Fibonacci sequence is a series of numbers where each number is the sum of the two preceding ones, usually starting with 0 and 1. The sequence typically goes: $0, 1, 1, 2, 3, 5, 8, 13, \dots$

The mathematical recurrence relation is defined as:
$$F(n) = F(n-1) + F(n-2)$$
With base cases:
$$F(0) = 0, \quad F(1) = 1$$

**Input:**

  * An integer index $n$.

**Output:**

  * The $n$-th number in the Fibonacci sequence.

## C/C++ Implementation

```cpp
#include <vector>
using namespace std;

int fibonacciRecursive(int n)
{
    if (n == 0)
        return 0;

    if (n == 1)
        return 1;

    return fibonacciRecursive(n - 1) + fibonacciRecursive(n - 2);
}

int fibonacciDynamic(int n)
{
    if (n == 0)
        return 0;

    if (n == 1)
        return 1;

    vector<int> resultant(n + 1);
    resultant[0] = 0;
    resultant[1] = 1;

    for (int i = 2; i <= n; i++)
    {
        resultant[i] = resultant[i - 1] + resultant[i - 2];
    }
    return resultant[n];
}

int fibonacciOptimised(int n)
{
    if (n == 0)
        return 0;

    if (n == 1)
        return 1;

    int a = 0, b = 1;

    for (int i = 2; i <= n; i++)
    {
        int c = a + b;
        a = b;
        b = c;
    }
    return b;
}
```

## Time Complexity

**1. Recursive Solution:**

  * **Time:** $O(2^n)$ (Exponential)
      * The recurrence tree grows exponentially because it recalculates the same values repeatedly (e.g., `fib(n-2)` is calculated twice, `fib(n-3)` three times, etc.).
  * **Space:** $O(n)$
      * Due to the recursion stack depth.

**2. Dynamic Programming (Tabulation):**

  * **Time:** $O(n)$ (Linear)
      * We calculate each number from $2$ to $n$ exactly once using a loop.
  * **Space:** $O(n)$
      * Due to the `vector` storing all intermediate values.

**3. Space Optimized Solution:**

  * **Time:** $O(n)$ (Linear)
      * Similar to the DP approach, we iterate $n$ times.
  * **Space:** $O(1)$ (Constant)
      * We only store the last two values (`a` and `b`) instead of the entire history.
