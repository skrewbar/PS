#include <bits/stdc++.h>
using namespace std;

#define all(v) (v).begin(), (v).end()
#define compress(v) \
    sort(all(v));   \
    v.erase(unique(all(v)), (v).end())

#define by(x) [](const auto& a, const auto& b) { return a.x < b.x; }
#define by_desc(x) [](const auto& a, const auto& b) { return a.x > b.x; }

constexpr int MX = 202020, INF = 2e9;

struct Range {
    int start, end, id;
};

int prevId[MX][20];

Range rng[MX], s[MX], e[MX];
vector<Range> stk;

int getMaxCntOfRange(int l, int r) {
    auto it = lower_bound(all(stk), Range(0, r, 0), by(end));
    if (it == stk.begin())
        return 0;

    auto [start, end, id] = *(it - 1);

    if (start <= l)
        return 0;

    int ret = 1;
    for (int i = 17; i >= 0; i--) {
        if (rng[prevId[id][i]].start <= l)
            continue;

        id = prevId[id][i];
        ret += 1 << i;
    }

    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    for (int i = 1; i <= N; i++) {
        auto& [start, end, id] = rng[i];
        id = i;
        cin >> start >> end;

        s[i] = e[i] = rng[i];
    }
    sort(s + 1, s + 1 + N, by(start));
    sort(e + 1, e + 1 + N, by(end));

    for (int i = 1, j = 1, prev = 0; i <= N; i++) {
        auto& [start, end, id] = s[i];

        while (not stk.empty() and end <= stk.back().end)
            stk.pop_back();
        stk.push_back(s[i]);

        for (; e[j].end < start; j++) {
            if (rng[prev].start < e[j].start)
                prev = e[j].id;
        }
        prevId[id][0] = prev;

        for (int k = 1; k < 18; k++)
            prevId[id][k] = prevId[prevId[id][k - 1]][k - 1];
    }

    println("{}", getMaxCntOfRange(0, INF));

    map<int, int> endOfStart;
    endOfStart[0] = 0;
    endOfStart[INF] = INF;

    for (int id = 1; id <= N; id++) {
        auto& [start, end, _] = rng[id];

        auto l = endOfStart.upper_bound(start);
        auto r = l--;

        if (start <= l->second or r->first <= end)
            continue;

        if (getMaxCntOfRange(l->second, start) +
                getMaxCntOfRange(end, r->first) ==
            getMaxCntOfRange(l->second, r->first) - 1) {
            print("{} ", id);
            endOfStart.emplace(start, end);
        }
    }

    return 0;
}