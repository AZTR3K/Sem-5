#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

vector<int> getDigits(long long num)
{
    vector<int> digits;
    while (num > 0)
    {
        digits.push_back(num % 10);
        num /= 10;
    }
    reverse(digits.begin(), digits.end());
    return digits;
}

long long count(int pos, bool tight, bool has_bad, vector<int> digits, int n)
{
    if (pos == n)
        return has_bad ? 0 : 1;

    int limit = 9;
    if (tight)
        limit = digits[pos];

    long long total = 0;

    for (int i = 0; i <= limit; i++)
    {
        bool next_tight = tight && (i == limit);
        bool next_has_bad = has_bad || i == 4 || i == 9;
        total += count(pos + 1, next_tight, next_has_bad, digits, n);
    }

    return total;
}

long long countValid(long long num)
{
    vector<int> digits = getDigits(num);
    return count(0, true, false, digits, digits.size());
}

long long countR(long long L, long long R)
{
    if (L == 0)
        return countValid(R) - 1;
    return countValid(R) - countValid(L - 1);
}

long long countDP(long long num)
{
    long long count = 0;
    vector<int> digits = getDigits(num);
    int n = digits.size();

    vector<vector<vector<long long>>> res(
        n + 1, vector<vector<long long>>(2, vector<long long>(2)));

    // Base case
    for (int tight = 0; tight < 2; tight++)
        for (int has_bad = 0; has_bad < 2; has_bad++)
            res[n][tight][has_bad] = has_bad ? 0 : 1;

    // Filling the table backwards as we need pos + 1
    for (int pos = n - 1; pos >= 0; pos--)
    {
        for (int tight = 0; tight < 2; tight++)
        {
            for (int has_bad = 0; has_bad < 2; has_bad++)
            {
                long long total = 0;

                int limit = 9;
                if (tight == 1)
                    limit = digits[pos];

                for (int i = 0; i <= limit; i++)
                {
                    bool next_tight = tight && i == limit;
                    bool next_has_bad = has_bad || i == 4 || i == 9;
                    total += res[pos + 1][next_tight][next_has_bad];
                }
                res[pos][tight][has_bad] = total;
            }
        }
    }
    return res[0][1][0];
}

long long countD(long long L, long long R)
{
    if (L == 0)
        return countDP(R) - 1;
    return countDP(R) - countDP(L - 1);
}

int main()
{
    freopen("q6_input.txt", "r", stdin);
    freopen("q6_output.txt", "w", stdout);

    int t;
    cin >> t;

    while (t--)
    {
        long long L, R;
        cin >> L >> R;

        cout << "Recursive: Valid numbers between " << L << " and " << R << ": "
             << countR(L, R) << "\n";
        cout << "Dynamic: Valid numbers between " << L << " and " << R << ": "
             << countD(L, R) << "\n";
    }
}
