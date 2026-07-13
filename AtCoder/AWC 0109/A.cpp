#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int D[101010];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, S, K;
    cin >> N >> S >> K;

    for (int i = 1; i <= N; i++) cin >> D[i];

    ll ans = S;
    for (int i = 1; i <= N; i++) ans += D[i] + K;

    cout << ans;

    return 0;
}
