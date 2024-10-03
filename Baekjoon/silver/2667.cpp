#include<bits/stdc++.h>
using namespace std;
int n;
vector<vector<int>> map_;

int dfs(int x, int y) {
    if (map_[x][y] == 1) {
        map_[x][y] = 2;

        int ret = 0;

        if (0 < x) {
            ret += dfs(x-1, y);
        }
        if (x < n-1) {
            ret += dfs(x+1, y);
        }

        if (0 < y) {
            ret += dfs(x, y-1);
        }
        if (y < n-1) {
            ret += dfs(x, y+1);
        }

        return ret + 1;
    }
    return 0;
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    map_ = vector<vector<int>>(n, vector<int>(n, 0));

    for (int i = 0 ; i < n ; i++) {
        string line;
        cin >> line;

        for (int j = 0 ; j < n ; j++) {
            map_[i][j] = line[j] - '0';
        }
    }

    priority_queue<int, vector<int>, greater<int>> danji;

    for (int i = 0 ; i < n ; i++) {
        for (int j = 0 ; j < n ; j++) {
            if (map_[i][j] == 1) {
                danji.push(dfs(i, j));
            }
        }
    }

    int danjiSize = danji.size();

    cout << danjiSize << '\n';
    for (int i = 0 ; i < danjiSize ; i++) {
        cout << danji.top() << '\n';
        danji.pop();
    }

    return 0;
}