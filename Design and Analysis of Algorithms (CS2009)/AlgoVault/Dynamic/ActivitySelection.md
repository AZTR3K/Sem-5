# Activity Selection Problem

## Description

Given a set of $N$ activities, each with a specific `start_time` and `finish_time`, the objective is to select the **maximum number of non-overlapping activities** that a single person can perform.

A person can work on only one activity at a time. Two activities are considered compatible (non-overlapping) if the start time of the new activity is greater than or equal to the finish time of the previously selected activity.

**Input:**

  * A list of start times: $S = \{s_1, s_2, ..., s_n\}$
  * A list of finish times: $F = \{f_1, f_2, ..., f_n\}$

**Output:**

  * The count of the maximum set of activities that can be executed without conflict.

## C/C++ Implementation

```cpp
#include <vector>
using namespace std;

struct activity
{
    int start_time;
    int finish_time;
};

void merge(vector<activity> &activities, int low, int mid, int high)
{
    int lsize = mid - low + 1;
    int rsize = high - mid;

    vector<activity> l(lsize);
    vector<activity> r(rsize);

    for (int i = 0; i < lsize; i++)
        l[i] = activities[low + i];

    for (int j = 0; j < rsize; j++)
        r[j] = activities[mid + j + 1];

    int i = 0, j = 0, k = low;
    while (i < lsize && j < rsize)
    {
        if (l[i].finish_time <= r[j].finish_time)
            activities[k++] = l[i++];
        else
            activities[k++] = r[j++];
    }

    while (i < lsize)
        activities[k++] = l[i++];

    while (j < rsize)
        activities[k++] = r[j++];
}

void mergeSort(vector<activity> &activities, int low, int high)
{
    if (low < high)
    {
        int mid = low + (high - low) / 2;
        mergeSort(activities, low, mid);
        mergeSort(activities, mid + 1, high);
        merge(activities, low, mid, high);
    }
}

int activitySelection(vector<int> &start, vector<int> &finish)
{
    vector<activity> activities;

    for (int i = 0; i < start.size(); i++)
        activities.push_back({start[i], finish[i]});

    mergeSort(activities, 0, activities.size() - 1);

    int j = 0;
    int count = 1;

    for (int i = 1; i < activities.size(); i++)
    {
        if (activities[i].start_time >= activities[j].finish_time)
        {
            count++;
            j = i;
        }
    }

    return count;
}
```

## Time Complexity

  * **Sorting:** $O(N \log N)$ (using Merge Sort).
  * **Selection:** $O(N)$ (one linear pass through the sorted activities).
  * **Total:** $O(N \log N)$.
