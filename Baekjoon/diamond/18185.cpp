#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(_) ((void)0)
#endif
using namespace std;

int A[10101];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    for (int i = 0; i < N; i++)
        cin >> A[i];

    int answer = 0;
    for (int i = 0; i < N; i++) {
        if (A[i + 1] > A[i + 2]) {
            int cnt = min(A[i], A[i + 1] - A[i + 2]);
            answer += 5 * cnt;

            A[i] -= cnt;
            A[i + 1] -= cnt;
        }

        if (A[i + 2]) {
            int cnt = min({A[i], A[i + 1], A[i + 2]});
            answer += 7 * cnt;

            A[i] -= cnt;
            A[i + 1] -= cnt;
            A[i + 2] -= cnt;
        }

        if (A[i + 1]) {
            int cnt = min(A[i], A[i + 1]);
            answer += 5 * cnt;

            A[i] -= cnt;
            A[i + 1] -= cnt;
        }

        answer += 3 * A[i];
    }

    println("{}", answer);

    return 0;
}