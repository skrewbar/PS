#include <bits/stdc++.h>
using namespace std;

struct Point {
    int x, y;

    Point() = default;
    Point(int x, int y) : x(x), y(y) {}

    bool operator<(const Point &p) const { return tie(x, y) < tie(p.x, p.y); }
    bool operator>(const Point &p) const { return p < *this; }
};

#define all(v) v.begin(), v.end()

#define compress(v)                                                            \
    sort(all(v));                                                              \
    v.erase(unique(all(v)), (v).end())

#define convert(x, v) lower_bound(all(v), x) - v.begin()

bool hWall[2020][2020], vWall[2020][2020];
bool visited[2020][2020];

bool canGo(Point from, Point to) {
    if (from > to) swap(from, to);

    if (from.x == to.x) return not hWall[to.x][to.y];
    else return not vWall[to.x][to.y];
}

vector<int> xs = {-1, 10101}, ys = {-1, 10101};
int W, H;

int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};

int calcArea(Point start) {
    int area = 0;

    queue<Point> q;
    q.push(start);

    visited[start.x][start.y] = true;

    while (not q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        area += (xs[x + 1] - xs[x]) * (ys[y + 1] - ys[y]);

        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];

            if (nx < 0 or ny < 0 or nx >= W or ny >= H) continue;
            if (visited[nx][ny]) continue;
            if (not canGo({x, y}, {nx, ny})) continue;

            visited[nx][ny] = true;
            q.emplace(nx, ny);
        }
    }

    return area;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<Point> points(N);

    for (int i = 0; i < N; i++) {
        auto &[x, y] = points[i];

        cin >> x >> y;

        xs.push_back(x);
        ys.push_back(y);
    }

    compress(xs);
    compress(ys);

    W = xs.size();
    H = ys.size();

    for (int i = 0; i < N; i++) {
        auto &[x, y] = points[i];

        x = lower_bound(all(xs), x) - xs.begin();
        y = lower_bound(all(ys), y) - ys.begin();
    }
    for (int i = 0; i < N; i++) {
        auto a = points[i], b = points[(i + 1) % N];

        if (a > b) swap(a, b);

        if (a.x == b.x) {
            for (int y = a.y; y < b.y; y++) vWall[a.x][y] = true;
        } else /* if (a.y == b.y) */ {
            for (int x = a.x; x < b.x; x++) hWall[x][a.y] = true;
        }
    }

    for (int x = 0; x < W; x++) hWall[x][0] = hWall[x][ys.size() - 1] = true;
    for (int y = 0; y < H; y++) vWall[0][y] = vWall[xs.size() - 1][y] = true;

    calcArea({0, 0});
    int ans = 0;
    for (int x = 0; x < W - 1; x++) {
        for (int y = 0; y < H - 1; y++) {
            if (visited[x][y]) continue;

            ans = max(ans, calcArea({x, y}));
        }
    }

    cout << ans;

    return 0;
}