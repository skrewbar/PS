#include <iostream>
using namespace std;
using ll = long long int;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    ll n, k, x;
    cin >> n >> k >> x;

    cout << n + 1 - k*3 + (x < 2) + (x < 5);

    return 0;
}