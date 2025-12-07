# Maximum Subarray Sum

## Description

The Maximum Subarray Sum problem asks you to find the contiguous subarray (containing at least one number) within a one-dimensional array `nums` that has the largest sum.

**Input:**

  * A vector of integers `nums`.

**Output:**

  * The value of the largest sum found in any contiguous subarray.

## C/C++ Implementation

```cpp
#include <algorithm>
#include <climits>
#include <vector>
using namespace std;

int crossSum(vector<int> &nums, int low, int mid, int high)
{
    int sum = 0;
    int lsum = INT_MIN;
    for (int i = mid; i >= low; i--)
    {
        sum += nums[i];
        lsum = max(lsum, sum);
    }

    sum = 0;
    int rsum = INT_MIN;
    for (int i = mid + 1; i <= high; i++)
    {
        sum += nums[i];
        rsum = max(rsum, sum);
    }
    return lsum + rsum;
}

int maximumSum(vector<int> &nums, int low, int high)
{
    if (low > high)
        return 0;

    if (low == high)
        return nums[low];

    int mid = low + (high - low) / 2;
    int lsum = maximumSum(nums, low, mid);
    int rsum = maximumSum(nums, mid + 1, high);
    int csum = crossSum(nums, low, mid, high);

    return max({lsum, csum, rsum});
}

int kadaneAlgorithm(vector<int> &nums)
{
    int maximum = nums[0];

    for (int i = 1; i < nums.size(); i++)
    {
        nums[i] = max(nums[i], nums[i] + nums[i - 1]);
        maximum = max(maximum, nums[i]);
    }
    return maximum;
}
```

## Time Complexity

**1. Divide and Conquer (`maximumSum`):**

  * **Time:** $O(N \log N)$
      * Similar to Merge Sort, the problem is split into halves ($\log N$ levels), and at each level, we perform a linear scan ($O(N)$) to find the crossing sum.
  * **Space:** $O(\log N)$
      * Due to the recursion stack depth.

**2. Kadane’s Algorithm (`kadaneAlgorithm`):**

  * **Time:** $O(N)$
      * We pass through the array exactly once. This is the optimal time complexity for this problem.
  * **Space:** $O(1)$
      * This specific implementation modifies the input array `nums` in-place to store cumulative sums. If the input array must be preserved, you would need $O(N)$ space for a DP array or just $O(1)$ variables to track the `current_sum`.
