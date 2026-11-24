#include <bits/stdc++.h>
using namespace std;

int n;
const int INF = 987654321;
vector<vector<int>> cost;
vector<vector<int>> DP;


int TSP(int cur, int visited) {
    if (visited == (1 << n) - 1) {
        if (cost[cur][0] == 0) return INF;
        else return cost[cur][0];
    }
    if (DP[cur][visited] != -1) {
        return DP[cur][visited];
    }
    
    DP[cur][visited] = INF;
    for (int next = 0 ; next < n ; next++) {
        if (!(visited & 1<<next) and cost[cur][next] != 0) {
            DP[cur][visited] = min(
                DP[cur][visited],
                TSP(next, visited | 1<<next) + cost[cur][next]
            );
        }
    }
    return DP[cur][visited];
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    cin >> n;
    cost = vector<vector<int>>(n, vector<int>(n, 0));
    for (int i = 0 ; i < n ; i++) {
        for (int j = 0 ; j < n ; j++) {
            cin >> cost[i][j];
        }
    }
    DP = vector<vector<int>>(n, vector<int>(1<<n, -1));
    cout << TSP(0, 1);


    return 0;
}