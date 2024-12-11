#include <bits/stdc++.h>
using namespace std;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<bool> is_prime(123456 * 2 + 1, true);
    is_prime[1] = false;

    for (int i = 2; i < is_prime.size(); i++) {
        if (not is_prime[i]) continue;
        for (int j = i+i; j < is_prime.size(); j+=i) {
            is_prime[j] = false;
        }
    }

    vector<int> prime_count(is_prime.size());
    for (int i = 0; i < prime_count.size()-1; i++) {
        prime_count[i+1] = prime_count[i] + is_prime[i+1];
    }

    int n;
    while (true) {
        cin >> n;
        if (n == 0) break;
        cout << prime_count[2*n] - prime_count[n] << '\n';
    }
}