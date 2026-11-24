#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

constexpr int INF = 1e9;

struct Bus {
    bool isVertical;
    int fixedCoord;
    int lo, hi;

    Bus() = default;
    Bus(const pair<int, int>& depart, const pair<int, int>& dest) {
        isVertical = (depart.second == dest.second);
        if (isVertical) {
            fixedCoord = depart.second;
            lo = min(depart.first, dest.first);
            hi = max(depart.first, dest.first);
        } else {
            fixedCoord = depart.first;
            lo = min(depart.second, dest.second);
            hi = max(depart.second, dest.second);
        }
    }

    bool isIntersect(const Bus& bus) const {
        if (isVertical == bus.isVertical)
            return (fixedCoord == bus.fixedCoord) and
                   (lo <= bus.hi and bus.lo <= hi);

        return (lo <= bus.fixedCoord and bus.fixedCoord <= hi) and
               (bus.lo <= fixedCoord and fixedCoord <= bus.hi);
    }
} buses[5050];

vector<int> adj[5050];
int cnt[5050];

int m, n, k;

vector<int> findBusesPassing(const pair<int, int>& point) {
    const auto& [r, c] = point;

    vector<int> ret;

    for (int i = 0; i < k; i++) {
        int lo_r, hi_r, lo_c, hi_c;

        lo_r = hi_r = buses[i].fixedCoord;
        lo_c = buses[i].lo;
        hi_c = buses[i].hi;

        if (buses[i].isVertical) {
            swap(lo_r, lo_c);
            swap(hi_r, hi_c);
        }

        if ((lo_r <= r and r <= hi_r) and (lo_c <= c and c <= hi_c))
            ret.push_back(i);
    }

    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> m >> n;
    cin >> k;

    for (int i = 0; i < k; i++) {
        int b, r1, c1, r2, c2;
        cin >> b >> r1 >> c1 >> r2 >> c2;

        buses[i] = Bus(pair(r1, c1), pair(r2, c2));

        for (int j = 0; j < i; j++) {
            if (buses[i].isIntersect(buses[j])) {
                adj[i].push_back(j);
                adj[j].push_back(i);
            }
        }
    }

    pair<int, int> depart, dest;
    cin >> depart.first >> depart.second >> dest.first >> dest.second;

    fill(cnt, cnt + k, INF);
    queue<int> q;
    for (int i : findBusesPassing(depart)) {
        cnt[i] = 1;
        q.push(i);
    }

    while (not q.empty()) {
        int now = q.front();
        q.pop();

        for (int nxt : adj[now]) {
            if (cnt[nxt] != INF)
                continue;

            cnt[nxt] = cnt[now] + 1;
            q.push(nxt);
        }
    }

    int ans = INF;
    for (int i : findBusesPassing(dest))
        ans = min(ans, cnt[i]);

    println("{}", ans);

    return 0;
}