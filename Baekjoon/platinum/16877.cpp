#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

constexpr int MAX_STONE = 3'000'000;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> fib(40);
    fib[1] = 1;
    for (int i = 2; i < (int)fib.size(); i++)
        fib[i] = fib[i - 1] + fib[i - 2];

    vector<int> grundy(MAX_STONE + 1);
    for (int i = 1; i < (int)grundy.size(); i++) {
        vector<bool> next(40);
        for (int j = 1; i - fib[j] >= 0; j++)
            next[grundy[i - fib[j]]] = true;
        while (next[grundy[i]])
            grundy[i]++;
    }

    int n;
    cin >> n;
    int xorGrundy = 0;
    for (int i = 0; i < n; i++) {
        int p;
        cin >> p;
        xorGrundy ^= grundy[p];
    }

    cout << (xorGrundy == 0 ? "cubelover" : "koosaga");
}