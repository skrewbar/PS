#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

using ll = long long;

vector<pair<ll, ll>> producers, consumers;
ll ans = 0;

ll getProfit(int p, int c) {
    return (consumers[c].first - producers[p].first) *
           (consumers[c].second - producers[p].second);
}

void dnc(int s, int e, int l, int r) {
    if (s > e)
        return;

    int m = (s + e) >> 1;

    int i = l;
    while (i <= r and consumers[i].first <= producers[m].first)
        i++;
    int opt = min(i, r);
    ll profit = 0;
    for (; i <= r; i++) {
        ll p = getProfit(m, i);
        if (p > profit) {
            profit = p;
            opt = i;
        }
    }
    ans = max(ans, profit);

    dnc(s, m - 1, l, opt);
    dnc(m + 1, e, opt, r);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    cin >> m >> n;

    producers.reserve(m);
    consumers.reserve(n);

    vector<pair<ll, ll>> temp(m);
    for (int i = 0; i < m; i++)
        cin >> temp[i].first >> temp[i].second;
    sort(temp.begin(), temp.end());
    ll minD = LLONG_MAX;
    for (int i = 0; i < m; i++) {
        if (temp[i].second > minD)
            continue;
        minD = min(minD, temp[i].second);
        producers.push_back(temp[i]);
    }
    temp.clear();

    temp.resize(n);
    for (int i = 0; i < n; i++)
        cin >> temp[i].first >> temp[i].second;
    sort(temp.begin(), temp.end());
    ll maxD = 0;
    for (int i = n - 1; i >= 0; i--) {
        if (temp[i].second < maxD)
            continue;
        maxD = max(maxD, temp[i].second);
        consumers.push_back(temp[i]);
    }
    reverse(consumers.begin(), consumers.end());

    dnc(0, producers.size() - 1, 0, consumers.size() - 1);
    cout << ans;

    return 0;
}