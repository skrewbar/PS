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

    int cnt = 0, ans = 0;
    int getOn = -1, getOff = -1;
    while (getOn != 0) {
        cin >> getOff >> getOn;

        cnt += getOn - getOff;
        ans = max(ans, cnt);
    }

    println("{}", ans);

    return 0;
}