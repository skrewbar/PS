#include <bits/stdc++.h>
using namespace std;

map<int, int> visitedCnt, trySum;

int a[101010];

void solve() {
    int n;
    cin >> n;

    visitedCnt.clear();
    trySum.clear();

    for (int i = 1; i <= n; i++) cin >> a[i];

    int v = a[1];
    int tryCnt = -1;
    while (v != 1) {
        visitedCnt[v]++;
        trySum[v] += ++tryCnt;

        if (v & 1) v++;
        else v /= 2;
    }
    visitedCnt[1]++;
    trySum[1] += ++tryCnt;
    if (a[1] == 1) {
        visitedCnt[2]++;
        trySum[2] += ++tryCnt;
    }

    for (int i = 2; i <= n; i++) {
        v = a[i];
        tryCnt = -1;
        while (v != 1) {
            tryCnt++;
            if (visitedCnt.contains(v)) {
                visitedCnt[v]++;
                trySum[v] += tryCnt;
            }

            if (v & 1) v++;
            else v /= 2;
        }
        visitedCnt[1]++;
        trySum[1] += ++tryCnt;
        if (a[i] == 1) {
            visitedCnt[2]++;
            trySum[2] += ++tryCnt;
        }
    }

    int answer = 1e9;
    for (auto &[v, cnt] : visitedCnt) {
        if (cnt != n) continue;
        answer = min(answer, trySum[v]);
    }

    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) solve();

    return 0;
}