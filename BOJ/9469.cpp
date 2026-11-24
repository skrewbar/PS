#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

void solve() {
    int N;
    long double D, A, B, F;
    cin >> N >> D >> A >> B >> F;

    cout << N << ' ' << (F * D) / (A + B) << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout.precision(6);
    cout << fixed;

    int P;
    cin >> P;
    while (P--)
        solve();

    return 0;
}