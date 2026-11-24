#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int nA, nB;
    cin >> nA >> nB;

    set<int> a;
    while (nA--) {
        int e;
        cin >> e;
        a.insert(e);
    }

    while (nB--) {
        int e;
        cin >> e;
        a.erase(e);
    }

    cout << a.size() << '\n';
    for (int e : a)
        cout << e << ' ';
}