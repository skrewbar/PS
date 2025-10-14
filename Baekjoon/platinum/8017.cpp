#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

int height[2020];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    int ans = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            bool isWaste;
            cin >> isWaste;

            if (isWaste)
                height[j] = 0;
            else
                height[j]++;
        }

        stack<int> s;
        s.push(0);
        for (int j = 1; j <= n + 1; j++) {
            while (height[s.top()] > height[j]) {
                int h = height[s.top()];
                s.pop();
                ans = max(ans, h * (j - (s.top() + 1)));
            }
            s.push(j);
        }
    }

    cout << ans;

    return 0;
}