#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

using ll = long long;
using i128 = __int128;
using ld = long double;

i128 gcd(i128 a, i128 b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}
struct Fraction {
    i128 numer, denom;

    Fraction(i128 _numer, i128 _denom) : numer(_numer), denom(_denom) {
        reduce();
    }

    void reduce() {
        if (denom < 0) {
            numer = -numer;
            denom = -denom;
        }
        bool negative = numer < 0;

        if (negative)
            numer = -numer;

        i128 g = gcd(numer, denom);
        numer /= g;
        denom /= g;

        if (negative)
            numer = -numer;
    }

    bool operator==(const Fraction& f) const {
        return numer == f.numer and denom == f.denom;
    }

    operator ld() { return (ld)numer / denom; }
};

int k;
struct Line {
    ll A, B;
    Fraction fracSlope;
    ld slope, yIntercept, start;

    Line(ll _A, ll _B)
        : A(_A),
          B(_B),
          fracSlope(k, A + B),
          slope(fracSlope),
          yIntercept((ld)A / (A + B)),
          start(-INFINITY) {}

    ld getIntersection(const Line& l) const {
        return (l.yIntercept - yIntercept) / (slope - l.slope);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M >> k;

    vector<Line> lines;
    lines.reserve(N);

    for (int i = 0; i < N; i++) {
        ll A, B;
        cin >> A >> B;

        lines.emplace_back(A, B);
    }

    sort(lines.begin(), lines.end(),
         [](const Line& a, const Line& b) { return a.slope > b.slope; });

    deque<Line> upperHull;
    for (int i = 0; i < N; i++) {
        bool shouldPush = true;

        Line l = lines[i];

        while (not upperHull.empty()) {
            const Line& back = upperHull.back();

            if (l.fracSlope == back.fracSlope) {
                if (l.yIntercept < back.yIntercept) {
                    upperHull.pop_back();
                    continue;
                } else {
                    shouldPush = false;
                    break;
                }
            }

            l.start = l.getIntersection(back);
            if (l.start <= back.start)
                upperHull.pop_back();
            else
                break;
        }

        if (shouldPush)
            upperHull.push_back(l);
    }

    for (ll x = 1; x <= M; x++) {
        Line front = upperHull.front();
        upperHull.pop_front();
        while (not upperHull.empty() and upperHull.front().start <= x) {
            front = upperHull.front();
            upperHull.pop_front();
        }
        upperHull.push_front(front);

        Fraction ans(front.B - k * x, front.A + k * x);
        if (ans.numer == 0)
            cout << "0/0\n";
        else
            cout << (ll)ans.numer << '/' << (ll)ans.denom << '\n';
    }

    return 0;
}