#include <bits/stdc++.h>
using namespace std;

struct Item {
    int value, satisfaction;
};
vector<Item> items(1, {0, 0});
vector<vector<int>> DP;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    int n, m;
    cin >> n >> m;
    for (int i = 0 ; i < n ; i++) {
        int v, c, k;
        cin >> v >> c >> k;

        int j = 1;
        while (k > 0) {
            int temp = min(j, k);

            items.push_back({v * temp, c * temp});

            j *= 2;
            k -= temp;
        }
    }

    DP.resize(items.size(), vector<int>(m+1, 0));
    for (int i = 1 ; i <= DP.size()-1 ; i++) {
        for (int j = 0 ; j <= m ; j++) {
            Item item = items[i];
            DP[i][j] = DP[i-1][j];
            if (0 <= j - item.value) {
                DP[i][j] = max(DP[i][j], DP[i-1][j - item.value] + item.satisfaction);
            }
        }
    }
    cout << DP[DP.size()-1][m];


    return 0;
}