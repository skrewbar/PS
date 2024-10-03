#include <bits/stdc++.h>
using namespace std;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    int n, s, m;
    cin >> n >> s >> m;
    vector<vector<bool>> isPlayable(n+1, vector<bool>(m+1, false));
    vector<int> v(n+1);

    for (int i = 1 ; i <= n ; i++) {
        cin >> v[i];
    }

    isPlayable[0][s] = true;
    for (int i = 0 ; i < n ; i++) {
        for (int volume = 0 ; volume <= m ; volume++) {
            if (isPlayable[i][volume]) {
                if (volume + v[i+1] <= m) isPlayable[i+1][volume+v[i+1]] = true;
                if (0 <= volume - v[i+1]) isPlayable[i+1][volume-v[i+1]] = true;
            }
        }
    }

    bool hasAnswered = false;
    for (int volume = m ; 0 <= volume ; volume--) {
        if (isPlayable[n][volume]) {
            cout << volume;
            hasAnswered = true;
            break;
        }
    }

    if (not hasAnswered) cout << -1;


    return 0;
}