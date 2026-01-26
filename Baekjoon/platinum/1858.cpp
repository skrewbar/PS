#include <bits/stdc++.h>
#include <compare>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

using ll = long long;

ll gcd(ll a, ll b) {
    while (b) {
        a %= b;
        swap(a, b);
    }

    return a;
}

struct Fraction {
    ll numerator, denominator;

    Fraction(ll _numerator, ll _denominator)
        : numerator(_numerator), denominator(_denominator) {
        ll g = gcd(numerator, denominator);
        numerator /= g;
        denominator /= g;

        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
    }

    bool operator<(const Fraction& f) const {
        return numerator * f.denominator < f.numerator * denominator;
    }

    bool operator==(const Fraction& f) const {
        return numerator == f.numerator and denominator == f.denominator;
    }
};

Fraction abs(const Fraction& f) {
    return Fraction(abs(f.numerator), f.denominator);
}

struct Point {
    int x, y;
    int number;

    bool operator<(const Point& p) const {
        if (x != p.x)
            return x < p.x;
        return y < p.y;
    }

    Fraction getSlope(const Point& p) const {
        return Fraction(p.y - y, p.x - x);
    }
};

Point points[50505];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    for (int i = 0; i < N; i++) {
        cin >> points[i].x >> points[i].y;
        points[i].number = i + 1;
    }
    sort(points, points + N);

    pair<int, int> ans(points[0].number, points[1].number);
    int ansIdx = 0;
    if (ans.first > ans.second)
        swap(ans.first, ans.second);
    Fraction ansSlope = abs(points[0].getSlope(points[1]));

    for (int i = 1; i < N - 1; i++) {
        Point p1 = points[i], p2 = points[i + 1];
        if (p1.number > p2.number)
            swap(p1, p2);

        Fraction slope = abs(p1.getSlope(p2));

        if (ansSlope < slope or (slope == ansSlope and pair(p1.number, p2.number) < ans)) {
            ansSlope = slope;
            ans = pair(p1.number, p2.number);
            ansIdx = i;
        }
    }

    ansSlope = points[ansIdx].getSlope(points[ansIdx + 1]);

    int i = ansIdx - 1;
    while (i >= 0 and ansSlope == points[i].getSlope(points[ansIdx])) {
        ans.second = min(ans.second, points[i].number);
        i--;
    }
    i = ansIdx + 2;
    while (i < N and ansSlope == points[i].getSlope(points[ansIdx])) {
        ans.second = min(ans.second, points[i].number);
        i++;
    }

    println("{} {}", ans.first, ans.second);

    return 0;
}