#include <bits/stdc++.h>
using namespace std;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> minDist(n, vector<int>(n, 1e9));
    for (int i = 0; i < n; i++) minDist[i][i] = 0;
    vector<vector<int>> maxLineLen(n, vector<int>(n));
    
    for (int i = 0; i < m; i++) {
        int s, e, l;
        cin >> s >> e >> l;
        s--, e--;

        minDist[s][e] = min(l, minDist[s][e]);
        minDist[e][s] = minDist[s][e];

        maxLineLen[s][e] = max(l, maxLineLen[s][e]);
        maxLineLen[e][s] = maxLineLen[s][e];
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                minDist[i][j] = min(minDist[i][k] + minDist[k][j], minDist[i][j]);
            }
        }
    }

    double answer = 1e9;
    for (int i = 0; i < n; i++) {
        // 모든 간선 확인
        double maxBurnTime = 0;
        for (int start = 0; start < n; start++) {
            for (int end = 0; end < n; end++) {
                if (maxLineLen[start][end] == 0) continue;
                
                double remainLen = maxLineLen[start][end] - (minDist[i][end] - minDist[i][start]);
                if (remainLen > 0)
                    maxBurnTime = max(remainLen / 2 + minDist[i][end], maxBurnTime);
            }
        }
        answer = min(maxBurnTime, answer);
    }

    print("{:.1f}", answer);
}