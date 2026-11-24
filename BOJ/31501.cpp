#include <bits/stdc++.h>
using namespace std;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    
    vector<int> difficulty(n);
    for (int i = 0; i < n; i++) cin >> difficulty[i];

    vector<int> lis(n, 1);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (difficulty[i] <= difficulty[j]) continue;
            lis[i] = max(lis[j] + 1, lis[i]);
        }
    }

    vector<int> rev_lds(n, 1);
    for (int i = n-1; i >= 0; i--) {
        for (int j = n-1; j > i; j--) {
            if (difficulty[i] >= difficulty[j]) continue;
            rev_lds[i] = max(rev_lds[j] + 1, rev_lds[i]);
        }
    }

    while (q--) {
        int a;
        cin >> a;
        a--;
        
        cout << lis[a] + rev_lds[a] - 1 << '\n';
    }
}