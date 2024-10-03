#include <bits/stdc++.h>
using namespace std;


int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    int t; cin >> t;
    while (t--) {
        int n; cin >> n;
        vector<int> arr(n+1, 0);
        
        for (int i = 0 ; i < n ; i++) {
            cin >> arr[i];
        }

        int g = 0;
        for (int i = 1 ; i < n ; i++) {
            g = gcd(g, abs(arr[i] - arr[0]));
        }
        if (g == 0) cout << "INFINITY\n";
        else cout << g << '\n';
    }


    return 0;
}