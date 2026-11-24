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

    cout << N << ' ';
    for (int i = 1; i < (N + 1) >> 1; i++)
        cout << i << ' ' << N - i << ' ';
    if (~N & 1)
        cout << N / 2 << ' ';

    return 0;
}