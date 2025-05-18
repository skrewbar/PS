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

        cout << "mul 9" << endl;
        cin >> response;

        for (int i = 0; i < 2; i++) {
            cout << "digit" << endl;
            cin >> response;
        }

        cout << "add " << n - 9 << endl;
        cin >> response;

        cout << "!" << endl;
        cin >> response;
    }
}