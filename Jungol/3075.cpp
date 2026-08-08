#include <bits/stdc++.h>
using namespace std;

int ans[101010];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    for (int i = 1; i <= N; i++) ans[i] = i;
    
    for (int i = 0; i < M; i++) {
        int X, Y;
        cin >> X >> Y;

        ans[X]++;
        ans[Y]--;
    }
    
    set<int> s;
    for (int i = 1; i <= N; i++) {
        if (s.find(ans[i]) != s.end()) {
            cout << -1;
            return 0;
        }
        s.insert(ans[i]);
    }
    
    for (int i = 1; i <= N; i++) cout << ans[i] << ' ';

    return 0;
}