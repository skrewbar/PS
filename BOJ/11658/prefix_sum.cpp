#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#include <bits/stdc++.h>
using namespace std;


int main() { fastio
    int n, m;
    cin >> n >> m;

    vector<vector<int>> table(n, vector<int>(n));
    vector<vector<int>> prefix_sum(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        cin >> table[i][0];
        prefix_sum[i][0] = table[i][0];
        for (int j = 1; j < n; j++) {
            cin >> table[i][j];
            prefix_sum[i][j] = prefix_sum[i][j-1] + table[i][j];
        }
    }

    while (m--) {
        int w; cin >> w;

        if (w == 0) {
            int x, y, c;
            cin >> x >> y >> c;
            x--, y--;
            table[x][y] = c;
            for (int i = y-1; i < n-1; i++) {
                prefix_sum[x][i+1] = prefix_sum[x][i] + table[x][i+1];
            }
        } else {
            int x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            x1--, y1--, x2--, y2--;

            int sum = 0;
            for (int i = x1; i <= x2; i++) {
                sum += prefix_sum[i][y2] - prefix_sum[i][y1] + table[i][y1];
            }
            cout << sum << '\n';
        }
    }
}