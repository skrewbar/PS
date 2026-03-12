#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(_) ((void)0)
#endif
using namespace std;

int grundy[2020];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    grundy[0] = 0;
    grundy[1] = 1;
    for (int len = 1; len <= n; len++) {
        vector<bool> used(len + 1);

        for (int i = 1; i < len; i++) {
            int g = 0;
            if (i - 3 >= 0)
                g ^= grundy[i - 3];
            if (len - i - 2 >= 0)
                g ^= grundy[len - i - 2];

            used[g] = true;
        }

        while (used[grundy[len]])
            grundy[len]++;
    }

    if (grundy[n])
        println("1");
    else
        println("2");

    return 0;
}