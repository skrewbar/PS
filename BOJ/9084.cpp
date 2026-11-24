#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n;
        vector<int> coins(n);
        for (int i = 0; i < n; i++) {
            cin >> coins[i];
        }
        cin >> m;
        vector<int> ways(m + 1, 0);
        ways[0] = 1;

        for (int i = 0; i < n; i++) {
            for (int j = coins[i] ; j <= m ; j++) {
                ways[j] += ways[j - coins[i]];
            }
        }

        cout << ways[m] << '\n';
    }
}