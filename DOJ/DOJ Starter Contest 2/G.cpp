#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M, K;
    cin >> N >> M >> K;

    vector<string> answers(N + 1);
    unordered_map<string, int> cnt;
    for (int i = 1; i <= N; i++) {
        cin >> answers[i];
        answers[i] = '#' + answers[i];

        cnt[answers[i]]++;
    }

    bool consistent = false;
    for (int i = 1; i <= N; i++) {
        if (cnt[answers[i]] == K) {
            consistent = true;
            break;
        }
    }

    if (K == 0) {
        set<int> s;
        for (int i = 1; i <= N; i++) {
            int v = 0;
            for (int j = min(20, M); j >= 1; j--) {
                if (answers[i][j] == 'O') v |= (1 << (j - 1));
            }
            s.insert(v);
        }

        for (int i = 0;; i++) {
            int lg = (i == 0 ? -1 : 31 - __builtin_clz(i));
            if (lg >= M) break;

            if (s.find(i) == s.end()) {
                consistent = true;
                break;
            }
        }
    }

    if (consistent) cout << "YES";
    else cout << "NO";

    return 0;
}
