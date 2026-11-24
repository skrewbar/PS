#include <bits/stdc++.h>
using namespace std;
using ll = long long;


ll gcd(ll a, ll b) {
    while (b != 0) {
        a %= b;
        swap(a, b);
    }
    return a;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<string> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];

    int k;
    cin >> k;

    vector<int> tenMod_k(51);
    tenMod_k[0] = 1 % k;
    for (int i = 1; i < 51; i++) {
        tenMod_k[i] = tenMod_k[i-1] * 10 % k;
    }

    vector<int> numsMod_k(n);
    for (int i = 0; i < n; i++) {
        reverse(nums[i].begin(), nums[i].end());
        for (int exp = 0; exp < nums[i].size(); exp++) {
            numsMod_k[i] += tenMod_k[exp] * (nums[i][exp] - '0') % k;
            numsMod_k[i] %= k;
        }
    }

    vector<vector<ll>> dp(1 << n, vector<ll>(k));
    dp[0][0] = 1;
    for (int set = 0; set < (1 << n); set++) {
        for (int numIndex = 0; numIndex < n; numIndex++) {
            if (set & 1 << numIndex) continue;
            for (int remainder = 0; remainder < k; remainder++) {
                int newRemainder = (remainder * tenMod_k[nums[numIndex].size()] + numsMod_k[numIndex]) % k;
                dp[set | 1 << numIndex][newRemainder] += dp[set][remainder];
            }
        }
    }

    int universalSet = (1 << n) - 1;
    ll correctAnswerCount = dp[universalSet][0];
    ll answerCount = correctAnswerCount;
    for (int remainder = 1; remainder < k; remainder++) answerCount += dp[universalSet][remainder];
    ll g = gcd(correctAnswerCount, answerCount);
    print("{}/{}", correctAnswerCount / g, answerCount / g);
}