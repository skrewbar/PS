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

    int n;
    cin >> n;

    int prevRect[2], ans[2];
    cin >> prevRect[0] >> prevRect[1];
    ans[0] = prevRect[1], ans[1] = prevRect[0];

    n--;
    while (n--) {
        int rect[2];
        cin >> rect[0] >> rect[1];

        int newAns[2] = {};

        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                newAns[i] = max(newAns[i], ans[j] + abs(rect[i] - prevRect[j]) +
                                               rect[i ^ 1]);
            }
        }

        swap(prevRect, rect);
        swap(ans, newAns);
    }

    cout << max(ans[0], ans[1]);

    return 0;
}