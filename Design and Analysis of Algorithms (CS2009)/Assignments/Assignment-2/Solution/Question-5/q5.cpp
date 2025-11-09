#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

vector<int> weights;
vector<int> values;

void display(vector<int> &array)
{
    for (int num : array)
        cout << num << " ";
    cout << "\n";
}

int f_recursive(int n, int m)
{
    if (n == 0 || m == 0)
        return 0;

    if (m < weights[n - 1])
        return f_recursive(n - 1, m);

    return max(f_recursive(n - 1, m),
               f_recursive(n - 1, m - weights[n - 1]) + values[n - 1]);
}

int f_dynamic(int n, int m)
{
    vector<vector<int>> resultant(n + 1, vector<int>(m + 1));

    for (int i = 0; i <= n; i++)
        resultant[i][0] = 0;

    for (int j = 0; j <= m; j++)
        resultant[0][j] = 0;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (j < weights[i - 1])
                resultant[i][j] = resultant[i - 1][j];
            else
            {
                resultant[i][j]
                    = max(resultant[i - 1][j],
                          resultant[i - 1][j - weights[i - 1]] + values[i - 1]);
            }
        }
    }
    return resultant[n][m];
}

int main()
{
    freopen("q5_input.txt", "r", stdin);
    freopen("q5_output.txt", "w", stdout);

    int n, m;
    cin >> n;
    cin >> m;

    weights.resize(n);
    values.resize(n);

    for (int i = 0; i < n; i++)
    {
        cin >> weights[i];
        cin >> values[i];
    }

    cout << "Bag Capacity: " << m << "\n";
    cout << "Weights: ";
    display(weights);
    cout << "Values: ";
    display(values);

    cout << "\n";
    cout << "Max profit using recursive: " << f_recursive(n, m) << "\n";
    cout << "Max profit using dp: " << f_dynamic(n, m) << "\n";
}
