#include <bits/stdc++.h>
using namespace std;

#define all(v) (v).begin(), (v).end()

vector<int> a[3030];

bool compare(const vector<int> &v1, const vector<int> &v2) {
    for (int i = 0; i < min(v1.size(), v2.size()); i++) {
        if (v1[i] != v2[i]) return v1[i] < v2[i];
    }

    return v1.size() < v2.size();
}

void solve() {
    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        int l;
        cin >> l;

        a[i].resize(l);
        for (int j = 0; j < l; j++) cin >> a[i][j];

        reverse(all(a[i]));
        set<int> s;

        vector<int> v;
        for (int j = 0; j < l; j++) {
            if (s.find(a[i][j]) != s.end()) continue;
            s.insert(a[i][j]);
            v.push_back(a[i][j]);
        }

        swap(a[i], v);
    }

    for (int t = 0; t < n; t++) {
        sort(a + t, a + n, compare);

        set<int> erased;
        for (int num : a[t]) erased.insert(num);

        for (int i = t + 1; i < n; i++) {
            vector<int> v;

            for (int j = 0; j < a[i].size(); j++) {
                if (erased.find(a[i][j]) != erased.end()) continue;
                v.push_back(a[i][j]);
            }

            swap(v, a[i]);
        }
    }

    for (int i = 0; i < n; i++)
        for (int j = 0; j < a[i].size(); j++) cout << a[i][j] << ' ';

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
