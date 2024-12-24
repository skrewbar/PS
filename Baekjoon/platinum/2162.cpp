#include <bits/stdc++.h>
using namespace std;
using ll = long long;


class DisjointSet {
private:
    vector<int> parent;
public:
    DisjointSet(int n) {
        parent.resize(n);
        for (int i = 0; i < n; i++) parent[i] = i;
    }

    int find_parent(int u) {
        if (parent[u] == u) return u;
        return parent[u] = find_parent(parent[u]);
    }

    void union_parent(int u, int v) {
        parent[find_parent(u)] = find_parent(v);
    }
};


class Point {
public:
    ll x, y;
    Point(ll x, ll y) : x(x), y(y) {}
    
    bool operator<(const Point &p) const {
        if (x != p.x) return x < p.x;
        return y < p.y;
    }
    bool operator<=(const Point &p) const {
        if (x != p.x) return x < p.x;
        return y <= p.y;
    }

    int ccw(const Point &p2, const Point &p3) const {
        const Point &p1 = *this;
        ll p = (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y);

        if (p > 0) return 1;
        if (p < 0) return -1;
        return 0;
    }
};


class Line {
public:
    Point start, end;
    Line() = default;
    Line(Point _start, Point _end) : start(_start), end(_end) {
        if (end < start) swap(start, end);
    }

    int ccw(const Point &p) const {
        return start.ccw(end, p);
    }

    bool is_intersect(const Line &l2) {
        const Line &l1 = *this;

        int ccw1 = l1.ccw(l2.start) * l1.ccw(l2.end);
        int ccw2 = l2.ccw(l1.start) * l2.ccw(l1.end);
        if (ccw1 == 0 and ccw2 == 0) {
            return l1.start <= l2.end and l2.start <= l1.end;
        }
        return ccw1 <= 0 and ccw2 <= 0;
    }
};


int main() {
    int n;
    cin >> n;

    vector<Line> lines;
    lines.reserve(n);
    for (int i = 0; i < n; i++) {
        ll x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        lines.push_back(Line(Point(x1, y1), Point(x2, y2)));
    }

    DisjointSet set(n);
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            if (lines[i].is_intersect(lines[j])) {
                set.union_parent(i, j);
            }
        }
    }

    map<int, int> count;
    for (int i = 0; i < n; i++) {
        int parent = set.find_parent(i);

        if (count.find(parent) == count.end()) {
            count[parent] = 1;
        } else {
            count[parent]++;
        }
    }

    cout << count.size() << '\n';
    int max_count = 0;
    for (auto [key, value] : count) {
        max_count = max(value, max_count);
    }
    cout << max_count;
}