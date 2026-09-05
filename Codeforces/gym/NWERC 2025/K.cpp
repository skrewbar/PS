#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int h, w, k, i, t;
    cin >> h >> w >> k >> i >> t;

    vector<char> ans = {'T', 'I', 'K'};
    k--, i--, t--;
    while (k--) ans.push_back('K');
    while (t--) ans.push_back('T');
    while (i--) ans.push_back('I');

    for (int r = 0; r < h; r++) {
        for (int c = 0; c < w; c++)
            cout << ans[r*w + c];
        cout << '\n';
    }

    return 0;
}
