#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

constexpr int MAX_POS = 500'000;
int visitedTime[MAX_POS + 1][2];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;

    fill(&visitedTime[0][0], &visitedTime[MAX_POS][2], -1);
    visitedTime[N][0] = 0;

    queue<pair<int, int>> q;
    q.emplace(N, 0);

    while (not q.empty()) {
        auto [now, isOdd] = q.front();
        q.pop();

        if (now - 1 >= 0 and visitedTime[now - 1][isOdd ^ 1] == -1) {
            visitedTime[now - 1][isOdd ^ 1] = visitedTime[now][isOdd] + 1;
            q.emplace(now - 1, isOdd ^ 1);
        }
        if (now + 1 <= MAX_POS and visitedTime[now + 1][isOdd ^ 1] == -1) {
            visitedTime[now + 1][isOdd ^ 1] = visitedTime[now][isOdd] + 1;
            q.emplace(now + 1, isOdd ^ 1);
        }
        if (now * 2 <= MAX_POS and visitedTime[now * 2][isOdd ^ 1] == -1) {
            visitedTime[now * 2][isOdd ^ 1] = visitedTime[now][isOdd] + 1;
            q.emplace(now * 2, isOdd ^ 1);
        }
    }

    int ans = -1;
    for (int t = 0; t <= 1000; t++) {
        K += t;
        if (K > MAX_POS)
            break;

        for (int isOdd = 0; isOdd < 2; isOdd++) {
            if (visitedTime[K][isOdd] == -1)
                continue;

            if (t - visitedTime[K][isOdd] >= 0 and (t - visitedTime[K][isOdd]) % 2 == 0) {
                ans = t;
                break;
            }
        }

        if (ans != -1)
            break;
    }

    println("{}", ans);

    return 0;
}