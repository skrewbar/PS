#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<pair<int, int>> wormholes(N);

    for (auto &[x, y] : wormholes) cin >> x >> y;

    sort(all(wormholes), [&](const auto &a, const auto &b) {
        return tie(a.second, a.first) < tie(b.second, b.first);
    });

    auto isCycleExists = [&](vector<int> &pairing) -> bool {
        for (int i = 0; i < N; i++) {
            vector<bool> visited(N);

            int cur = i;
            while (cur < N) {
                if (visited[cur]) return true;
                visited[cur] = true;

                if (cur + 1 < N and
                    wormholes[cur].second == wormholes[cur + 1].second) {
                    cur = pairing[cur + 1];
                } else break;
            }
        }

        return false;
    };

    auto backtrack = [&](auto &&self, auto &&pairing, int pairCnt) -> int {
        if (pairCnt == N / 2) return isCycleExists(pairing);

        int ret = 0;

        int i = pairCnt;
        while (pairing[i] != -1) i++;
        for (int j = i + 1; j < N; j++) {
            if (pairing[j] != -1) continue;

            pairing[i] = j;
            pairing[j] = i;
            ret += self(self, pairing, pairCnt + 1);
            pairing[i] = pairing[j] = -1;
        }

        return ret;
    };

    cout << backtrack(backtrack, vector(N, -1), 0);

    return 0;
}