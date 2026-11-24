#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

int startSufSum[100100], endPrefSum[100100], range[100100];
pair<int, int> intervals[200200];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    for (int i = 1; i <= n; i++) {
        auto& [a, b] = intervals[i];
        cin >> a >> b;

        startSufSum[a]++, endPrefSum[b]++;
        range[a]++, range[b]--;
    }

    for (int i = 1; i <= 100'000; i++) {
        endPrefSum[i] += endPrefSum[i - 1];
        range[i] += range[i - 1];
    }

    for (int i = 100'000 - 1; i >= 1; i--)
        startSufSum[i] += startSufSum[i + 1];

    int s1 = 0;
    for (int i = 1; i <= n; i++) {
        auto& [l, r] = intervals[i];
        s1 = max(s1, n - endPrefSum[l] - startSufSum[r]);
    }

    int s2 = 0;
    for (int i = 1; i <= 100'000; i++)
        s2 = max(s2, range[i]);

    print("{} {}", s1, s2);

    return 0;
}