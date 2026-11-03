#include <bits/stdc++.h>
using namespace std;

int power(int base, int exp) {
    int ret = 1;

    while (exp) {
        if (exp & 1) ret *= base;
        base *= base;
        exp >>= 1;
    }

    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    list<int> a;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        a.push_back(x);
    }

    vector<pair<int, int>> operations;
    auto oper = [&](int i, int j) {
        operations.emplace_back(i, j);

        vector<int> stk;
        for (int k = 0; k < 3; k++) {
            auto it = next(a.begin(), i);
            stk.push_back(*it);
            a.erase(it);
        }

        a.insert(next(a.begin(), j), stk.begin(), stk.end());
    };

    for (int x = n; x >= 6; x--) {
        int p = 0;
        auto it = a.begin();
        while (*it != x) ++it, ++p;

        if (p < 2) {
            oper(0, 2 - p);
            p = 2;
        }
        oper(p - 2, x - 3);
    }

    bitset<1 << 12> visited;
    auto getHash = [&]() {
        int ret = 0;
        auto it = a.begin();
        for (int i = 0; i < 5; i++, ++it) { ret += (*it - 1) * power(5, i); }
        return ret;
    };

    auto dfs = [&](auto &&self) -> bool {
        int h = getHash();
        visited[h] = true;

        auto it = a.begin();

        if (h == 2930) return true;

        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (i == j) continue;

                oper(i, j);
                if (not visited[getHash()]) {
                    if (self(self)) return true;
                }
                oper(j, i);
            }
        }

        return false;
    };

    dfs(dfs);

    cout << operations.size() << '\n';
    for (auto [i, j] : operations) cout << i + 1 << ' ' << j + 1 << '\n';

    return 0;
}
