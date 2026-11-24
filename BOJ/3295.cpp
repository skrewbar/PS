#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

vector<int> matching;
vector<bool> matched;
vector<vector<int>> matchingList;

bool canBeMatched(int u) {
    for (int v : matchingList[u]) {
        if (matched[v])
            continue;
        matched[v] = true;

        if (matching[v] == -1 or canBeMatched(matching[v])) {
            matching[v] = u;
            return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--) {
        int n, m;
        cin >> n >> m;

        matching = vector(n, -1);
        matched = vector(n, false);
        matchingList = vector(n, vector<int>());

        while (m--) {
            int u, v;
            cin >> u >> v;
            matchingList[u].push_back(v);
        }

        int maxMatch = 0;
        for (int i = 0; i < n; i++) {
            ranges::fill(matched, false);
            if (canBeMatched(i))
                maxMatch++;
        }

        cout << maxMatch << '\n';
    }
}