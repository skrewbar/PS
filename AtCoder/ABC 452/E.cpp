#include <bits/stdc++.h>
using namespace std;

using ll = long long;

constexpr ll MOD = 998244353;

ll A[505050], B[505050];
ll Asum[505050];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    ll baseSum = 0;
    for (int i = 1; i <= N; i++) {
        cin >> A[i];
        Asum[i] = (Asum[i - 1] + A[i]) % MOD;

        baseSum += A[i] * i % MOD;
        baseSum %= MOD;
    }

    for (int j = 1; j <= M; j++)
        cin >> B[j];

    ll answer = 0;
    for (int j = 1; j <= M; j++) {
        ll sum = baseSum;
        sum %= MOD;
        for (int i = j; i <= N; i += j) {
            sum -= (Asum[min(N, i + j - 1)] - Asum[i - 1]) % MOD * (i / j) %
                      MOD * j % MOD;
            sum %= MOD;
        }
        
        answer += sum * B[j] % MOD;
        answer %= MOD;
    }

    cout << (answer + MOD) % MOD;

    return 0;
}