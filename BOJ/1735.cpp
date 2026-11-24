#include <bits/stdc++.h>
using namespace std;


int gcd(int a, int b) {
    while (b != 0) {
        a %= b;
        swap(a, b);
    }
    return a;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int numer1, denom1, numer2, denom2;
    cin >> numer1 >> denom1 >> numer2 >> denom2;

    int numer = denom1 * numer2 + denom2 * numer1;
    int denom = denom1 * denom2;
    int g = gcd(numer, denom);
    cout << numer / g << ' ' << denom / g;
}