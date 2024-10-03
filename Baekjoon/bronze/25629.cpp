#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int len, even, odd;
    even = 0; odd = 0;
    cin >> len;
    for (int i = 0 ; i < len ; i++) {
        int a;
        cin >> a;
        if (a % 2 == 0) {
            even += 1;
        } else {
            odd += 1;
        }
    }
    
    if (odd-1 == even || even == odd) {
        cout << 1;
    } else {
        cout << 0;
    }
}