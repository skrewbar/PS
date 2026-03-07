#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(_) ((void)0)
#endif
using namespace std;

int seq[202020], prv[202020], nxt[202020], lastPos[202020];
vector<int> values;

bool isNonBoring(int start, int end) {
    if (start >= end)
        return true;

    for (int i = 0; i <= (end - start + 1) / 2; i++) {
        for (int p : {start + i, end - i}) {
            if (prv[p] < start and end < nxt[p])
                return isNonBoring(start, p - 1) and isNonBoring(p + 1, end);
        }
    }

    return false;
}

void solve() {
    int n;
    cin >> n;

    values.clear();
    values.reserve(n);
    for (int i = 0; i < n; i++) {
        cin >> seq[i];
        values.push_back(seq[i]);
    }

    ranges::sort(values);
    values.erase(ranges::unique(values).begin(), values.end());
    for (int i = 0; i < n; i++)
        seq[i] = ranges::lower_bound(values, seq[i]) - values.begin();

    fill(prv, prv + n, -1);
    fill(nxt, nxt + n, n);
    fill(lastPos, lastPos + n, -1);
    for (int i = 0; i < n; i++) {
        if (lastPos[seq[i]] != -1) {
            prv[i] = lastPos[seq[i]];
            nxt[prv[i]] = i;
        }

        lastPos[seq[i]] = i;
    }

    if (isNonBoring(0, n - 1))
        println("non-boring");
    else
        println("boring");
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--)
        solve();

    return 0;
}