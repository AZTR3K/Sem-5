#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

int largest_square(const vector<vector<int>> &square, int r1, int c1, int r2,
                   int c2)
{
    // Boundary Checks
    if (r1 > r2 || c1 > c2)
        return 0;
    if (r1 < 0 || c1 < 0 || r2 >= square.size() || c2 >= square[0].size())
        return 0;

    // Base case, as one cell is a 1x1 square
    if (r1 == r2 && c1 == c2)
    {
        if (square[r1][c1] == 0)
            return 0;

        int length = 1;
        int rr = r2, cc = c2;
        while (rr + 1 < square.size() && cc + 1 < square[0].size())
        {
            // Check right side
            for (int i = r1; i <= rr; i++)
                if (square[i][cc + 1] == 0)
                    return length;

            // Check down side
            for (int j = c1; j <= cc; j++)
                if (square[rr + 1][j] == 0)
                    return length;

            // Check right diagonal
            if (square[rr + 1][cc + 1] == 1)
                length++, rr++, cc++;
            else
                break;
        }

        return length;
    }

    // Size of subsquare
    int size = r2 - r1 + 1;
    int n = size / 2;

    // Zero size square should have no square of 1's
    if (n == 0)
        return 0;

    int mid_r = r1 + n - 1;
    int mid_c = c1 + n - 1;

    int s1 = largest_square(square, r1, c1, mid_r, mid_c);
    int s2 = largest_square(square, r1, mid_c + 1, mid_r, c2);
    int s3 = largest_square(square, mid_r + 1, c1, r2, mid_c);
    int s4 = largest_square(square, mid_r + 1, mid_c + 1, r2, c2);

    return max({s1, s2, s3, s4});
}

int main()
{
    freopen("q1_input.txt", "r", stdin);
    freopen("q1_output.txt", "w", stdout);

    int test_cases;
    cin >> test_cases;

    for (int t = 1; t <= test_cases; t++)
    {
        int n;
        cin >> n;

        vector<vector<int>> square(n, vector<int>(n));
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                cin >> square[i][j];

        cout << "Test Case #" << t << "\n";
        cout << "Matrix Size: " << n << " x " << n << "\n";
        cout << "Matrix:\n";
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
                cout << square[i][j] << "   ";
            cout << "\n";
        }

        int result = largest_square(square, 0, 0, n - 1, n - 1);
        cout << "Max square length: " << result << "\n\n\n";
    }
}
