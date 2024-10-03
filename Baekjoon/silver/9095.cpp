#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int count[11] = { 0 };
    count[1] = 1;
    count[2] = 2;
    count[3] = 4;

    for (int i = 4 ; i < 11 ; i++) {
        for (int j = 1 ; j <= i ; j++) {
            count[i] = count[i-1] + count[i-2] + count[i-3];
        }
    }

    int t; cin >> t;
    for (int i = 0 ; i < t ; i++) {
        int n; cin >> n;
        cout << count[n] << '\n';
    }
    
    return 0;
}