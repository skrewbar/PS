#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    string s;
    int k;
    cin >> s >> k;
    string p = s;
    reverse(p.begin(), p.end());
    if (p == s) {
        cout << "YES";
    } else {
        cout << "NO";
    }
}