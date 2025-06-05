#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

vector<int> matching;
vector<bool> matched;
vector<vector<int>> matchList;

bool canBeMatched(int p) {
    for (int pick : matchList[p]) {
        if (matched[pick])
            continue;
        matched[pick] = true;

        if (matching[pick] == -1 or canBeMatched(matching[pick])) {
            matching[pick] = p;
            return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k1, k2;
    cin >> n >> m >> k1 >> k2;

    matching = vector(m, -1);
    matched = vector(m, false);
    matchList = vector(n, vector<int>());
    while (k1--) {
        int i, j;
        cin >> i >> j;
        i--, j--;

        matchList[i].push_back(j);
    }

    int wookjeCnt = 0;
    for (int i = 0; i < n; i++) {
        ranges::fill(matched, false);
        if (canBeMatched(i))
            wookjeCnt++;
    }

    matching = vector(m, -1);
    matched = vector(m, false);
    matchList = vector(n, vector<int>());
    while (k2--) {
        int i, j;
        cin >> i >> j;
        i--, j--;

        matchList[i].push_back(j);
    }

    int opponentCnt = 0;
    for (int i = 0; i < n; i++) {
        ranges::fill(matched, false);
        if (canBeMatched(i))
            opponentCnt++;
    }

    cout << (wookjeCnt < opponentCnt ? "네 다음 힐딱이" : "그만 알아보자");
}