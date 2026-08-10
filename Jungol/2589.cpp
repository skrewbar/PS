#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;

    auto operator<=>(const Point &p) const = default;

    int dist(const Point &p) const {
        int dx = x - p.x;
        int dy = y - p.y;

        return dx * dx + dy * dy;
    }

    int cross(const Point &p) const { return x * p.y - y * p.x; }

    Point operator-(const Point &p) const { return {x - p.x, y - p.y}; }
};
int getCCW(const Point &p1, const Point &p2, const Point &p3) {
    int product = (p2 - p1).cross(p3 - p1);

    if (product > 0) return 1;
    if (product < 0) return -1;
    return 0;
}

struct Line {
    Point s, t;

    Line() = default;
    Line(const Point &_s, const Point &_t) : s(_s), t(_t) {
        if (s > t) swap(s, t);
    }

    bool intersect(const Line &l) const {
        int ccw1 = getCCW(s, l.s, l.t) * getCCW(t, l.s, l.t);
        int ccw2 = getCCW(l.s, s, t) * getCCW(l.t, s, t);

        if (ccw1 == 0 and ccw2 == 0) return s <= l.t and l.s <= t;

        return ccw1 <= 0 and ccw2 <= 0;
    }
};

Line lines[3030];

vector<int> adj[6060];
stack<int> stk;
bool onStack[6060];

int visitCnt = 0;
int in[6060];

int sccCnt = 0;
int sccNum[6060];

bool include[3030];
bool impossible = false;

int findSCC(int cur) {
    stk.push(cur);
    onStack[cur] = true;

    int lowLink = in[cur] = visitCnt++;

    for (int next : adj[cur]) {
        if (in[next] == -1) {
            lowLink = min(lowLink, findSCC(next));
        } else if (onStack[next]) lowLink = min(lowLink, in[next]);
    }

    if (lowLink != in[cur]) return lowLink;

    while (true) {
        int top = stk.top();
        stk.pop();
        onStack[top] = false;

        sccNum[top] = sccCnt;
        if (sccNum[top ^ 1] == sccNum[top]) impossible = true;

        if (sccNum[top ^ 1] == -1) include[top >> 1] = top & 1;

        if (top == cur) break;
    }

    sccCnt++;
    return lowLink;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    for (int i = 1; i <= 3 * N; i++) {
        int X1, Y1, X2, Y2;
        cin >> X1 >> Y1 >> X2 >> Y2;

        lines[i] = {{X1, Y1}, {X2, Y2}};
    }

    for (int i = 1; i <= N; i++) {
        int indices[] = {3 * i - 2, 3 * i - 1, 3 * i};

        for (int j = 0; j < 3; j++) {
            for (int k = 0; k < 3; k++) {
                if (k == j) continue;

                // not a then (b and c)
                adj[indices[j] << 1].push_back(indices[k] << 1 | 1);
            }
        }
    }

    for (int i = 1; i <= 3 * N; i++) {
        for (int j = 1; j < i; j++) {
            if (lines[i].intersect(lines[j])) {
                adj[i << 1 | 1].push_back(j << 1);
                adj[j << 1 | 1].push_back(i << 1);
            }
        }
    }

    fill(in, in + 6 * N + 2, -1);
    fill(sccNum, sccNum + 6 * N + 2, -1);

    for (int i = 1 << 1; i <= (3 * N << 1 | 1); i++)
        if (in[i] == -1) findSCC(i);

    if (impossible) {
        cout << -1;
        return 0;
    }

    vector<int> ex;
    for (int i = 1; i <= 3 * N; i++) {
        if (not include[i]) ex.push_back(i);
    }
    sort(ex.begin(), ex.end());

    println("{}", ex.size());
    for (int i : ex) print("{} ", i);

    return 0;
}
