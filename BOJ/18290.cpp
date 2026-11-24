#include <bits/stdc++.h>
using namespace std;

int n, m, k, ans = INT_MIN;
int grid[10][10];
int isSelected[10][10];


void update_square(int x, int y, int value) {
    int dx[5] = {-1, 1, 0, 0, 0};
    int dy[5] = {0, 0, -1, 1, 0};

    for (int i = 0 ; i < 5 ; i++) {
        int nx = x + dx[i], ny = y + dy[i];
        if (0 <= nx < n and 0 <= ny < m) isSelected[nx][ny] += value;
    }
}


void dfs(int left_select, int sum) {
    if (left_select == 0) {
        ans = max(ans, sum);
        return;
    }

    for (int i = 0 ; i < n ; i++) {
        for (int j = 0 ; j < m ; j++) {
            if (not isSelected[i][j]) {
                update_square(i, j, 1);
                dfs(left_select-1, sum + grid[i][j]);
                update_square(i, j, -1);
            }
        }
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k;

    for (int i = 0 ; i < n ; i++) {
        for (int j = 0 ; j < m ; j++) {
            cin >> grid[i][j];
        }
    }

    fill(&isSelected[0][0], &isSelected[9][10], false);
    dfs(k, 0);
    cout << ans;

    return 0;
}