#include <bits/stdc++.h>
using namespace std;

constexpr int RED = 0;
constexpr int GREEN = 1;
constexpr int BLUE = 2;
constexpr int INF = 1e9;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<vector<int>> cost(3, vector<int>(3, INF));
    // cost[c1][c2] : 지금 c1색이고 맨 처음 칠한 색은 c2일때 최솟값
    cin >> cost[RED][RED] >> cost[GREEN][GREEN] >> cost[BLUE][BLUE];
    
    for (int i = 1; i < n; i++) {
        int red_cost, green_cost, blue_cost;
        cin >> red_cost >> green_cost >> blue_cost;

        vector<vector<int>> new_cost(3, vector<int>(3, INF));
        for (int i = 0; i < 3; i++) {
            new_cost[RED][i] = min(cost[GREEN][i], cost[BLUE][i]) + red_cost;
            new_cost[GREEN][i] = min(cost[RED][i], cost[BLUE][i]) + green_cost;
            new_cost[BLUE][i] = min(cost[RED][i], cost[GREEN][i]) + blue_cost;
        }
        cost = new_cost;
    }
    
    int ans = INF;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (i == j) continue;
            ans = min(cost[i][j], ans);
        }
    }
    cout << ans;
}