#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int L;
    cin >> L;

    vector<int> s(L + 1);
    for (int i = 1; i <= L; i++) cin >> s[i];
    sort(s.begin(), s.end());

    int n;
    cin >> n;
    int idx = lower_bound(s.begin(), s.end(), n) - s.begin();

    if (s[idx] == n) {
        cout << 0;
        return 0;
    }

    int lo = s[idx - 1], hi = s[idx];
    cout << (n - lo) * (hi - n) - 1;

    return 0;
}
