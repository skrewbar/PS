#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr ll MOD = 676767677;

int b[202020], mina[202020], maxa[202020];
vector<int> pos[202020];
bool sit[202020];

int n, m;

void initVariables() {
    for (int i = 0; i < m; i++)
        pos[i].clear();
    fill(sit + 1, sit + n + 1, false);
}

void solve() {
    cin >> n >> m;
    initVariables();

    for (int i = 1; i <= n; i++) {
        cin >> b[i];
        pos[b[i]].push_back(i);
    }

    for (int i : pos[0]) {
        sit[i] = true;
        mina[i] = maxa[i] = 0;
    }

    int sitCnt = pos[0].size();
    for (int t = 1; t < m; t++) {
        for (int i : pos[t]) {
            if (not sit[i - 1] and not sit[i + 1]) {
                cout << 0 << '\n';
                return;
            }

            mina[i] = 1;
            for (int j : {i - 1, i + 1}) {
                if (j == 0 or j == n + 1)
                    continue;

                if (b[j] < b[i] - 1)
                    mina[i] = sitCnt - pos[t - 1].size() + 1;
            }
            maxa[i] = sitCnt;
        }
        for (int i : pos[t])
            sit[i] = true;
        sitCnt += pos[t].size();
    }

    ll answer = 1;
    for (int i = 1; i <= n; i++) {
        answer = answer * (maxa[i] - mina[i] + 1) % MOD;
    }
    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--)
        solve();

    return 0;
}