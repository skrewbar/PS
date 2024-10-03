#include <iostream>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    bool is_can = true;
    int n, d;
    cin >> n;
    d = 0;
    vector<int> a(n);
    cin >> a[0];
    if (n != 1) {
        cin >> a[1];
        d = a[1] - a[0];
    }
    for (int i = 2 ; i < n ; i++) {
        cin >> a[i];
        if (a[i] - a[i-1] != d) {
            is_can = false;
            break;
        }
    }

    if (is_can) {
        cout << "YES\n";
        for (int i = 0 ; i < n ; i++) {
            cout << a[i] << ' ';
        }
        cout << '\n';
        for (int i = 0 ; i < n ; i++) {
            cout << 0 << ' ';
        }
    } else {
        cout << "NO";
    }
}