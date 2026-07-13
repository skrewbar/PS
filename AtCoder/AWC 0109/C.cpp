#include <bits/stdc++.h>
using namespace std;

int A[201010], C[201010];
int cnt[201010];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, Q;
    cin >> N >> M >> Q;

    for (int i = 1; i <= N; i++) cin >> A[i];
    for (int i = 1; i <= M; i++) cin >> C[i];

    for (int i = 0; i < Q; i++) {
        int P, D;
        cin >> P >> D;

        cnt[D] = min(cnt[D] + 1, C[D]);
    }

    for (int i = 1; i <= M; i++) cout << cnt[i] << ' ';

    return 0;
}
