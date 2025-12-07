# Rod Cutting Problem

## Description

The Rod Cutting problem determines the maximum revenue obtainable by cutting up a rod of length $N$ and selling the pieces. You are given a list of prices where the $i$-th price corresponds to a rod piece of length $i$.

You can cut the rod into any number of pieces (including leaving it whole) to maximize profit.

**Input:**

  * A vector `price` where `price[i]` is the selling price of a rod piece of length `i+1`.
  * An integer `n` representing the total length of the rod.

**Output:**

  * The maximum possible revenue.

## C/C++ Implementation

```cpp
#include <algorithm>
#include <vector>
using namespace std;

int cutRodRecursive(vector<int> &price, int n)
{
    if (n == 0)
        return 0;

    int res = 0;

    for (int i = 1; i <= n; i++)
        res = max(res, price[i - 1] + cutRodRecursive(price, n - i));

    return res;
}

int cutRodDynamic(vector<int> &price, int n)
{
    vector<int> res(n + 1);
    res[0] = 0;

    for (int i = 1; i <= n; i++)
    {
        int max_val = 0;
        for (int j = 1; j <= i; j++)
        {
            max_val = max(max_val, price[j - 1] + res[i - j]);
        }
        res[i] = max_val;
    }
    return res[n];
}
```

## Time Complexity

**1. Recursive Solution:**

  * **Time:** Exponential, $O(2^N)$.
      * The algorithm considers every possible pattern of cuts (essentially generating all subsets of cut locations).
  * **Space:** $O(N)$
      * Due to the recursion stack depth.

**2. Dynamic Programming Solution:**

  * **Time:** $O(N^2)$.
      * We have nested loops: the outer loop runs $N$ times, and the inner loop runs $i$ times. The total operations are roughly $1 + 2 + \dots + N = \frac{N(N+1)}{2}$.
  * **Space:** $O(N)$.
      * Due to the `res` vector storing the optimal result for each length up to $N$.
