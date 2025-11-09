#include <algorithm>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

using BalancePair = pair<int, int>;

struct PairHasher
{
    size_t operator()(const BalancePair &p) const
    {
        auto hash1 = hash<int>{}(p.first);
        auto hash2 = hash<int>{}(p.second);
        return hash1 ^ (hash2 << 1);
    }
};

vector<BalancePair> prefix_balances;

int solve(int L, int R)
{
    if (L >= R)
    {
        return 0;
    }

    int mid = L + (R - L) / 2;

    int len_left = solve(L, mid);
    int len_right = solve(mid + 1, R);

    int max_crossing = 0;
    unordered_map<BalancePair, int, PairHasher> left_balances;

    for (int i = L; i <= mid; ++i)
    {
        BalancePair b = prefix_balances[i];
        if (left_balances.find(b) == left_balances.end())
        {
            left_balances[b] = i;
        }
    }

    for (int j = mid + 1; j <= R; ++j)
    {
        BalancePair b = prefix_balances[j + 1];

        if (left_balances.find(b) != left_balances.end())
        {
            int i_idx = left_balances[b];
            int len = j - i_idx + 1;
            max_crossing = max(max_crossing, len);
        }
    }

    return max({len_left, len_right, max_crossing});
}

int longestBalanced(const string &s)
{
    int n = s.length();
    if (n < 2)
        return 0;

    prefix_balances.assign(n + 1, {0, 0});

    int b1 = 0, b2 = 0;
    for (int i = 0; i < n; ++i)
    {
        if (s[i] == 'A')
            b1++;
        else if (s[i] == 'T')
            b1--;
        else if (s[i] == 'C')
            b2++;
        else if (s[i] == 'G')
            b2--;
        prefix_balances[i + 1] = {b1, b2};
    }

    return solve(0, n - 1);
}

int main()
{
    freopen("q2_input.txt", "r", stdin);
    freopen("q2_output.txt", "w", stdout);

    int test_cases;
    cin >> test_cases;

    for (int t = 1; t <= test_cases; t++)
    {
        int n;
        cin >> n;

        string s;
        cin >> s;

        cout << "Test Case #" << t << "\n";
        cout << "String Length: " << n << "\n";
        cout << "String: " << s << "\n";

        int result = longestBalanced(s);

        cout << "Max balanced length: " << result << "\n\n\n";
    }
}
