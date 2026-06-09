#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s, t;
    cin >> s;
    cin >> t;
    int N = s.size(), M = t.size();
    s = '#' + s;
    t = '#' + t;

    int K;
    cin >> K;

    auto calc = [&]() {
        vector<vector<int>> dp(N + 1, vector<int>(M + 1));

        for (int i = 1; i <= N; i++) {
            for (int j = 1; j <= M; j++) {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);

                if (s[i] == t[j])
                    dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + 1);
            }
        }

        return dp[N][M];
    };

    vector<pair<string &, int>> flipList = {
        {s, 1},
        {s, N},
        {t, 1},
        {t, M},
    };

    int answer = 0;
    for (int bit = 0; bit < 1 << 4; bit++) {
        if (__builtin_popcount(bit) > K) continue;

        auto checkAdj = [&](const string &str, int idx) {
            if (str.size() == 2) return true;

            if (idx == 1) return str[idx] == str[idx + 1];
            else return str[idx - 1] == str[idx];
        };

        auto flipAll = [&](int change) {
            int changed = 0;

            for (int i = 0; i < 4; i++) {
                if (~change & (1 << i)) continue;

                auto &[str, idx] = flipList[i];
                changed |= 1 << i;
                str[idx] = (str[idx] == '0' ? '1' : '0');
            }
            
            return changed;
        };

        int change = 0;
        for (int i = 0; i < 4; i++) {
            if (~bit & (1 << i)) continue;
            auto &[str, idx] = flipList[i];

            if (not checkAdj(str, idx)) continue;
            change |= 1 << i;
        }

        int changed = flipAll(change);
        answer = max(answer, calc());
        flipAll(changed);
    }

    cout << answer;

    return 0;
}
