#include <bits/stdc++.h>
using namespace std;

int board[10][10];
bool rUpDiagonal[20];
bool lUpDiagonal[20];

int n;
int ans = 0;


void dfs(int r_i, int bishopCount) {
    if (r_i == 2*n) {
        ans = max(ans, bishopCount);
        return;
    }

    bool hasPlaced = false;
    for (int r_j = 0 ; r_j < (n - abs(r_i - (n - 1))) ; r_j++) {
        int x = (r_i <= n - 1) ? r_i-r_j : n-1-r_j;
        int y = (r_i <= n - 1) ? r_j : r_i-(n-1) + r_j;

        int l_i = x - y + n - 1;

        if (board[x][y] != 0 and not lUpDiagonal[l_i]) {
            hasPlaced = true;
            rUpDiagonal[r_i] = true;
            lUpDiagonal[l_i] = true;
            dfs(r_i+1, bishopCount+1);
            rUpDiagonal[r_i] = false;
            lUpDiagonal[l_i] = false;
        }
    }
    if (not hasPlaced) dfs(r_i+1, bishopCount);
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    cin >> n;
    fill(&board[0][0], &board[9][10], 0);
    fill(rUpDiagonal, rUpDiagonal+20, false);
    fill(lUpDiagonal, lUpDiagonal+20, false);
    for (int i = 0 ; i < n ; i++) {
        for (int j = 0 ; j < n ; j++) {
            cin >> board[i][j];
        }
    }
    dfs(0, 0);
    cout << ans;


    return 0;
}