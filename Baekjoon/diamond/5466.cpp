#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

using ll = long long;

constexpr ll INF = 1e15;

struct SegmentTree {
    int n;
    vector<ll> t;

    SegmentTree(int _n) : n(_n), t(n << 1, -INF) {}

    void modify(int i, ll v) {
        i += n;
        for (t[i] = max(t[i], v); i > 1; i >>= 1)
            t[i >> 1] = max(t[i], t[i ^ 1]);
    }

    ll getRangeMax(int l, int r) {
        ll ret = -INF;

        for (l += n, r += n; l <= r; l >>= 1, r >>= 1) {
            if (l & 1)
                ret = max(ret, t[l++]);
            if (~r & 1)
                ret = max(ret, t[r--]);
        }

        return ret;
    }
};

struct Market {
    ll day, pos, profit;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, U, D, S;
    cin >> N >> U >> D >> S;

    vector<Market> markets(N);
    for (auto& [day, pos, profit] : markets)
        cin >> day >> pos >> profit;

    sort(markets.begin(), markets.end(), [&](const Market& a, const Market& b) {
        if (a.day != b.day)
            return a.day < b.day;
        else
            return a.pos < b.pos;
    });

    vector<ll> maxProfit(N);

    SegmentTree upstream(505050), downstream(505050);
    upstream.modify(S, S * D);
    downstream.modify(S, -S * U);

    auto getMaxProfit = [&](int i) {
        ll upProfit =
            upstream.getRangeMax(0, markets[i].pos - 1) - markets[i].pos * D;
        ll downProfit =
            downstream.getRangeMax(markets[i].pos + 1, downstream.n - 1) +
            markets[i].pos * U;

        return max(upProfit, downProfit) + markets[i].profit;
    };

    int lo = 0, hi = 0;
    while (hi < N) {
        while (hi + 1 < N and markets[hi].day == markets[hi + 1].day)
            hi++;

        ll prevProfit = getMaxProfit(lo);
        maxProfit[lo] = prevProfit;
        // go downstream
        for (int i = lo + 1; i <= hi; i++) {
            prevProfit =
                max(getMaxProfit(i),
                    prevProfit - (markets[i].pos - markets[i - 1].pos) * D +
                        markets[i].profit);
            maxProfit[i] = prevProfit;
        }

        prevProfit = getMaxProfit(hi);
        maxProfit[hi] = max(maxProfit[hi], prevProfit);
        // go upstream
        for (int i = hi - 1; i >= lo; i--) {
            prevProfit =
                max(getMaxProfit(i),
                    prevProfit - (markets[i + 1].pos - markets[i].pos) * U +
                        markets[i].profit);
            maxProfit[i] = max(maxProfit[i], prevProfit);
        }

        for (int i = lo; i <= hi; i++) {
            upstream.modify(markets[i].pos, maxProfit[i] + markets[i].pos * D);
            downstream.modify(markets[i].pos,
                              maxProfit[i] - markets[i].pos * U);
        }

        hi++;
        lo = hi;
    }

    ll ans = max({0LL, upstream.getRangeMax(0, S) - S * D,
                  downstream.getRangeMax(S, downstream.n - 1) + S * U});

    println("{}", ans);

    return 0;
}