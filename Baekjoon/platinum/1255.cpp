#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

template <typename T>
using MinHeap = priority_queue<T, vector<T>, greater<T>>;

struct Point {
    int x, y;

    auto operator<=>(const Point& p) const = default;

    int crossProduct(const Point& p) const { return x * p.y - y * p.x; }

    Point operator-(const Point& p) const { return Point(x - p.x, y - p.y); }

    long double dist(const Point& p) const {
        int dx = x - p.x;
        int dy = y - p.y;

        return sqrtl(dx * dx + dy * dy);
    }
};

int getCCW(const Point& p1, const Point& p2, const Point& p3) {
    int product = (p2 - p1).crossProduct(p3 - p1);

    if (product > 0)
        return 1;
    if (product < 0)
        return -1;
    return 0;
}

struct Line {
    Point s, e;

    Line() = default;
    Line(const Point& _s, const Point& _e) : s(_s), e(_e) {
        if (s > e)
            swap(s, e);
    }

    bool isIntersect(const Line& l) const {
        int ccw1 = getCCW(s, e, l.s) * getCCW(s, e, l.e);
        int ccw2 = getCCW(l.s, l.e, s) * getCCW(l.s, l.e, e);

        if (ccw1 == 0 and ccw2 == 0)
            return s <= l.e and l.s <= e;
        return ccw1 <= 0 and ccw2 <= 0;
    }
};

istream& operator>>(istream& in, Point& p) {
    string s;
    cin >> s;

    p.x = 0;
    int i = 1;
    while (s[i] != ',') {
        p.x *= 10;
        p.x += s[i++] - '0';
    }
    i++;

    p.y = 0;
    while (s[i] != ')') {
        p.y *= 10;
        p.y += s[i++] - '0';
    }

    return in;
}

vector<Point> points;
vector<vector<int>> adj;
vector<Line> obstacles;

bool canGoTo(const Point& s, const Point& e) {
    const Line l(s, e);

    for (const Line& obstacle : obstacles) {
        if (s == obstacle.s or s == obstacle.e or e == obstacle.s or e == obstacle.e)
            continue;

        if (l.isIntersect(obstacle))
            return false;
    }

    return true;
}

constexpr long double INF = 1e9;
long double getMinTime(const Point& citizen, int speed) {
    if (canGoTo(citizen, Point(citizen.x, 0)))
        return (long double)citizen.y / speed;

    vector<long double> time(points.size() + 1, INF);
    MinHeap<pair<long double, int>> pq;
    for (int i = 0; i < (int)points.size(); i++) {
        if (canGoTo(citizen, points[i])) {
            time[i] = citizen.dist(points[i]) / speed;
            pq.emplace(time[i], i);
        }
    }

    while (not pq.empty()) {
        auto [nowTime, now] = pq.top();
        pq.pop();

        if (time[now] < nowTime)
            continue;

        if (canGoTo(points[now], Point(points[now].x, 0)))
            time.back() = min(time.back(), nowTime + (long double)points[now].y / speed);

        for (int next : adj[now]) {
            long double nextTime = nowTime + points[now].dist(points[next]) / speed;

            if (nextTime < time[next]) {
                time[next] = nextTime;
                pq.emplace(nextTime, next);
            }
        }
    }

    return time.back();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    vector<pair<Point, int>> citizens(N);
    for (auto& [point, speed] : citizens) {
        cin >> point >> speed;
    }

    obstacles.resize(M);
    for (auto& [s, e] : obstacles) {
        cin >> s;
        cin.ignore(3);
        cin >> e;

        points.push_back(s);
        points.push_back(e);
    }

    adj.resize(points.size());
    for (int i = 0; i < (int)points.size(); i++) {
        for (int j = i + 1; j < (int)points.size(); j++) {
            if (canGoTo(points[i], points[j])) {
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
    }

    long double answer = 0;
    for (auto [citizen, speed] : citizens) {
        answer = max(answer, getMinTime(citizen, speed));
    }

    print("{:.1f}", answer);
    
    return 0;
}