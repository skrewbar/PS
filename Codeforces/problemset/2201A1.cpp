#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    
    int prv;
    cin >> prv;
    int start = prv;
    
    int answer = 1;
    
    for (int i = 2; i <= n; i++) {
        int a;
        cin >> a;

        if (a <= start or a > prv + 1) {
            answer++;
            start = prv = a;
            continue;
        }

        prv = a;
    }
    
    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--)
        solve();

    return 0;
}