#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(_) ((void)0)
#endif
using namespace std;

using ll = long long;

int A[1010101];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll N, B, C;
    cin >> N >> B >> C;
    C = min(B, C);

    for (int i = 0; i < N; i++)
        cin >> A[i];

    ll answer = 0;
    for (int i = 0; i < N; i++) {
        if (A[i + 1] > A[i + 2]) {
            ll count = min(A[i + 1] - A[i + 2], A[i]);
            answer += count * (B + C);

            A[i] -= count;
            A[i + 1] -= count;
        }

        if (A[i + 1] > 0 and A[i + 2] > 0) {
            ll count = min(A[i], A[i + 1]);
            answer += count * (B + 2 * C);

            A[i] -= count;
            A[i + 1] -= count;
            A[i + 2] -= count;
        }

        if (A[i + 1] > 0) {
            ll count = min(A[i], A[i + 1]);
            answer += count * (B + C);

            A[i] -= count;
            A[i + 1] -= count;
        }

        answer += A[i] * B;
    }

    println("{}", answer);

    return 0;
}