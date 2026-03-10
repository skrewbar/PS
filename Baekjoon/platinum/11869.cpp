#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(_) ((void)0)
#endif
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M;
    cin >> M;

    int g = 0;
    for (int i = 0; i < M; i++) {
        int p;
        cin >> p;
        g ^= p;
    }

    if (g)
        println("koosaga");
    else
        println("cubelover");

    return 0;
}