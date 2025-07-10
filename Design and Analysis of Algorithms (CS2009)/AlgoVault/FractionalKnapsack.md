> # Fractional Knapsack Algorithm

## Description
The Fractional Knapsack Problem is a greedy algorithm problem where:
- You're given n items, each with a profit and a weight.
- You have a knapsack with a maximum capacity w.
- You can take fractions of items.
- Your goal is to maximize total profit while staying within the weight limit.

## Strategy
- Calculate the profit-to-weight ratio for each item.
- Sort all items in descending order of this ratio.
- Greedily pick items with the highest ratio until the knapsack is full.
- If only part of an item can be taken, take the fraction that fits.

## C/C++ Implementation
```cpp
struct item
{
    int profit, weight;
    float ratio;
};

int partition(item objects[], int low, int high)
{
    float pivot = objects[low].ratio;
    int p = low + 1;
    int q = high;

    while (p <= q)
    {
        while (objects[p].ratio > pivot && p <= high) p++;

        while (objects[q].ratio <= pivot && q >= low) q--;

        if (p < q) swap(objects[p], objects[q]);
    }

    swap(objects[low], objects[q]);
    return q;
}

void quickSort(item objects[], int low, int high)
{
    if (low < high)
    {
        int pivotIndex = partition(objects, low, high);

        quickSort(objects, low, pivotIndex - 1);
        quickSort(objects, pivotIndex + 1, high);
    }
}

float knapsack(item objects[], int w, int n)
{
    float maxProfit = 0;

    quickSort(objects, 0, n - 1);

    for (int i = 0; i < n; i++)
    {
        if (objects[i].weight <= w)
        {
            maxProfit += objects[i].ratio * objects[i].weight;
            w -= objects[i].weight;
        }
        else
        {
            maxProfit += objects[i].ratio * w;
            break;
        }
    }

    return maxProfit;
}

int main()
{
    int profits[] = {10, 5, 15, 7, 6, 18, 3};
    int weights[] = {2, 3, 5, 7, 1, 4, 1};
    int n = 7;
    int w = 15;

    item objects[n];

    for (int i = 0; i < n; i++)
    {
        objects[i].profit = profits[i];
        objects[i].weight = weights[i];
        objects[i].ratio = profits[i] / float(weights[i]);
    }

    float maxProfit = knapsack(objects, w, n);
    cout << "Max Profit: " << maxProfit << "\n";
}
```

### Time Complexity:
- O(n) -> Ratio Calculation
- O(n log n) -> Sorting
- O(n) -> Knapsack loop
- O(n log n) -> Total
