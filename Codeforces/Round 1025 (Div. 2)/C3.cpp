#include <bits/stdc++.h>
using namespace std;

using ll = long long;

int main() {
    int t;
    cin >> t;
    while (t--) {
        ll n;
        cin >> n;
        int response;

        cout << "mul 999999999" << endl;
        cin >> response;

        cout << "digit" << endl;
        cin >> response;

        if (n == 81) {
            cout << "!" << endl;
            cin >> response;
            continue;
        }

        cout << "add " << n - 81 << endl;
        cin >> response;

        cout << "!" << endl;
        cin >> response;
    }
}