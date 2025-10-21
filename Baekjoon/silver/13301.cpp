#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

using ll = long long;

ll fibonacci[88];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    fibonacci[1] = fibonacci[2] = 1;
    for (int i = 3; i <= N + 2; i++)
        fibonacci[i] = fibonacci[i - 1] + fibonacci[i - 2];

    cout << (fibonacci[N + 2] << 1);

    return 0;
}