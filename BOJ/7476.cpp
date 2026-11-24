#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

int A[555], B[555];
vector<int> sameIdx[555];

int lcis[555][555];
pair<int, int> prevPair[555][555];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M1;
    cin >> M1;
    for (int i = 1; i <= M1; i++)
        cin >> A[i];

    int M2;
    cin >> M2;
    for (int i = 1; i <= M2; i++)
        cin >> B[i];

    for (int i = 1; i <= M1; i++) {
        for (int j = 1; j <= M2; j++) {
            if (A[i] == B[j]) {
                sameIdx[i].push_back(j);
                lcis[i][j] = 1;
            }
        }
    }

    for (int i = 1; i <= M1; i++) {
        for (int j = 1; j <= M2; j++) {
            if (A[i] != B[j])
                continue;

            for (int k = 1; k < i; k++) {
                if (A[k] >= A[i])
                    continue;

                auto it = lower_bound(sameIdx[k].begin(), sameIdx[k].end(), j);
                if (it == sameIdx[k].begin())
                    continue;

                int l = *(it - 1);
                ASSERT(A[k] == B[l] and A[i] > B[l]);
                if (lcis[k][l] + 1 > lcis[i][j]) {
                    lcis[i][j] = lcis[k][l] + 1;
                    prevPair[i][j] = pair(k, l);
                }
            }
        }
    }

    int ans = 0;
    int i = 0, j = 0;
    for (int k = 1; k <= M1; k++) {
        for (int l = 1; l <= M2; l++) {
            if (lcis[k][l] > ans) {
                ans = lcis[k][l];
                i = k, j = l;
            }
        }
    }

    cout << ans << '\n';

    stack<int> seq;

    while (i > 0 and j > 0) {
        seq.push(A[i]);
        auto [k, l] = prevPair[i][j];
        i = k, j = l;
    }

    ASSERT((int)seq.size() == ans);

    while (not seq.empty()) {
        cout << seq.top() << ' ';
        seq.pop();
    }

    return 0;
}