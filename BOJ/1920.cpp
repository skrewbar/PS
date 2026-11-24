#include <iostream>
#include <unordered_set>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    unordered_set<int> set;
    for (int i = 0 ; i < n ; i++) {
        int a;
        cin >> a;
        set.insert(a);
    }

    int m;
    cin >> m;
    for (int i = 0 ; i < m ; i++) {
        int b;
        cin >> b;
        if (set.find(b) != set.end()) cout << 1 << '\n';
        else cout << 0 << '\n';
    }

    return 0;
}