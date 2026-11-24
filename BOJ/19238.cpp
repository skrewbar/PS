#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(_) ((void)0)
#endif
using namespace std;

constexpr int INF = 1e9;

constexpr int dr[] = {-1, 0, 0, 1}, dc[] = {0, -1, 1, 0};

bool isWall[22][22];
int dist[22][22];

int getDist(const pair<int, int>& p) {
    return dist[p.first][p.second];
}

struct Passenger {
    pair<int, int> depart, dest;
};

int N, M, fuel;

bool canMoveTo(int r, int c) {
    return 1 <= r and r <= N and 1 <= c and c <= N and not isWall[r][c];
}

void findDistFrom(pair<int, int> start) {
    queue<pair<int, int>> q;
    q.push(start);

    fill(&dist[1][1], &dist[N][N + 1], INF);
    auto [r, c] = start;
    dist[r][c] = 0;

    while (not q.empty()) {
        tie(r, c) = q.front();
        q.pop();

        for (int k = 0; k < 4; k++) {
            int nr = r + dr[k];
            int nc = c + dc[k];

            if (not canMoveTo(nr, nc) or dist[nr][nc] != INF)
                continue;

            dist[nr][nc] = dist[r][c] + 1;
            q.emplace(nr, nc);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> M >> fuel;

    for (int i = 1; i <= N; i++)
        for (int j = 1; j <= N; j++)
            cin >> isWall[i][j];

    int r, c;
    cin >> r >> c;
    pair<int, int> taxi = {r, c};

    vector<Passenger> passengers(M);
    for (int i = 0; i < M; i++) {
        cin >> r >> c;
        passengers[i].depart = {r, c};

        cin >> r >> c;
        passengers[i].dest = {r, c};
    }
    sort(passengers.begin(), passengers.end(),
         [&](const Passenger& a, const Passenger& b) {
             return a.depart < b.depart;
         });

    while (not passengers.empty()) {
        findDistFrom(taxi);

        int p = 0;
        for (int i = 1; i < passengers.size(); i++) {
            if (getDist(passengers[i].depart) < getDist(passengers[p].depart))
                p = i;
        }

        Passenger passenger = passengers[p];

        fuel -= getDist(passenger.depart);
        findDistFrom(passenger.depart);
        int d = getDist(passenger.dest);
        fuel -= d;
        if (fuel < 0)
            break;
        fuel += 2 * d;

        taxi = passenger.dest;
        passengers.erase(passengers.begin() + p);
    }

    if (passengers.empty()) {
        cout << fuel;
    } else {
        cout << -1;
    }

    return 0;
}