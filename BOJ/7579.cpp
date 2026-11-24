#include <bits/stdc++.h>
using namespace std;

vector<int> memory;
vector<int> cost;
vector<vector<int>> DP;
/* DP[i][c] == 
    i번째 앱까지 탐색했을 때
    c만큼의 비용을 소비해서 얻을 수 있는 최대 메모리
*/


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    int n, m; cin >> n >> m;
    memory.resize(n+1);
    for (int i = 1 ; i <= n ; i++) {
        cin >> memory[i];
    }
    int sumCost = 0;
    cost.resize(n+1);
    for (int i = 1 ; i <= n ; i++) {
        cin >> cost[i];
        sumCost += cost[i];
    }
    DP.resize(n+1, vector<int>(10001, 0));


    for (int i = 1 ; i <= n ; i++) {
        for (int c = 0 ; c <= sumCost ; c++) {
            if (c - cost[i] >= 0) {
                DP[i][c] = max(
                    DP[i][c],
                    DP[i-1][c - cost[i]] + memory[i]
                );
            }
            DP[i][c] = max(
                DP[i][c],
                DP[i-1][c]
            );
        }
    }

    for (int c = 0 ; c <= sumCost ; c++) {
        if (DP[n][c] >= m) {
            cout << c;
            break;
        }
    }


    return 0;
}