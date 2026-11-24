#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

int matching[111];
vector<int> matchList[111];
bool matched[111];

bool match(int i) {
    for (int j : matchList[i]) {
        if (matched[j])
            continue;
        matched[j] = true;

        if (matching[j] == -1 or match(matching[j])) {
            matching[j] = i;
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

    while (M--) {
        int a, b;
        cin >> a >> b;

        matchList[a].push_back(b);
    }

    fill(matching + 1, matching + N + 1, -1);
    int ans = 0;
    for (int i = 1; i <= N; i++) {
        fill(matched + 1, matched + N + 1, false);
        if (match(i))
            ans++;
    }

    cout << ans;

    return 0;
}