#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int L, K, C;
    cin >> L >> K >> C;

    vector<int> pos(K + 1);
    for (int i = 0; i < K; i++)
        cin >> pos[i];
    pos[K] = L;
    sort(pos.begin(), pos.end());

    auto findFirstCut = [&](int lenLimit) {
        int cut = C;
        int end = L;

        for (int i = K - 1; i >= 0 and cut; i--) {
            if (end - pos[i] > lenLimit) {
                if (pos[i + 1] - pos[i] > lenLimit)
                    return -1;
                cut--;
                end = pos[i + 1];
            }
        }

        if (cut > 0)
            end = pos[0];

        if (end > lenLimit)
            return -1;

        return end;
    };

    int lo = 1, hi = L;
    while (lo < hi) {
        int mid = (lo + hi) / 2;

        if (findFirstCut(mid) != -1)
            hi = mid;
        else
            lo = mid + 1;
    }


    print("{} {}", lo, findFirstCut(lo));

    return 0;
}