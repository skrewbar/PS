#include <bits/stdc++.h>
using namespace std;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    int a, b; cin >> a >> b;
    cout << (int)floor(b * log10(a) + 1);


    return 0;
}