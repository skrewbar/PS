#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()

void solve() {
    int n;
    cin >> n;

    vector<vector<int>> pref(3, vector<int>(n + 1));
    for (int j = 0; j < 3; j++) {
        for (int i = 1; i <= n; i++) cin >> pref[j][i];
    }
    vector<vector<pair<int, int>>> cand(3);
    for (int j = 0; j < 3; j++) {
        for (int i = 1; i <= n; i++) cand[j].emplace_back(pref[j][i], i);
        sort(all(cand[j]), greater<>());
    }

    vector<bool> possible(n + 1);
    vector<pair<int, int>> prev(n + 1);
    possible[1] = true;

    for (int i = 1; i <= n; i++) {
        if (not possible[i]) continue;

        for (int j = 0; j < 3; j++) {
            if (cand[j].empty()) continue;

            while (not cand[j].empty()) {
                auto [p, c] = cand[j].back();
                if (p > pref[j][i]) break;

                if (i < c) {
                    possible[c] = true;
                    prev[c] = {j, i};
                }

                cand[j].pop_back();
            }
        }
    }

    if (not possible[n]) {
        println("NO");
        return;
    }

    println("YES");

    stack<pair<int, int>> ans;
    int p, c;
    for (int i = n; i != 1; i = c) {
        tie(p, c) = prev[i];
        ans.emplace(p, i);
    }

    string players = "qkj";
    println("{}", ans.size());
    while (not ans.empty()) {
        tie(p, c) = ans.top();
        ans.pop();

        println("{} {}", players[p], c);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) solve();

    return 0;
}
