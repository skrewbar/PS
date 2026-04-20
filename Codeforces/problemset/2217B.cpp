#include <bits/stdc++.h>
using namespace std;

int a[202020];

void solve() {
    int n, k;
    cin >> n >> k;

    for (int i = 0; i < n; i++)
        cin >> a[i];

    int sp;
    cin >> sp;
    sp--;

    int left = 0;
    for (int i = sp - 1; i >= 0; i--) {
        if (a[i] != a[i + 1])
            left++;
    }
    if (a[0] == a[sp])
        left--;

    int right = 0;
    for (int i = sp + 1; i < n; i++) {
        if (a[i] != a[i - 1])
            right++;
    }
    if (a[n - 1] == a[sp])
        right--;

    int answer = max(left, right);
    if (answer & 1)
        answer++;

    println("{}", answer);
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