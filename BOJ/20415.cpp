#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

int dp[44][50505];
int limit[44];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    int s, g, p, d;
    cin >> s >> g >> p >> d;

    string grades;
    cin >> grades;
    for (int i = 1; i <= N; i++) {
        switch (grades[i - 1]) {
            case 'B': {
                limit[i] = s - 1;
                break;
            }
            case 'S': {
                limit[i] = g - 1;
                break;
            }
            case 'G': {
                limit[i] = p - 1;
                break;
            }
            case 'P': {
                limit[i] = d - 1;
                break;
            }
            case 'D': {
                limit[i] = limit[i - 1] + d;
                break;
            }
        }
    }

    int ans = 0, prev = 0;
    for (int i = 1; i <= N; i++) {
        if (prev >= limit[i]) {
            ans -= prev - limit[i];
            prev = limit[i];
        }

        prev = min(d, limit[i] - prev);
        ans += prev;
    }

    println("{}", ans);

    return 0;
}