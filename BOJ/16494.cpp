#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> arr(n);
    for (int i = 0; i < n; i++)
        cin >> arr[i];

    int answer = -1e9;
    for (int k = 0; k < 1 << n; k++) {
        int sum = 0, count = 0, groupCnt = 0;
        bool group = false;

        for (int i = 0; i < n; i++) {
            if (k & (1 << i)) {
                sum += arr[i];
                count++;
                if (not group) {
                    group = true;
                    groupCnt++;
                }
            } else
                group = false;
        }

        if (groupCnt <= m and count >= m) {
            answer = max(answer, sum);
        }
    }

    cout << answer;
}