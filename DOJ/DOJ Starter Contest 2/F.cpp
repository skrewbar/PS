#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> P(N + 1);
    vector<int> pos(N + 1);
    for (int i = 1; i <= N; i++) {
        cin >> P[i];
        pos[P[i]] = i;
    }

    int ans = 1;
    for (int i = 1; i < N; i++) {
        if (pos[i + 1] < pos[i]) ans++;
    }

    cout << ans;

    return 0;
}
