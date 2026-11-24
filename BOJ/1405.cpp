#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

int delta[] = {0, 0, -1, 1};

bool visited[30][30];
int N;
double probs[4];

double getSimpleProb(int x, int y, int cnt) {
    if (cnt == N)
        return 1;

    double ret = 0;
    for (int k = 0; k < 4; k++) {
        int nx = x + delta[k];
        int ny = y + delta[3 - k];

        if (not visited[nx][ny]) {
            visited[nx][ny] = true;
            ret += getSimpleProb(nx, ny, cnt + 1) * probs[k];
            visited[nx][ny] = false;
        }
    }

    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N >> probs[0] >> probs[1] >> probs[2] >> probs[3];
    for (int i = 0; i < 4; i++)
        probs[i] /= 100;

    visited[14][14] = true;
    print("{:.11f}", getSimpleProb(14, 14, 0));

    return 0;
}