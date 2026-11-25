#include <bits/stdc++.h>
#include <cassert>
using namespace std;

using ll = long long;

#define all(v) (v).begin(), (v).end()
#define by(x) [](const auto &a, const auto &b) { return a.x < b.x; }
#define by_desc(x) [](const auto &a, const auto &b) { return a.x > b.x; }

#ifdef LOCAL
#define local_assert(...) assert(__VA_ARGS__)
#else
#define local_assert(...) (void(0))
#endif

template <typename T> using MinHeap = priority_queue<T, vector<T>, greater<T>>;

template <typename T> void compress(vector<T> &v) {
    sort(all(v));
    v.erase(unique(all(v)), v.end());
}

template <typename T> bool minimize(T &target, type_identity_t<T> candidate) {
    return target > candidate ? (target = candidate, true) : false;
}
template <typename T> bool maximize(T &target, type_identity_t<T> candidate) {
    return target < candidate ? (target = candidate, true) : false;
}

void solve() {
    int N;
    cin >> N;

    vector<pair<int, int>> pts(N);
    for (auto &[x, y] : pts) cin >> x >> y;

    ll ansSquare = LLONG_MAX;

    for (int mask = (1 << N / 2) - 1; mask < (1 << (N - 1));) {
        int cnt = 0;
        for (int i = 0; i < N; i++) {
            if (mask & (1 << i)) cnt++;
        }
        if (cnt != N / 2) continue;

        ll xSum = 0, ySum = 0;

        for (int i = 0; i < N; i++) {
            auto [x, y] = pts[i];

            if (mask & (1 << i)) {
                xSum += x;
                ySum += y;
            } else {
                xSum -= x;
                ySum -= y;
            }
        }

        minimize(ansSquare, xSum * xSum + ySum * ySum);

        int lowbit = mask & -mask, r = mask + lowbit;
        mask = (((r ^ mask) >> 2) / lowbit) | r;
    }

    cout << sqrt(ansSquare) << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << fixed << setprecision(12);

    int T;
    cin >> T;

    while (T--) solve();

    return 0;
}
