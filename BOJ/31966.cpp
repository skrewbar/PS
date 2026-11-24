#include <bits/stdc++.h>
using namespace std;

constexpr long long MOD = 1e9 + 7;

struct Tree {
    long long s, suffix, prefix, count;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<Tree> t(n + 1);
    t[0] = Tree{1, 1, 1, 1};

    for (int i = 1; i <= n; i++) {
        int l, r;
        cin >> l >> r;

        t[i].s = (t[l].s + t[r].s + t[l].suffix * t[r].count + t[l].count * t[r].prefix - 1) % MOD;
        t[i].prefix = (t[l].prefix + t[r].count + t[r].prefix - 1) % MOD;
        t[i].suffix = (t[l].suffix + t[l].count + t[r].suffix - 1) % MOD;
        t[i].count = (t[l].count + t[r].count) % MOD;
        cout << t[i].s << '\n';
    }
}