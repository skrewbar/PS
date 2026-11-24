#include <bits/stdc++.h>
using namespace std;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int size = 1000001;
    vector<long long> g(size);
    for (int i = 1; i < size; i++) {
        for (int j = 1; i * j < size; j++) {
            g[i*j] += i;
        }
    }
    for (int i = 1; i < size; i++) {
        g[i] += g[i-1];
    }

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        cout << g[n] << '\n';
    }
}