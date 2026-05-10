#include <bits/stdc++.h>
using namespace std;

constexpr int max_a = 1e6;
constexpr int max_sqrt_a = 1e3;

bitset<max_a + 1> isPrime;
int a[101010];

void solve() {
    int n;
    cin >> n;

    bool nonDecreasing = true;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (a[i] < a[i - 1])
            nonDecreasing = false;
    }
    if (nonDecreasing) {
        cout << "Bob\n";
        return;
    }

    bool bobWin = true;
    int prevPrime = -1;
    for (int i = 1; i <= n; i++) {
        if (a[i] == 1) {
            if (a[i] < a[i - 1]) {
                bobWin = false;
                break;
            }
            continue;
        }

        set<int> foundPrimes;
        for (int factor = 1; factor * factor <= a[i]; factor++) {
            if (a[i] % factor != 0)
                continue;

            for (int p : {factor, a[i] / factor}) {
                if (not isPrime[p])
                    continue;
                
                foundPrimes.insert(p);
                if (foundPrimes.size() > 1 or p < prevPrime) {
                    bobWin = false;
                    break;
                }
                prevPrime = p;
            }
        }

        if (not bobWin)
            break;
    }

    cout << (bobWin ? "Bob" : "Alice") << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    isPrime.set();
    isPrime[1] = false;
    for (int i = 2; i <= max_a; i++) {
        if (not isPrime[i])
            continue;

        for (int j = i + i; j <= max_a; j += i)
            isPrime[j] = false;
    }

    int t;
    cin >> t;

    while (t--)
        solve();

    return 0;
}