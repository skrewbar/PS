#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

using ll = long long;

template <typename T>
using MinHeap = priority_queue<T, vector<T>, greater<T>>;

struct Pirate {
    ll x, y, c, deadline;
} pirates[505050];

ll abs(const Pirate& p) {
    return p.x * p.x + p.y * p.y;
}

ll square(ll x) {
    return x * x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    ll L;
    cin >> N >> L;

    for (int i = 1; i <= N; i++) {
        Pirate& p = pirates[i];
        cin >> p.x >> p.y >> p.c;

        if (square(L) < abs(p)) {
            p.deadline = 0;
            continue;
        }

        ll lo = 1, hi = L;
        while (lo < hi) {
            ll mid = (lo + hi) >> 1;

            if (square(L - mid) >= abs(p))
                lo = mid + 1;
            else
                hi = mid;
        }

        p.deadline = lo;

        ASSERT(square(L - p.deadline) < abs(p) and
               abs(p) <= square(L - p.deadline + 1));
    }

    sort(pirates + 1, pirates + N + 1, [](const Pirate& p1, const Pirate& p2) {
        return p1.deadline < p2.deadline;
    });

    MinHeap<ll> bounties;
    for (int i = 1; i <= N; i++) {
        if (pirates[i - 1].deadline != pirates[i].deadline) {
            while (bounties.size() > pirates[i - 1].deadline)
                bounties.pop();
        }

        bounties.push(pirates[i].c);
    }

    while (bounties.size() > pirates[N].deadline)
        bounties.pop();

    ll ans = 0;
    while (not bounties.empty()) {
        ans += bounties.top();
        bounties.pop();
    }
    cout << ans;

    return 0;
}