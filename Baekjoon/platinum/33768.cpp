#include <bits/stdc++.h>
using namespace std;

#define all(v) (v).begin(), (v).end()
#define by(x) [](const auto& a, const auto& b) { return a.x < b.x; }
#define by_desc(x) [](const auto& a, const auto& b) { return a.x > b.x; }

using ll = long long;

template <typename T>
bool minimize(T& target, T value) {
    return target > value ? (target = value, true) : false;
}
template <typename T>
bool maximize(T& target, T value) {
    return target < value ? (target = value, true) : false;
}

constexpr int MX = 101010;

int p[MX], d[MX], e[MX];
pair<int, ll> DE[11][MX];
vector<int> top11[MX];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    for (int i = 2; i <= N; i++)
        cin >> p[i] >> d[i] >> e[i];

    top11[1] = vector<int>(11);
    for (int i = 2; i <= N; i++) {
        top11[i] = top11[p[i]];
        top11[i].push_back(d[i]);
        sort(all(top11[i]), greater());
        top11[i].resize(11);
    }

    for (int c = 0; c <= 10; c++) {
        DE[c][1] = {top11[1][c], e[1]};

        for (int i = 2; i <= N; i++)
            DE[c][i] = {top11[i][c], DE[c][p[i]].second + e[i]};

        sort(DE[c] + 1, DE[c] + N + 1);
        for (int i = 2; i <= N; i++)
            maximize(DE[c][i].second, DE[c][i - 1].second);
    }

    int M;
    cin >> M;
    while (M--) {
        int s, c;
        cin >> s >> c;

        ll ans =
            (upper_bound(DE[c] + 1, DE[c] + N + 1, pair(s, 0), by(first)) - 1)
                ->second;

        cout << ans << "\n";
    }

    return 0;
}