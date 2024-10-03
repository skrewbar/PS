#include <bits/stdc++.h>
#define fastio() ios::sync_with_stdio(false); cin.tie(nullptr);
using namespace std;
using ll = long long;

ll cnt[10];


ll power(ll base, ll exp) {
    if (exp == 0) return 1;

    ll x = power(base, exp / 2);

    if (exp % 2 == 1) return x * x * base;
    else return x * x;
}


int main() {
    fastio();

    ll n;
    cin >> n;

    int maxDigit;
    for (int i = 0; i < 10; i++) {
        if (n / power(10, i) != 0) maxDigit = i;
    }

    for (int i = 0; i < maxDigit; i++) {
        ll temp = n / power(10, i+1) * power(10, i);
        
        cnt[0] += (n / power(10, i+1)-1) * power(10, i);
        for (int j = 1; j < 10; j++) {
            cnt[j] += temp;
        }


        ll nowDigit = n / power(10, i) % 10;
        for (int j = 0; j < nowDigit; j++) {
            cnt[j] += power(10, i);
        }
        cnt[nowDigit] += n % power(10, i) + 1;
    }

    ll lastDigit = n / power(10, maxDigit) % 10;
    for (int j = 1; j < lastDigit; j++) {
        cnt[j] += power(10, maxDigit);
    }
    cnt[lastDigit] += n % power(10, maxDigit) + 1;


    for (int i = 0; i <= 9; i++) {
        cout << cnt[i] << ' ';
    }
    
    return 0;
}