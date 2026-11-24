#include <bits/stdc++.h>
using namespace std;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> snow(n);
    for (int i = 0; i < n; i++) cin >> snow[i];
    
    int ans = 0;
    if (n == 1) ans = snow[0];
    else while (ans <= 1440) {
        sort(snow.begin(), snow.end(), greater<>());
        if (snow[0] == 0) break;
        if (snow[1] == 0) {
            ans += snow[0];
            break;
        }

        ans += snow[1];
        snow[0] -= snow[1];
        snow[1] = 0;
    }

    cout << (ans > 1440 ? -1 : ans);
}