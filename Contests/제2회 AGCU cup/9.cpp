#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int X, Y;
    cin >> X >> Y;

    int dist = X * X + Y * Y;

    int L1, L2;
    cin >> L1 >> L2;

    auto square = [](int x) { return x * x; };

    if (square(abs(L1 - L2)) <= dist and dist <= square(L1 + L2)) cout << "YES";
    else cout << "NO";

    return 0;
}