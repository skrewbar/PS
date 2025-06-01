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

    vector<int> grundy(1001, 0);

    for (int i = 2; i < (int)grundy.size(); i++) {
        vector<bool> makable(grundy.size());
        for (int j = 0; j <= i - 2; j++)
            makable[grundy[j] ^ grundy[(i - 2) - j]] = true;
        while (makable[grundy[i]])
            grundy[i]++;
    }

    int n;
    cin >> n;
    cout << (grundy[n] != 0 ? 1 : 2);
    return 0;
}