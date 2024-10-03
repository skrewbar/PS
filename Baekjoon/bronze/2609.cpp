#include <iostream>
using namespace std;

int gcd(int a, int b) {
    int r = a % b;
    if (r == 0) {
        return b;
    } else {
        return gcd(b, r);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int a, b;
    cin >> a >> b;
    int G = gcd(a, b);

    cout << G << '\n' << a * b / G;

    return 0;
}