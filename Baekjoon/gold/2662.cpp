#include <bits/stdc++.h>
using namespace std;

int profit[21][301]; // profit[corp][cost];
int dp[21][301]; // dp[corp][usedMoney];
vector<int> answer[21][301]; // corp, usedMoney에서의 답


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    int n, m;
    cin >> n >> m;

    for (int i = 0 ; i < n ; i++) {
        int cost;
        cin >> cost;
        for (int corp = 1 ; corp <= m ; corp++) {
            cin >> profit[corp][cost];
        }
    }


    for (int corp = 1 ; corp <= m ; corp++) {
        for (int usedMoney = 0 ; usedMoney <= n ; usedMoney++) {
            dp[corp][usedMoney] = dp[corp-1][usedMoney];
            answer[corp][usedMoney] = answer[corp-1][usedMoney];
            answer[corp][usedMoney].push_back(0);
            for (int cost = 1 ; 0 <= usedMoney-cost ; cost++) {
                if (dp[corp][usedMoney] < dp[corp-1][usedMoney-cost] + profit[corp][cost]) {
                    dp[corp][usedMoney] = dp[corp-1][usedMoney-cost] + profit[corp][cost];
                    answer[corp][usedMoney] = answer[corp-1][usedMoney-cost];
                    answer[corp][usedMoney].push_back(cost);
                }
            }
        }
    }

    cout << dp[m][n] << '\n';

    for (int i : answer[m][n]) {
        cout << i << ' ';
    }


    return 0;
}