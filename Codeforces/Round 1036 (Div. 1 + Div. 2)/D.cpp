#include <bits/stdc++.h>
using namespace std;

#define all(v) v.begin(), v.end()

void solve() {
    int n, k;
    cin >> n >> k;

    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];

    vector<int> sortedA(a);
    sort(all(sortedA));

    int x = sortedA[k - 1];
    vector<int> filtered;
    for (int i = 0; i <= n; i++)
        if (a[i] <= x) filtered.push_back(a[i]);
    a = std::move(filtered);

    int remove = 0;
    for (int i = 1, j = a.size() - 1; i < j; i++, j--) {
        if (a[i] == a[j]) continue;
        remove++;

        if (a[i] == x) j++;
        else if (a[j] == x) i--;
        else {
            cout << "NO\n";
            return;
        }
    }

    cout << (a.size() - remove < k ? "NO" : "YES") << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) solve();

    return 0;
}
