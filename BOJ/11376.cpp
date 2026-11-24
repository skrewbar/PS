#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

int matching[1010];
bool matched[1010];
vector<int> matchingList[1010];

bool match(int u) {
    for (int v : matchingList[u]) {
        if (matched[v])
            continue;
        matched[v] = true;

        if (matching[v] == -1 or match(matching[v])) {
            matching[v] = u;
            return true;
        }
    }

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    for (int i = 1; i <= N; i++) {
        int cnt;
        cin >> cnt;
        while (cnt--) {
            int work;
            cin >> work;
            matchingList[i].push_back(work);
        }
    }

    fill(matching + 1, matching + 1 + M, -1);

    int ans = 0;
    for (int i = 1; i <= N; i++) {
        for (int j = 0; j < 2; j++) {
            fill(matched + 1, matched + 1 + M, false);
            if (match(i))
                ans++;
        }
    }

    println("{}", ans);

    return 0;
}