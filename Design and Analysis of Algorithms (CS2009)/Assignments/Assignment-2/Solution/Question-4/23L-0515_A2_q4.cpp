#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

vector<int> A, B, C;

void display(vector<int> array)
{
    for (int num : array)
        cout << num << " ";
    cout << "\n";
}

int f_recursive(int day, char last)
{
    if (day == 0)
        return 0;

    if (last == 'A')
        return max(f_recursive(day - 1, 'B') + B[day - 1],
                   f_recursive(day - 1, 'C') + C[day - 1]);
    else if (last == 'B')
        return max(f_recursive(day - 1, 'A') + A[day - 1],
                   f_recursive(day - 1, 'C') + C[day - 1]);
    else if (last == 'C')
        return max(f_recursive(day - 1, 'A') + A[day - 1],
                   f_recursive(day - 1, 'B') + B[day - 1]);
    else
        return max({f_recursive(day - 1, 'A') + A[day - 1],
                    f_recursive(day - 1, 'B') + B[day - 1],
                    f_recursive(day - 1, 'C') + C[day - 1]});
}

int f_dynamic(int day)
{
    vector<vector<int>> resultant(day + 1, vector<int>(4, 0));

    for (int i = 1; i <= day; i++)
    {
        resultant[i][0]
            = A[i - 1] + max(resultant[i - 1][1], resultant[i - 1][2]);

        resultant[i][1]
            = B[i - 1] + max(resultant[i - 1][0], resultant[i - 1][2]);

        resultant[i][2]
            = C[i - 1] + max(resultant[i - 1][0], resultant[i - 1][1]);

        resultant[i][3]
            = max({resultant[i][0], resultant[i][1], resultant[i][2]});
    }

    return resultant[day][3];
}

int main()
{
    freopen("q4_input.txt", "r", stdin);
    freopen("q4_output.txt", "w", stdout);

    int d;
    cin >> d;

    A.resize(d);
    B.resize(d);
    C.resize(d);

    for (int i = 0; i < d; i++)
    {
        cin >> A[i];
        cin >> B[i];
        cin >> C[i];
    }

    cout << "A: ";
    display(A);
    cout << "B: ";
    display(B);
    cout << "C: ";
    display(C);

    cout << "\n";
    cout << "Maximum Happiness recursive: " << f_recursive(d, 'S') << "\n";
    cout << "Maximum Happiness dynamic: " << f_dynamic(d) << "\n";
}
