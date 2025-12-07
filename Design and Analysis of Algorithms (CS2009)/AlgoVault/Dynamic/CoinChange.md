# Coin Change Problem (Minimum Coins)

## Description

The Coin Change problem (specifically the **Minimum Coin** variation) is a classic algorithmic problem. Given an infinite supply of coins of distinct denominations, the goal is to find the **minimum number of coins** needed to make up a specific total `amount`.

**Input:**

  * A set of coin denominations: $C = \{c_1, c_2, ..., c_n\}$
  * A target amount: $A$

**Output:**

  * The minimum count of coins required to sum exactly to $A$.

## C/C++ Implementation

```cpp
#include <climits>
#include <vector>
using namespace std;

int coinChange(vector<int> &coins, int n, int amount)
{
	if (n == 0)
		return INT_MAX;

	if (n == 1 && coins[0] == 1)
		return amount;

	if (amount == 0)
		return 0;

	if (coins[n - 1] > amount)
		return coinChange(coins, n - 1, amount);

	return min(coinChange(coins, n - 1, amount), coinChange(coins, n, amount - coins[n - 1]) + 1);
}

int coinChangeDynamic(vector<int> &coins, int amount)
{
	int n = coins.size();

	vector<vector<int>> res(n + 1, vector<int>(amount + 1));

	for (int j = 0; j <= amount; j++)
		res[0][j] = -1;

	if (coins[0] == 1)
	{
		for (int j = 0; j <= amount; j++)
			res[1][j] = j;
	}

	for (int i = 0; i <= n; i++)
		res[i][0] = 0;

	for (int i = 1; i <= n; i++)
	{
		for (int j = 1; j <= amount; j++)
		{
			if (coins[i - 1] > j)
				res[i][j] = res[i - 1][j];
			else
			{
				int drop = res[i - 1][j];
				int add = res[i][j - coins[i - 1]];

				if (add == -1 && drop == -1)
					res[i][j] = -1;
				else if (add == -1)
					res[i][j] = drop;
				else if (drop == -1)
					res[i][j] = add + 1;
				else
					res[i][j] = min(drop, add + 1);
			}
		}
	}
	return res[n][amount];
}
```

## Time Complexity

**1. Recursive Solution:**

  * **Time:** Exponential, roughly $O(2^n)$ (or more accurately, branching factor based on $A$).
      * This brute-force approach explores every possible combination of picking or dropping a coin.
  * **Space:** $O(A)$
      * Maximum recursion depth corresponds to the smallest coin repeatedly subtracted from the amount (e.g., $A/min(c_i)$).

**2. Dynamic Programming Solution:**

  * **Time:** $O(N \times A)$
      * Where $N$ is the number of coin types and $A$ is the target amount. We iterate through a table of size $(N+1) \times (A+1)$.
  * **Space:** $O(N \times A)$
      * Requires a 2D array to store the minimum coins for every sub-amount using every subset of coins.
