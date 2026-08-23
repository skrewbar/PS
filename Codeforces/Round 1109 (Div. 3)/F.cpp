#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()

void solve() {
    int n;
    cin >> n;

    vector<vector<int>> childs(n + 1);

    for (int i = 2; i <= n; i++) {
        int p;
        cin >> p;

        childs[p].push_back(i);
    }
    for (int i = 1; i <= n; i++) sort(all(childs[i]));

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    vector<int> subMin(n + 1), subMax(n + 1);
    auto canSort = [&](auto &&self, int v) -> bool {
        if (childs[v].empty()) {
            subMin[v] = subMax[v] = a[v];
            return true;
        }

        for (int c : childs[v])
            if (not self(self, c)) return false;

        vector<pair<int, int>> ranges;
        for (int c : childs[v]) ranges.emplace_back(subMin[c], subMax[c]);


        int childCnt = childs[v].size();
        auto nextIdx = [&](int i) { return (i + 1) % childCnt; };
        int s = min_element(all(ranges)) - ranges.begin();
        for (int i = s; nextIdx(i) != s; i = nextIdx(i))
            if (ranges[i].second >= ranges[nextIdx(i)].first) return false;

        int e = (s - 1 + childCnt) % childCnt;
        subMin[v] = ranges[s].first;
        subMax[v] = ranges[e].second;
        return true;
    };

    cout << (canSort(canSort, 1) ? "YES" : "NO") << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) solve();

    return 0;
}
