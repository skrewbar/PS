#include <bits/stdc++.h>

#define fastio ios::sync_with_stdio(false); cin.tie(nullptr);
#define debug if constexpr (local) std::cout

#ifdef LOCAL
constexpr bool local = true;
#else
constexpr bool local = false;
#endif

using namespace std;
vector<int> graph[100];
bool canGo[100][100];


int main() { fastio
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> canGo[i][j];
        }
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (canGo[i][j]) continue;
                canGo[i][j] = canGo[i][k] and canGo[k][j];
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << canGo[i][j] << ' ';
        }
        cout << '\n';
    }


    return 0;
}