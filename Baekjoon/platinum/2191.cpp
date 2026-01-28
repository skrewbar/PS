#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

using ll = long long;

pair<ll, ll> mousePos[111], tunnelPos[111];

vector<int> adj[111];
int matching[111];
bool matched[111];

bool match(int mouse) {
    for (auto tunnel : adj[mouse]) {
        if (matched[tunnel])
            continue;

        matched[tunnel] = true;
        if (matching[tunnel] == -1 or match(matching[tunnel])) {
            matching[tunnel] = mouse;
            return true;
        }
    }

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    ll S, V;
    cin >> N >> M >> S >> V;
    V *= 1000;  // distance calibration

    for (int i = 0; i < N; i++) {
        double x, y;
        cin >> x >> y;

        mousePos[i] = pair((int)round(x * 1000), (int)round(y * 1000));
    }
    for (int i = 0; i < M; i++) {
        double x, y;
        cin >> x >> y;

        tunnelPos[i] = pair((int)round(x * 1000), (int)round(y * 1000));
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            ll dx = mousePos[i].first - tunnelPos[j].first;
            ll dy = mousePos[i].second - tunnelPos[j].second;

            ll dist = dx * dx + dy * dy;

            if (dist <= S * S * V * V)
                adj[i].push_back(j);
        }
    }

    fill(matching, matching + M, -1);
    int matchCnt = 0;
    for (int i = 0; i < N; i++) {
        fill(matched, matched + M, false);
        if (match(i))
            matchCnt++;
    }

    println("{}", N - matchCnt);

    return 0;
}