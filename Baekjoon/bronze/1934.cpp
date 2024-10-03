#include <iostream>
using namespace std;

int get_max_factor(int a, int b) {
    int r = a % b;
    if (r == 0) {
        return b;
    }
    return get_max_factor(b, r);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t, a, b;
    cin >> t;
    while (t--) {
        cin >> a >> b;
        cout << a*b/get_max_factor(a,b) << '\n';
    }

    return 0;
}