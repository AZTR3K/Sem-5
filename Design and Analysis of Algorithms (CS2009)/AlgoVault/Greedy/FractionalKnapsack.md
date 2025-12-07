# Fractional Knapsack Problem

## Description

The Fractional Knapsack problem is a variation of the classic Knapsack problem where you can take **fractions** of an item. The goal is to maximize the total value in a knapsack of capacity $M$.

Because we can split items, this problem can be solved optimally using a **Greedy Algorithm**:

1.  Calculate the **value-to-weight ratio** ($v_i / w_i$) for every item.
2.  Sort all items in **descending order** based on this ratio.
3.  Iterate through the sorted items:
      * If the item fits entirely, take it all.
      * If the item does not fit entirely, take the remaining capacity fraction of the item to fill the knapsack exactly.

**Input:**

  * A set of items, each with a `weight` and `value`.
  * A maximum capacity $M$.

**Output:**

  * The maximum total profit achievable (can be a floating-point value).

## C/C++ Implementation

```cpp
#include <iostream>
#include <vector>
using namespace std;

struct item
{
    int weight;
    int value;
    float val_wt;

    item() {}
    item(int w, int v) : weight(w), value(v)
    {
        val_wt = v / static_cast<float>(w);
    }
};

void display(vector<int> array)
{
    for (int num : array)
        cout << num << " ";
    cout << "\n";
}

void merge(vector<item> &array, int low, int mid, int high)
{
    int lsize = mid - low + 1;
    int rsize = high - mid;
    vector<item> left_array(lsize);
    vector<item> right_array(rsize);

    for (int i = 0; i < lsize; i++)
        left_array[i] = array[low + i];

    for (int i = 0; i < rsize; i++)
        right_array[i] = array[mid + i + 1];

    int i = 0, j = 0, k = low;
    while (i < lsize && j < rsize)
    {
        // Sort descending based on value/weight ratio
        if (left_array[i].val_wt >= right_array[j].val_wt)
            array[k++] = left_array[i++];
        else
            array[k++] = right_array[j++];
    }
    while (i < lsize)
        array[k++] = left_array[i++];

    while (j < rsize)
        array[k++] = right_array[j++];
}

void sort(vector<item> &array, int low, int high)
{
    if (low < high)
    {
        int mid = low + (high - low) / 2;
        sort(array, low, mid);
        sort(array, mid + 1, high);
        merge(array, low, mid, high);
    }
}

int fractional_knapsack(vector<item> array, int n, int m)
{
    int profit = 0;

    // Sort items by value/weight ratio
    sort(array, 0, n - 1);

    for (int i = 0; i < n; i++)
    {
        // If the item fits entirely
        if (m >= array[i].weight)
        {
            profit += array[i].value;
            m -= array[i].weight;
        }
        else
        {
            // Take fraction of the item and break (knapsack full)
            profit += array[i].val_wt * m;
            break;
        }
    }

    return profit;
}

int main()
{
    int n = 3;
    int m = 10;
    vector<int> weights = {10, 7, 3};
    vector<int> values = {1000, 800, 700};

    vector<item> array;
    for (int i = 0; i < n; i++)
    {
        array.push_back(item(weights[i], values[i]));
    }

    cout << "Values: ";
    display(values);
    cout << "Weights: ";
    display(weights);
    cout << "\nMax profit: " << fractional_knapsack(array, n, m) << "\n";
}
```

## Time Complexity

  * **Sorting:** $O(N \log N)$
      * The items are sorted based on their value/weight ratio using Merge Sort.
  * **Selection:** $O(N)$
      * We iterate through the sorted items once to fill the knapsack.
  * **Total:** $O(N \log N)$.
