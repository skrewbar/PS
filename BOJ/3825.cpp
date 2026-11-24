#include <bits/stdc++.h>
using namespace std;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    int t;
    cin >> t;
    while (t--) {
        int m, n;
        cin >> m >> n;

        bool is_prime = true;

        int sum = m*m + n*n;
        int factor = 1;
        int k = 2;

        while (sum > 1) {
            if (sum % k == 0) {
                sum /= k;
                factor *= k;

                for (int i = 0; i*i <= factor; i++) {
                    if (not is_prime) break;
                    for (int j = 0; j <= i; j++) {
                        if (not is_prime) break;

                        int temp = i*i + j*j;
                        if (temp <= 1 or temp == (n*n + m*m)) continue;

                        if (factor % temp == 0) {
                            is_prime = false;
                            // cout << i << ' ' << j << '\n';
                        }
                    }
                }
            } else k++;
            if (not is_prime) break;
        }
        cout << (is_prime ? 'P' : 'C') << '\n';
    }
}