#include <bits/stdc++.h>
using namespace std;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<int> diff(n);
    for (int i = 0; i < n; i++) cin >> diff[i];

    vector<int> lis_len(n);
    vector<int> lis;
    for (int i = 0; i < n; i++) {
        int idx = lower_bound(lis.begin(), lis.end(), diff[i]) - lis.begin();
        if (idx == lis.size()) lis.push_back(diff[i]);
        else lis[idx] = diff[i];
        lis_len[i] = idx+1;
    }

    vector<int> lds_len(n);
    vector<int> lds;
    for (int i = n-1; i >= 0; i--) {
        int idx = lower_bound(lds.begin(), lds.end(), diff[i], greater<int>()) - lds.begin();
        if (idx == lds.size()) lds.push_back(diff[i]);
        else lds[idx] = diff[i];
        lds_len[i] = idx+1;
    }

    while (q--) {
        int a;
        cin >> a;
        a--;
        cout << lis_len[a] + lds_len[a] - 1 << '\n';
    }
}