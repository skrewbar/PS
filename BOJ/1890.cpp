#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

using ll = long long;

ll cnt[101][101];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cnt[0][0] = 1;

    int N;
    cin >> N;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int num;
            cin >> num;

            if (num == 0)
                continue;

            if (i + num < N)
                cnt[i + num][j] += cnt[i][j];
            if (j + num < N)
                cnt[i][j + num] += cnt[i][j];
        }
    }

    cout << cnt[N - 1][N - 1] << '\n';

    return 0;
}