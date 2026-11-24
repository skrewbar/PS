#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

int level[1010101], subCnt[1010101], top[1010101];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    for (int i = 1; i <= N; i++) {
        cin >> level[i];

        if (level[i] - level[i - 1] >= 2) {
            println("-1");
            return 0;
        }

        top[level[i]] = i;
        subCnt[top[level[i] - 1]]++;
    }

    for (int i = 1; i <= N; i++)
        println("{}", subCnt[i]);

    return 0;
}