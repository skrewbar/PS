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

    bool operator<(const Line& l) const { return start < l.start; }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<ll> a(n);
    for (int i = 0; i < n; i++)
        cin >> a[i];

    vector<ll> b(n);
    for (int i = 0; i < n; i++)
        cin >> b[i];

    vector<ll> dp(n);

    vector<Line> lines;
    lines.emplace_back(b[0], 0, 0);

    for (int i = 1; i < n; i++) {
        const Line& l =
            *(upper_bound(lines.begin(), lines.end(), Line(0, 0, a[i])) - 1);

        dp[i] = l.a * a[i] + l.b;
        Line newLine(b[i], dp[i], 0);
        double& crossX = newLine.start;

        while (not lines.empty()) {
            Line back = lines.back();
            crossX = (double)(back.b - newLine.b) / (newLine.a - back.a);

            if (crossX <= back.start)
                lines.pop_back();
            else
                break;
        }

        lines.push_back(newLine);
    }

    cout << dp.back();
}