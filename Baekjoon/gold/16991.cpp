#include <bits/stdc++.h>
using namespace std;

int n;
struct Point {
    int x, y;
};

vector<Point> point;
vector<vector<double>> dp;


double cost(Point p1, Point p2) {
    return sqrt(pow((p1.x - p2.x), 2) + pow((p1.y - p2.y), 2));
}


double tsp(int city, int visited) {
    if (visited == (1 << n) - 1) {
        return cost(point[city], point[0]);
    }

    if (dp[city][visited] != -1) {
        return dp[city][visited];
    }

    dp[city][visited] = INT_MAX;
    for (int next = 0 ; next < n ; next++) {
        if (not (visited & 1 << next)) {
            dp[city][visited] = min(
                dp[city][visited],
                tsp(next, visited | 1 << next) + cost(point[city], point[next])
            );
        }
    }
    return dp[city][visited];
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    point.resize(n);
    for (int i = 0 ; i < n ; i++) {
        int x, y;
        cin >> x >> y;
        point[i] = {x, y};
    }
    dp.resize(n, vector<double>(1 << 16, -1));

    cout << fixed;
    cout.precision(6);
    cout << tsp(0, 0);

    return 0;
}