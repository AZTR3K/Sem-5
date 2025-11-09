#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>

using namespace std;

using ll = long long;

ll dp[20][101][2];
string s;
int K;

ll count_recursive(int pos, int sumMod, bool tight)
{
    if (pos == s.length())
    {
        return (sumMod == 0) ? 1 : 0;
    }

    if (dp[pos][sumMod][tight] != -1)
    {
        return dp[pos][sumMod][tight];
    }

    ll ans = 0;
    int limit = tight ? (s[pos] - '0') : 9;

    for (int digit = 0; digit <= limit; digit++)
    {
        int new_sumMod = (sumMod + digit) % K;
        bool new_tight = tight && (digit == limit);
        ans += count_recursive(pos + 1, new_sumMod, new_tight);
    }

    return dp[pos][sumMod][tight] = ans;
}

ll solve(long long N)
{
    if (N < 0)
        return 0;
    if (N == 0)
        return 1;

    s = to_string(N);
    memset(dp, -1, sizeof(dp));
    return count_recursive(0, 0, true);
}

int main()
{
    freopen("q7_input.txt", "r", stdin);
    freopen("q7_output.txt", "w", stdout);

    int test_cases;
    cin >> test_cases;

    while (test_cases--)
    {
        long long L, R;
        cin >> L >> R >> K;

        ll ans = solve(R) - solve(L - 1);
        cout << ans << endl;
    }
}
