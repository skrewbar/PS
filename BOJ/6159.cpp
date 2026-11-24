#include <bits/stdc++.h>
using namespace std;



int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    int n, s;
    cin >> n >> s;
    vector<int> len(n);
    for (int i = 0 ; i < n ; i++) {
        cin >> len[i];
    }

    sort(len.begin(), len.end());
    int ans = 0;
    int l = 0, r = n-1;
    while (l < r) {
        if (len[l] + len[r] <= s) {
            ans += r - l;
            l++;
        } else {
            r--;
        }
    }
    cout << ans;


    return 0;
}