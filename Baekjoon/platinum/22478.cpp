#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(_) ((void)0)
#endif
using namespace std;

using ll = long long;

ll power(ll base, ll exp) {
    ll ret = 1;

    while (exp) {
        if (exp & 1)
            ret *= base;
        base *= base;
        exp >>= 1;
    }

    return ret;
}

ll getMultipleCnt(ll start, ll end, ll base) {
    ll c = 0;

    while (start <= end and start % base != 1) {
        if (start % base == 0)
            c++;
        start++;
    }

    return c + (end - start + 1) / base;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll s;
    cin >> s;

    ll lo = 1;
    ll digit = 1;
    while (true) {
        ll cnt = digit * 9 * power(10, digit - 1);
        cnt += (4 - digit) * getMultipleCnt(lo, 10 * lo - 1, 3);
        cnt += (4 - digit) * getMultipleCnt(lo, 10 * lo - 1, 5);
        cnt += digit * getMultipleCnt(lo, 10 * lo - 1, 15);

        if (s <= cnt)
            break;

        s -= cnt;
        lo *= 10;
        digit++;
    }

    ll hi = lo * 10 - 1;
    while (lo < hi) {
        ll mid = (lo + hi) / 2;

        ll cnt = digit * (mid - lo + 1);
        cnt += (4 - digit) * getMultipleCnt(lo, mid, 3);
        cnt += (4 - digit) * getMultipleCnt(lo, mid, 5);
        cnt += digit * getMultipleCnt(lo, mid, 15);

        if (s <= cnt)
            hi = mid;
        else {
            lo = mid + 1;
            s -= cnt;
        }
    }

    string str;
    for (int i = 0; i < 20; i++) {
        if (lo % 3 == 0 and lo % 5 == 0)
            str.append("FizzBuzz");
        else if (lo % 3 == 0)
            str.append("Fizz");
        else if (lo % 5 == 0)
            str.append("Buzz");
        else
            str.append(to_string(lo));
        lo++;
    }

    for (int i = 0; i < 20; i++)
        print("{}", str[s + i - 1]);

    return 0;
}