#include <bits/stdc++.h>
using namespace std;

int A[202020], B[202020];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    for (int i = 1; i <= N; i++) cin >> A[i];
    for (int i = 1; i <= N - 1; i++) cin >> B[i];

    auto calc = [&]() {
        int ret = 0;

        bool added = false;
        for (int i = 1; i <= N - 1; i++) {
            if ((A[i] + A[i + 1] + added) % 2 != B[i]) {
                added = true;
                ret++;
            } else added = false;
        }

        return ret;
    };

    int ans = calc();
    A[1]++;
    ans = min(ans, calc() + 1);
    cout << ans;

    return 0;
}
