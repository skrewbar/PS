#include <bits/stdc++.h>
using namespace std;

class Point {
public:
    int x, y;

    Point() = default;
    Point(int x, int y) : x(x), y(y) {}
    Point(double x, double y) : x(round(x)), y(round(y)) {}

    bool operator<(const Point &p) const {
        if (x != p.x) return x < p.x;
        return y < p.y;
    }
    bool operator<=(const Point &p) const {
        if (x != p.x) return x < p.x;
        return y <= p.y;
    }

    int ccw(const Point &p1, const Point &p2) const {
        int p = (p1.x - x) * (p2.y - y) - (p2.x - x) * (p1.y - y);

        if (p > 0) return 1;
        if (p < 0) return -1;
        return 0;
    }
};

class Line {
public:
    Point start, end;

    Line() = default;
    Line(Point start, Point end) {
        if (end < start) swap(start, end);
        this->start = start;
        this->end = end;
    }

    int ccw(const Point &p) const {
        return start.ccw(end, p);
    }

    friend bool is_oneline(const Line &l1, const Line &l2) {
        if (l1.ccw(l2.start) == 0 and l1.ccw(l2.end) == 0) {
            return l1.start <= l2.end and l2.start <= l1.end;
        }
        return false;
    }
};


int find_parent(vector<int> &parent, int x) {
    if (parent[x] == x) return x;
    return parent[x] = find_parent(parent, parent[x]);
}
void union_parent(vector<int> &parent, int u, int v) {
    u = find_parent(parent, u);
    v = find_parent(parent, v);
    parent[u] = v;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<Line> lines(n);
    for (int i = 0; i < n; i++) {
        double x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        lines[i] = Line(Point(x1*100, y1*100), Point(x2*100, y2*100));
    }

    vector<int> parent(n);
    for (int i = 0; i < n; i++) parent[i] = i;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (is_oneline(lines[i], lines[j])) {
                union_parent(parent, i, j);
            }
        }
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (find_parent(parent, i) == i) ans++;
    }

    cout << ans;
}