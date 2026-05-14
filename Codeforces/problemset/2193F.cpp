#include <bits/stdc++.h>
using namespace std;

using ll = long long;

pair<ll, ll> points[202020];

struct Range {
    ll x;
    ll minY, maxY;
};

void solve() {
    ll n, Ax, Ay, Bx, By;
    cin >> n >> Ax >> Ay >> Bx >> By;

    for (int i = 1; i <= n; i++)
        cin >> points[i].first;
    for (int i = 1; i <= n; i++)
        cin >> points[i].second;

    sort(points + 1, points + n + 1);
    points[n + 1].first = 0;

    vector<Range> compressed;
    compressed.emplace_back(Ax, Ay, Ay);
    for (int i = 1; i <= n; i++) {
        if (points[i].first != points[i - 1].first)
            compressed.emplace_back(points[i].first, points[i].second);
        if (points[i].first != points[i + 1].first)
            compressed.back().maxY = points[i].second;
    }
    compressed.emplace_back(Bx, By, By);

    ll minTop = 0, minBottom = 0;
    for (int i = 1; i < compressed.size(); i++) {
        auto [px, pbottom, ptop] = compressed[i - 1];
        auto [x, bottom, top] = compressed[i];

        ll newMinTop = min(minTop + abs(bottom - ptop),
                           minBottom + abs(bottom - pbottom)) +
                       top - bottom + x - px;

        ll newMinBottom =
            min(minTop + abs(top - ptop), minBottom + abs(top - pbottom)) +
            top - bottom + x - px;

        minTop = newMinTop;
        minBottom = newMinBottom;
    }

    cout << min(minTop, minBottom) << '\n';
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