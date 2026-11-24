#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(_) ((void)0)
#endif
using namespace std;

using ll = long long;
constexpr ll MOD = 1e9 + 7;

ll power(ll base, ll exp, ll mod) {
    ll ret = 1;

    while (exp) {
        if (exp & 1)
            ret = (ret * base) % MOD;
        base = (base * base) % MOD;
        exp >>= 1;
    }

    return ret;
}

int targetCnt[26];
int cnt[202020][26];

int getCount(int start, int end, char c) {
    int ret = cnt[end][c - 'a'];

    if (start != 0)
        ret -= cnt[start - 1][c - 'a'];

    return ret;
}

struct RabinKarp {
    ll base;
    vector<ll> pref;

    RabinKarp(string& s, ll _base) : base(_base), pref(s.size()) {
        pref[0] = s[0];
        for (int i = 1; i < s.size(); i++)
            pref[i] = (pref[i - 1] + s[i] * power(base, i, MOD) % MOD) % MOD;
    }

    ll getHash(int start, int end) {
        ll ret = pref[end];

        if (start != 0)
            ret = ((ret - pref[start - 1]) % MOD + MOD) % MOD;

        ret *= power(power(base, MOD - 2, MOD), start, MOD);

        return ret % MOD;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string N, H;
    cin >> N >> H;

    for (char c : N)
        targetCnt[c - 'a']++;

    cnt[0][H[0] - 'a'] = 1;
    for (int i = 1; i < H.size(); i++) {
        for (char c = 'a'; c <= 'z'; c++) {
            cnt[i][c - 'a'] = cnt[i - 1][c - 'a'] + (H[i] == c);
        }
    }

    set<tuple<int, int, int>> s;
    RabinKarp hash1(H, 2), hash2(H, 101), hash3(H, 1007);

    for (int i = 0; i + N.size() - 1 < H.size(); i++) {
        int j = i + N.size() - 1;
        bool isPerm = true;

        for (char c = 'a'; c <= 'z'; c++) {
            if (getCount(i, j, c) != targetCnt[c - 'a']) {
                isPerm = false;
                break;
            }
        }

        if (not isPerm)
            continue;

        s.emplace(hash1.getHash(i, j), hash2.getHash(i, j),
                  hash3.getHash(i, j));
    }

    println("{}", s.size());

    return 0;
}