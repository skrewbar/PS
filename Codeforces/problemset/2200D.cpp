#include <bits/stdc++.h>
using namespace std;

int p[202020];

void solve() {
    int n, x, y;
    cin >> n >> x >> y;

    for (int i = 1; i <= n; i++)
        cin >> p[i];

    int minIdx = x + 1;
    for (int i = x + 2; i <= y; i++) {
        if (p[i] < p[minIdx])
            minIdx = i;
    }

    int left = 1;
    while (left <= x and p[left] < p[minIdx])
        left++;
    int right = y + 1;
    if (left == x + 1)
        while (right <= n and p[right] < p[minIdx])
            right++;

    for (int i = 1; i < left; i++)
        cout << p[i] << ' ';
    if (right != y + 1) {
        for (int i = y + 1; i < right; i++)
            cout << p[i] << ' ';
    }
    cout << p[minIdx] << ' ';
    for (int i = minIdx + 1;; i++) {
        if (i > y)
            i = x + 1;
        if (i == minIdx)
            break;
        cout << p[i] << ' ';
    }
    if (left != x + 1) {
        for (int i = left; i <= x; i++)
            cout << p[i] << ' ';
    }
    for (int i = right; i <= n; i++)
        cout << p[i] << ' ';
    cout << '\n';
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