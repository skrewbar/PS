#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> A(N + 1);
    for (int i = 1; i <= N; i++) cin >> A[i];
    sort(A.begin() + 1, A.end());

    ll ans = 0;
    ll last = 0;
    for (int i = 2; i <= N; i++) {
        ans += A[i] - last - A[1];
        last += A[i] - last - A[1];
    }

    cout << ans;

    return 0;
}
