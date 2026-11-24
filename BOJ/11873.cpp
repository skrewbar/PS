#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

int grid[1010][1010];
int height[1010];

void solve(int N, int M) {
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            cin >> grid[i][j];
        }
    }
    fill(height, height + M + 2, 0);

    int ans = 0;
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            if (grid[i][j] == 0)
                height[j] = 0;
            else
                height[j]++;
        }

        stack<int> s;
        s.push(0);
        for (int j = 1; j <= M + 1; j++) {
            while (height[s.top()] > height[j]) {
                int h = height[s.top()];
                s.pop();
                ans = max(ans, h * (j - (s.top() + 1)));
            }
            s.push(j);
        }
    }

    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (true) {
        int N, M;
        cin >> N >> M;

        if (N == 0)
            break;

        solve(N, M);
    }

    return 0;
}