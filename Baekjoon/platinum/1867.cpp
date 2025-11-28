#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

vector<int> matchList[555];
bool isMatched[555];
int matching[555];

bool match(int row) {
    for (int col : matchList[row]) {
        if (isMatched[col])
            continue;

        isMatched[col] = true;
        if (matching[col] == -1 or match(matching[col])) {
            matching[col] = row;
            return true;
        }
    }

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    while (k--) {
        int r, c;
        cin >> r >> c;

        matchList[r].push_back(c);
    }

    fill(matching + 1, matching + n + 1, -1);

    int ans = 0;
    for (int r = 1; r <= n; r++) {
        fill(isMatched + 1, isMatched + n + 1, false);

        if (match(r))
            ans++;
    }

    cout << ans;

    return 0;
}