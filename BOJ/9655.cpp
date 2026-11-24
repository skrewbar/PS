#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

bool canWin[1010];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    canWin[1] = canWin[3] = true;
    for (int i = 4; i <= N; i++)
        canWin[i] = (not canWin[i - 1] or not canWin[i - 3]);

    cout << (canWin[N] ? "SK" : "CY");

    return 0;
}