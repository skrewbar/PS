#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

using ll = long long;
using ld = long double;

ll sum[101010];

struct Line {
    int idx;
    ll slope, yinter;
    ld start;
    Line(int _idx, ll _slope, ll _yinter)
        : idx(_idx), slope(_slope), yinter(_yinter), start(-INFINITY) {}

    ld getIntersection(const Line& l) {
        return (ld)(l.yinter - yinter) / (slope - l.slope);
    }
};

// Only supports inserting lines in strictly increasing slope order
struct LineContainer {
    vector<Line> lines;

    void push(Line l) {
        while (not lines.empty()) {
            Line back = lines.back();

            ASSERT(l.slope != back.slope);

            l.start = l.getIntersection(back);
            if (l.start <= back.start)
                lines.pop_back();
            else
                break;
        }

        lines.push_back(l);
    }

    // Returns idx of line
    int query(ld x) {
        return (upper_bound(lines.begin(), lines.end(), x,
                            [](ld v, const Line& l) { return v < l.start; }) -
                1)
            ->idx;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    LineContainer container;
    for (int i = 1; i <= N; i++) {
        cin >> sum[i];
        sum[i] += sum[i - 1];

        container.push(Line(i, sum[i], -sum[i - 1]));
    }

    int before, now;
    cin >> now;
    ll ans = 0;
    for (int i = 2; i <= M; i++) {
        swap(before, now);
        cin >> now;

        int idx = container.query((ld)before / now);
        ans += max(before * sum[1], sum[idx] * before - sum[idx - 1] * now);
    }
    ans += sum[N] * now;

    cout << ans;

    return 0;
}