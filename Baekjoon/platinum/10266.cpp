#include <bits/stdc++.h>
using namespace std;

using ll = long long;
ll BASE = 101, MOD = 1e9 + 7;

ll pow(ll base, ll exp, ll mod) {
    ll ret = 1;
    while (exp) {
        if (exp & 1)
            ret = (ret * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return ret;
}

template <typename T>
void uniquify(vector<T>& v) {
    v.erase(unique(v.begin(), v.end()), v.end());
}

// template <typename T>
// ll rabinKarp(vector<T> v, int s) {
//     ll n = v.size();
//     ll ret = 0;
//     for (int i = 0; i < n; i++) {
//         ret += (v[(s + i) % n] * pow(BASE, i, MOD)) % MOD;
//         ret %= MOD;
//     }
//     return ret;
// }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    // 입력
    vector<ll> clock1(n), clock2(n);
    for (int i = 0; i < n; i++)
        cin >> clock1[i];
    for (int i = 0; i < n; i++)
        cin >> clock2[i];

    sort(clock1.begin(), clock1.end()), sort(clock2.begin(), clock2.end());

    // 차분 배열로 변환
    ll degMod = 360'000;
    int back = (clock1.front() - clock1.back() + degMod) % degMod;
    for (int i = 0; i + 1 < n; i++)
        clock1[i] = (clock1[i + 1] - clock1[i] + degMod) % degMod;
    clock1.back() = back;

    back = (clock2.front() - clock2.back() + degMod) % degMod;
    for (int i = 0; i + 1 < n; i++)
        clock2[i] = (clock2[i + 1] - clock2[i] + degMod) % degMod;
    clock2.back() = back;

    // 라빈 카프 해싱
    ll hash1 = 0;
    for (int i = 0; i < n; i++) {
        hash1 += (clock1[i] * pow(BASE, i, MOD)) % MOD;
        hash1 %= MOD;
    }

    ll hash2 = 0;
    for (int i = 0; i < n; i++) {
        hash2 += (clock2[i] * pow(BASE, i, MOD)) % MOD;
        hash2 %= MOD;
    }

    bool isPossible = false;
    for (int s = 0; s < n; s++) {  // s of "start"
        if (hash1 == hash2) {
            isPossible = true;
            for (int i = 0; i < n; i++) {
                if (clock2[(s + i) % n] != clock1[i]) {
                    isPossible = false;
                    break;
                }
            }
        }
        if (isPossible)
            break;

        hash2 = (hash2 - clock2[s] + MOD) % MOD * pow(BASE, MOD-2, MOD) % MOD;
        hash2 = (hash2 + clock2[s] * pow(BASE, n-1, MOD)) % MOD;
    }

    cout << (isPossible ? "possible" : "impossible");
}