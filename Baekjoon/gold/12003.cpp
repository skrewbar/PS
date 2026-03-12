#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(_) ((void)0)
#endif
using namespace std;

int sz[50505];
int maxCntAfter[50505];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;

    for (int i = 1; i <= N; i++)
        cin >> sz[i];
    sort(sz, sz + N + 1);

    int lo, hi;
    lo = hi = N;
    for (int i = N - 1; i >= 0; i--) {
        maxCntAfter[i] = maxCntAfter[i + 1];

        while (i < lo) {
            while (i < lo and sz[hi] - sz[lo] <= K)
                lo--;
            maxCntAfter[i] = max(maxCntAfter[i], hi - lo);
            if (i < lo)
                hi--;
        }
    }

    int answer = 0;
    lo = hi = 1;
    while (hi <= N) {
        while (hi <= N and sz[hi] - sz[lo] <= K) {
            hi++;
            answer = max(answer, hi - lo + maxCntAfter[hi - 1]);
        }
        lo++;
    }

    println("{}", answer);

    return 0;
}