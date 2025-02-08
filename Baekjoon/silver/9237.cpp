#include <bits/stdc++.h>
using namespace std;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    vector<int> t(n);
    for (int i = 0; i < n; i++) cin >> t[i];
    sort(t.begin(), t.end(), greater<>());

    int turnaround = n;
    for (int i = 0; i < n; i++) {
        turnaround = max(t[i] + i + 1, turnaround);
    }

    cout << turnaround + 1;
}