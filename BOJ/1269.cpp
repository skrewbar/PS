#include <bits/stdc++.h>
using namespace std;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int a_cnt, b_cnt;
    cin >> a_cnt >> b_cnt;

    set<int> a;
    while (a_cnt--) {
        int elem;
        cin >> elem;
        a.insert(elem);
    }

    set<int> b;
    while (b_cnt--) {
        int elem;
        cin >> elem;
        b.insert(elem);
    }

    int cnt = 0;
    for (int elem : a) {
        if (b.find(elem) == b.end()) cnt++;
    }
    for (int elem : b) {
        if (a.find(elem) == a.end()) cnt++;
    }
    cout << cnt;
}