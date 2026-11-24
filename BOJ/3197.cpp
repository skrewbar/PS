#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

char lake[1515][1515];
int meltedAt[1515][1515];
bool visited[1515][1515];

int delta[] = {1, -1, 0, 0};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int R, C;
    cin >> R >> C;

    queue<pair<int, int>> swanQueue, meltQueue;

    for (int i = 0; i < R; i++)
        cin >> lake[i];

    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            if (lake[i][j] == 'X') {
                for (int k = 0; k < 4; k++) {
                    int ni = i + delta[k], nj = j + delta[3 - k];

                    if (ni < 0 or ni >= R or nj < 0 or nj >= C)
                        continue;
                    if (lake[ni][nj] != 'X') {
                        meltedAt[i][j] = 1;
                        meltQueue.emplace(i, j);
                        break;
                    }
                }
            } else if (lake[i][j] == 'L' and swanQueue.empty()) {
                visited[i][j] = true;
                swanQueue.emplace(i, j);
                lake[i][j] = '.';
            }
        }
    }

    int time = 0;
    while (true) {
        bool meet = false;
        queue<pair<int, int>> nextQueue;

        while (not swanQueue.empty()) {
            auto [i, j] = swanQueue.front();

            if (lake[i][j] == 'X')
                break;
            swanQueue.pop();

            if (lake[i][j] == 'L') {
                meet = true;
                break;
            }

            for (int k = 0; k < 4; k++) {
                int ni = i + delta[k], nj = j + delta[3 - k];

                if (ni < 0 or ni >= R or nj < 0 or nj >= C or visited[ni][nj])
                    continue;

                visited[ni][nj] = true;

                if (lake[ni][nj] == 'X')
                    nextQueue.emplace(ni, nj);
                else
                    swanQueue.emplace(ni, nj);
            }
        }

        if (meet)
            break;

        swap(nextQueue, swanQueue);

        time++;
        while (not meltQueue.empty()) {
            auto [i, j] = meltQueue.front();

            if (meltedAt[i][j] > time)
                break;
            lake[i][j] = '.';
            meltQueue.pop();

            for (int k = 0; k < 4; k++) {
                int ni = i + delta[k], nj = j + delta[3 - k];

                if (ni < 0 or ni >= R or nj < 0 or nj >= C)
                    continue;
                if (lake[ni][nj] != 'X' or meltedAt[ni][nj] != 0)
                    continue;

                meltedAt[ni][nj] = meltedAt[i][j] + 1;
                meltQueue.emplace(ni, nj);
            }
        }
    }

    println("{}", time);

    return 0;
}