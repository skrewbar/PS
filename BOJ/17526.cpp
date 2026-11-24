#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

using ll = long long;
using ldouble = long double;

struct Line {
    ll slope, yIntercept;
    ldouble start;

    Line(ll _slope, ll _yIntercept)
        : slope(_slope), yIntercept(_yIntercept), start(-INFINITY) {}

    ldouble getIntersection(const Line& l) const {
        return (ldouble)(l.yIntercept - yIntercept) / (slope - l.slope);
    }

    ll operator()(ll x) const { return slope * x + yIntercept; }
};

// upper hull
struct LineContainer {
    size_t bufSize;
    vector<Line> lines, buffer;

    LineContainer(size_t _bufSize) : bufSize(_bufSize) {}

    void push(Line l) {
        while (not lines.empty()) {
            const Line& back = lines.back();

            if (l.slope > back.slope) {
                buffer.push_back(l);
                return;
            }

            if (l.slope == back.slope) {
                if (l.yIntercept < back.yIntercept) {
                    lines.pop_back();
                    continue;
                }
                return;
            }

            l.start = l.getIntersection(back);
            if (l.start <= back.start)
                lines.pop_back();
            else
                break;
        }

        lines.push_back(l);
    }

    void flush() {
        sort(buffer.begin(), buffer.end(), [](const Line& l1, const Line& l2) {
            return l1.slope > l2.slope;
        });

        vector<Line> oldLines;
        swap(oldLines, lines);

        int i = 0, j = 0;
        while (i < (int)oldLines.size() and j < (int)buffer.size()) {
            if (oldLines[i].slope > buffer[j].slope)
                push(oldLines[i++]);
            else
                push(buffer[j++]);
        }

        while (i < (int)oldLines.size())
            push(oldLines[i++]);
        while (j < (int)buffer.size())
            push(buffer[j++]);

        buffer.clear();
    }

    ll query(ll x) {
        if (buffer.size() > bufSize)
            flush();

        ll ret = (*(upper_bound(lines.begin(), lines.end(), (ldouble)x,
                                [](ldouble val, const Line& l) {
                                    return val < l.start;
                                }) -
                    1))(x);

        for (const Line& l : buffer)
            ret = min(ret, l(x));

        return ret;
    }
};

ll dp[100100], pos[100100];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    for (int i = 2; i <= n; i++) {
        cin >> pos[i];
        pos[i] += pos[i - 1];
    }

    LineContainer lineContainer(sqrt(n));

    ll pre, pace;
    cin >> pre >> pace;
    lineContainer.push(Line(pace, pre));

    for (int i = 2; i < n; i++) {
        cin >> pre >> pace;

        ll totalTime = lineContainer.query(pos[i]);
        lineContainer.push(Line(pace, -pace * pos[i] + totalTime + pre));
    }

    cout << lineContainer.query(pos[n]);

    return 0;
}