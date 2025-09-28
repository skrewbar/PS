#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

using ll = long long;
using ld = long double;

struct Line {
    int idx;
    ll slope, yinter;
    ld start;

    Line(int _idx, ll _slope, ll _yinter)
        : idx(_idx), slope(_slope), yinter(_yinter), start(-INFINITY) {}

    ld getIntersection(const Line& l) const {
        return (ld)(l.yinter - yinter) / (slope - l.slope);
    }
};

ll sum[101010];
int opt[222][101010];
deque<Line> lines[2];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    for (int i = 1; i <= n; i++) {
        cin >> sum[i];
        sum[i] += sum[i - 1];
    }

    lines[1].emplace_back(0, 0, 0);
    for (int t = 0; t <= k; t++) {
        lines[t & 1].clear();

        for (int i = 1; i <= n - (k - t); i++) {
            Line l = lines[~t & 1].front();
            lines[~t & 1].pop_front();

            while (not lines[~t & 1].empty() and
                   lines[~t & 1].front().start <= sum[i]) {
                l = lines[~t & 1].front();
                lines[~t & 1].pop_front();
            }

            lines[~t & 1].push_front(l);

            opt[t][i] = l.idx;

            ll dp = sum[i] * l.slope + l.yinter;

            Line newLine(i, sum[i], dp - sum[i] * sum[i]);
            while (not lines[t & 1].empty()) {
                Line back = lines[t & 1].back();

                if (newLine.slope == back.slope) {
                    newLine.yinter = max(newLine.yinter, back.yinter);
                    lines[t & 1].pop_back();
                    continue;
                }

                newLine.start = newLine.getIntersection(back);
                if (newLine.start <= back.start)
                    lines[t & 1].pop_back();
                else
                    break;
            }
            lines[t & 1].push_back(newLine);
        }
    }

    Line l = lines[~k & 1].front();
    cout << sum[n] * l.slope + l.yinter << '\n';

    int prev = n;
    for (int i = k; i >= 1; i--) {
        prev = opt[i][prev];
        cout << prev << ' ';
    }

    return 0;
}