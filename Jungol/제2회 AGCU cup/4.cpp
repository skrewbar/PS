#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    vector<int> d(N + 1);
    for (int i = 1; i <= N; i++) cin >> d[i];

    int ans = 1;
    int maxCnt = 0;
    for (int s = 1; s <= 7; s++) {
        int cnt = 0;

        for (int i = 1; i <= N; i++) {
            if ((d[i] - s) % 7 == 0) cnt++;
        }

        if (cnt > maxCnt) {
            ans = s;
            maxCnt = cnt;
        }
    }

    cout << ans;

    return 0;
}