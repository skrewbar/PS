#include <bits/stdc++.h>
using namespace std;

int A[60606], B[60606];
int limitCnt[333][333], stress[333][333];

int N, K, Q;

pair<int, int> processTasks(int l, int r, int G) {
    int C = 0;

    for (int i = l; i <= r; i++) {
        G += A[i] - B[i];
        G = max(G, 0);

        if (G >= K) {
            C++;
            G = 0;
        }
    }

    return {C, G};
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> K >> Q;

    int sz = sqrt(N);

    for (int i = 0; i < N; i++) cin >> A[i] >> B[i];

    for (int b = 0; b * sz < N; b++) {
        for (int s = 0; s <= K; s++) {
            tie(limitCnt[b][s], stress[b][s]) =
                processTasks(b * sz, min(N, (b + 1) * sz) - 1, s);
        }
    }

    while (Q--) {
        int L, R;
        cin >> L >> R;
        L--, R--;

        int lBucket = L / sz;
        int rBucket = R / sz;

        int C = 0;
        int G = 0;

        if (lBucket == rBucket) {
            auto [c, g] = processTasks(L, R, 0);
            C += c;
            G = g;
        } else {
            auto [c, g] = processTasks(L, (lBucket + 1) * sz - 1, 0);
            C += c;
            G = g;

            for (int b = lBucket + 1; b < rBucket; b++) {
                C += limitCnt[b][G];
                G = stress[b][G];
            }

            tie(c, g) = processTasks(rBucket * sz, R, G);
            C += c;
            G = g;
        }

        cout << C << ' ' << G << '\n';
    }

    return 0;
}
