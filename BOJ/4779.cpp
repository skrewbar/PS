#include <bits/stdc++.h>
using namespace std;

char str[600000];


void solve(int start, int end) {
    int remove_size = end - start + 1;
    if (remove_size == 1) return;

    solve(start, start + remove_size/3 - 1);
    fill(&str[start + remove_size/3], &str[end - remove_size/3 + 1], ' ');
    solve(end - remove_size/3 + 1, end);
}


int main() {
    ios::sync_with_stdio(false);
    // cin.tie(nullptr);


    int n;
    while (cin >> n) {
        n = pow(3, n);
        fill(str, str+n, '-');
        solve(0, n-1);
        for (int i = 0 ; i < n ; i++) {
            cout << str[i];
        }
        cout << '\n';
    }


    return 0;
}