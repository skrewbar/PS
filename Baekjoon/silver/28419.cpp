#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    long long sum[2] = {0, 0};
    for (int i = 1; i <= N; i++) {
        int num;
        cin >> num;

        sum[i & 1] += num;
    }

    if (N == 3 and sum[1] > sum[0])
        cout << -1;
    else
        cout << abs(sum[1] - sum[0]);

    return 0;
}