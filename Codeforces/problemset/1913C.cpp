#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m;
    cin >> m;

    vector<int> cnt(30);
    while (m--) {
        int t, v;
        cin >> t >> v;

        if (t == 1)
            cnt[v]++;
        else {
            int sum = 0;

            for (int i = 29; i >= 0; i--) {
                if (not cnt[i]) continue;
                sum += min(cnt[i], ((v - sum) >> i)) << i;
            }

            cout << (sum == v ? "YES": "NO") << '\n';
        }
    }

    return 0;
}
