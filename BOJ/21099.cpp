#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(_) ((void)0)
#endif
using namespace std;

int A[101010];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    if (n >= 1000) {
        println("Yes");
        return 0;
    }

    for (int i = 0; i < n; i++)
        cin >> A[i];

    vector<bool> exist(1 << 18);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (exist[A[i] ^ A[j]]) {
                println("Yes");
                return 0;
            }
            exist[A[i] ^ A[j]] = true;
        }
    }

    println("No");

    return 0;
}