#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

int length[202][202];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    for (int len = 1; len <= s.size(); len++) {
        for (int i = 0; i <= s.size() - len; i++) {
            int j = i + len - 1;

            length[i][j] = len;

            for (int k = i; k < j; k++)
                length[i][j] =
                    min(length[i][j], length[i][k] + length[k + 1][j]);

            for (int k = 1; k < len; k++) {
                if ((j - i + 1) % k != 0)
                    continue;

                bool canCompress = true;

                for (int l = i + k; l <= j; l += k) {
                    if (not canCompress)
                        break;

                    for (int m = 0; m < k; m++) {
                        if (s[i + m] != s[l + m]) {
                            canCompress = false;
                            break;
                        }
                    }
                }

                if (canCompress) {
                    length[i][j] =
                        min(length[i][j], 2 + length[i][i + k - 1] +
                                              (int)floor(log10(len / k)) + 1);
                    break;
                }
            }
        }
    }

    cout << length[0][s.size() - 1];

    return 0;
}