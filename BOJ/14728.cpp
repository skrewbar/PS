#include <bits/stdc++.h>
using namespace std;

struct Chapter {
    int time, score;
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    int n, t;
    cin >> n >> t;

    vector<Chapter> chapters(n+1);
    for (int i = 1 ; i <= n ; i++) {
        int k, s;
        cin >> k >> s;
        chapters[i] = {k, s};
    }

    vector<vector<int>> DP(n+1, vector<int>(t+1, 0));

    for (int i = 1 ; i <= n ; i++) {
        for (int j = 0 ; j <= t ; j++) {
            DP[i][j] = DP[i-1][j];
            if (0 <= j - chapters[i].time) {
                DP[i][j] = max(
                    DP[i][j],
                    DP[i-1][j-chapters[i].time] + chapters[i].score
                );
            }
        }
    }

    cout << DP[n][t];


    return 0;
}