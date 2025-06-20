#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

using ll = long long;

ll square(ll x) {
    return x * x;
}

struct Line {
    ll a, b;
    double start;

    ll operator()(ll x) { return a * x + b; }

    double getIntersection(const Line& l) { return (l.b - b) / (a - l.a); }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    ll a, b, c;
    cin >> a >> b >> c;

    vector<ll> atk(n + 1);
    vector<ll> atkSum(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> atk[i];
        atkSum[i] = atkSum[i - 1] + atk[i];
    }

    vector<ll> dp(n + 1);
    deque<Line> lines;
    lines.emplace_back(0, 0, 0);
    for (int i = 1; i <= n; i++) {
        Line front = lines.front();
        lines.pop_front();
        while (not lines.empty() and
               front(atkSum[i]) <= lines.front()(atkSum[i])) {
            front = lines.front();
            lines.pop_front();
        }
        lines.push_front(front);

        dp[i] = front(atkSum[i]) + a * square(atkSum[i]) + b * atkSum[i] + c;
        ll grad = -2 * a * atkSum[i];
        ll yInterc = a * square(atkSum[i]) - b * atkSum[i] + dp[i];
        Line newLine(grad, yInterc, 0);
        while (not lines.empty()) {
            Line back = lines.back();
            newLine.start = back.getIntersection(newLine);
            if (newLine.start <= back.start)
                lines.pop_back();
            else
                break;
        }
        lines.push_back(newLine);
    }

    cout << dp[n];
    return 0;
}