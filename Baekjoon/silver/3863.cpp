#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

pair<int, int> intersection(const pair<int, int>& range1,
                            const pair<int, int>& range2) {
    return pair(max(range1.first, range2.first),
                min(range1.second, range2.second));
}

void solve(int N, int M) {
    vector<pair<int, int>> callRanges(N);
    for (int i = 0; i < N; i++) {
        int s, d, ign;
        cin >> ign >> ign >> s >> d;

        callRanges[i] = pair(s, s + d);
    }

    for (int i = 0; i < M; i++) {
        int s, d;
        cin >> s >> d;
        int e = s + d;

        int cnt = 0;
        for (const auto& call : callRanges) {
            auto inter = intersection(call, pair(s, e));
            if (inter.second - inter.first > 0)
                cnt++;
        }

        cout << cnt << '\n';
    }
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