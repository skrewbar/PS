#include <bits/stdc++.h>
using namespace std;

// returns a set of prime numbers less than or equal to n
set<int> get_prime_numbers(int n) {
    vector<int> is_prime(n+1, true);
    for (int i = 2; 2*i <= n; i++) {
        if (not is_prime[i]) continue;
        for (int j = 2*i; j <= n; j += i) {
            is_prime[j] = false;
        }
    }

    set<int> prime_numbers;
    for (int i = 2; i <= n; i++) {
        if (is_prime[i]) prime_numbers.insert(i);
    }
    return prime_numbers;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    set<int> prime_numbers = get_prime_numbers(1000000);

    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;

        int ans = 0;
        for (int p : prime_numbers) {
            if (n < 2*p) break;
            if (prime_numbers.find(n-p) != prime_numbers.end()) ans++;
        }
        cout << ans << '\n';
    }
}