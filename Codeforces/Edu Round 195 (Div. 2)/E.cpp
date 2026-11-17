#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int n;
string s;
int nxt[303030][10];

int getNext(int i, string str) {
    for (char c : str) {
        if (i >= n) break;
        i = nxt[i][c - '0'];
    }

    return i;
}

ll diff[303030], imos[303030];

void addRange(ll arr[], int l, int r, ll v) {
    arr[l] += v;
    arr[r + 1] -= v;
}
void addAP(int l, int r, ll begin) {
    addRange(diff, l, l, begin);
    addRange(diff, l + 1, r, -1);
    addRange(diff, r + 1, r + 1, -begin + (r - l));
}

void solve() {
    cin >> n;
    cin >> s;

    fill(&nxt[0][0], &nxt[n][10], n);
    fill(&diff[0], &diff[n], 0);
    fill(&imos[0], &imos[n], 0);
    nxt[n - 1][s.back() - '0'] = n - 1;

    for (int i = n - 1; i >= 0; i--) {
        for (int d = 0; d < 10; d++) nxt[i][d] = nxt[i + 1][d];
        nxt[i][s[i] - '0'] = i;
    }

    for (int l = n - 1; l >= 0; l--) {
        int r25 = getNext(l, "2025");
        int r26 = getNext(l, "2026");

        if (r26 <= r25) {
            addAP(l, n - 1, n - l);
        } else {
            addAP(l, r25 - 1, n - l - (r26 - r25));
            addRange(imos, r25, r26 - 1, n - r26);
            addAP(r26, n - 1, n - r26);
        }
    }

    for (int i = 1; i < n; i++) diff[i] += diff[i - 1];
    for (int i = 1; i < n; i++) diff[i] += diff[i - 1];
    for (int i = 1; i < n; i++) imos[i] += imos[i - 1];

    for (int i = 0; i < n; i++) cout << diff[i] + imos[i] << ' ';
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) solve();

    return 0;
}
