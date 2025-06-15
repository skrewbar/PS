#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<vector<int>> dist(n, vector<int>(n));
    vector<vector<bool>> deleted(n, vector(n, false));
    for (int i = 0; i < n; i++)
        deleted[i][i] = true;

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> dist[i][j];

    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = i + 1; j < n; j++) {
                if (deleted[i][k] or deleted[k][j] or deleted[i][j])
                    continue;

                if (dist[i][k] + dist[k][j] < dist[i][j]) {
                    cout << -1;
                    return 0;
                }
                if (dist[i][k] + dist[k][j] == dist[i][j]) {
                    deleted[i][j] = true;
                    deleted[j][i] = true;
                }
            }

    int answer = 0;
    for (int i = 0; i < n; i++)
        for (int j = i + 1; j < n; j++)
            if (not deleted[i][j])
                answer += dist[i][j];

    cout << answer;

    return 0;
}