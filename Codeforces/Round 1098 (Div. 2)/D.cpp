#include <bits/stdc++.h>
using namespace std;

using ll = long long;

#define all(v) v.begin(), v.end()
#define compress(v)                                                            \
    sort(all(v));                                                              \
    v.erase(unique(all(v)), v.end())
#define rank(v, x) lower_bound(all(v), x) - v.begin();

template <typename T> bool minimize(T &target, T candidate) {
    return target > candidate ? (target = candidate, true) : false;
}
template <typename T> bool maximize(T &target, T candidate) {
    return target < candidate ? (target = candidate, true) : false;
}

pair<int, int> intersection(pair<int, int> rng1, pair<int, int> rng2) {
    if (rng1 > rng2) swap(rng1, rng2);
    if (rng1.first <= rng2.first and rng2.second <= rng1.second) return rng2;
    return {rng2.first, rng1.second};
}

void solve() {
    int n;
    cin >> n;

    vector<pair<int, int>> points(n + 1);
    vector<int> xs, ys;
    for (int i = 1; i <= n; i++) {
        auto &[x, y] = points[i];
        cin >> x >> y;

        xs.push_back(x);
        ys.push_back(y);
    }
    sort(1 + all(points));

    compress(xs), compress(ys);

    for (int i = 1; i <= n; i++) {
        auto &[x, y] = points[i];
        x = rank(xs, x);
        y = rank(ys, y);
    }

    vector<tuple<int, int, int>> revP(n + 1);
    for (int i = 1; i <= n; i++) {
        auto &[y, x, idx] = revP[i];
        tie(x, y) = points[i];
        idx = i;
    }
    sort(1 + all(revP));

    int ri = 1, rj = n;
    bitset<2020202> removed;

    int lMin = n, lMax = 0;
    ll ans = 0;
    int i = 1, j = 1;
    while (i <= n) {
        j = i;
        while (j + 1 <= n and points[i].first == points[j + 1].first) j++;

        for (int k = i; k <= j; k++) {
            auto [x, y] = points[k];
            minimize(lMin, y);
            maximize(lMax, y);
            removed[k] = true;
        }
        while (ri <= n and removed[get<2>(revP[ri])]) ri++;
        while (rj >= 1 and removed[get<2>(revP[rj])]) rj--;
        if (ri > rj) break;

        auto [l, r] = intersection(
            {lMin, lMax}, {get<0>(revP[ri]), get<0>(revP[rj])});

        ans += max(0, r - l);
        i = j + 1;
    }

    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) solve();

    return 0;
}
