#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

using ll = long long;

struct Line {
    ll a, b;
    double start;

    Line() = default;
    Line(ll a, ll b, double start) : a(a), b(b), start(start) {}

    ll operator()(ll x) { return a * x + b; }
};

struct Land {
    ll w, h;

    auto operator<=>(const Land& land) const = default;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<Land> lands(n);
    for (auto& [w, h] : lands)
        cin >> w >> h;
    sort(lands.begin(), lands.end());
    lands.emplace_back(-1, -1);

    vector<Land> temp;
    for (int i = 0; i < n; i++) {
        if (lands[i].w != lands[i + 1].w) {
            while (not temp.empty() and temp.back().h <= lands[i].h)
                temp.pop_back();
            temp.push_back(lands[i]);
        }
    }
    swap(lands, temp);
    n = lands.size();

    vector<ll> dp(n);
    deque<Line> lines;
    lines.emplace_back(lands[0].h, 0, 0);

    for (int i = 0; i < n - 1; i++) {
        Line front = lines.front();
        lines.pop_front();

        while (not lines.empty() and
               front(lands[i].w) >= lines.front()(lands[i].w)) {
            front = lines.front();
            lines.pop_front();
        }
        lines.push_front(front);

        dp[i] = front(lands[i].w);

        if (i == n - 1)
            break;
        Line newLine(lands[i + 1].h, dp[i], 0);
        double& start = newLine.start;
        while (not lines.empty()) {
            Line back = lines.back();

            start = (double)(back.b - newLine.b) / (newLine.a - back.a);
            if (start <= back.start)
                lines.pop_back();
            else
                break;
        }
        lines.push_back(newLine);
    }

    Line front = lines.front();
    lines.pop_front();
    while (not lines.empty() and
           front(lands.back().w) >= lines.front()(lands.back().w)) {
        front = lines.front();
        lines.pop_front();
    }
    print("{}", front(lands.back().w));

    return 0;
}