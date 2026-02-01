#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

int dist[4][4];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            cin >> dist[i][j];

    if (dist[0][2] + dist[2][1] < dist[0][1] or
        dist[0][3] + dist[3][1] < dist[0][1]) {
        println("NO");
        return 0;
    }

    double x3 = (pow(dist[0][1], 2) + pow(dist[0][2], 2) - pow(dist[1][2], 2)) /
                (2 * dist[0][1]);
    double y3 = sqrt(pow(dist[0][2], 2) - x3 * x3);

    double x4 = (pow(dist[0][1], 2) + pow(dist[0][3], 2) - pow(dist[1][3], 2)) /
                (2 * dist[0][1]);
    double y4 = sqrt(pow(dist[0][3], 2) - x4 * x4);

    double minDist = sqrt(pow(x4 - x3, 2) + pow(y4 - y3, 2));
    y4 = -y4;
    double maxDist = sqrt(pow(x4 - x3, 2) + pow(y4 - y3, 2));

    if (minDist > maxDist)
        swap(minDist, maxDist);

    if (minDist <= dist[2][3] and dist[2][3] <= maxDist)
        println("YES");
    else
        println("NO");

    return 0;
}