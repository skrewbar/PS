#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <cmath>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    while (true) {
        vector<int> v(3);
        for (int i = 0 ; i < 3 ; i++) {
            cin >> v[i];
        }

        if (accumulate(v.begin(), v.end(), 0) == 0) {
            return 0;
        }

        sort(v.begin(), v.end());

        if (pow(v[2], 2) == pow(v[0], 2) + pow(v[1], 2)) {
            cout << "right\n";
        } else {
            cout << "wrong\n";
        }
    }
}