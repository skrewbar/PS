#include <algorithm>
#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

int n, m;
bool isObstacle[110][110];
int rdDiag[110][110];
int ruDiag[110][110];

vector<vector<int>> matchList;
vector<int> matching;
vector<bool> matched;

bool match(int u) {
    for (int v : matchList[u]) {
        if (matched[v])
            continue;
        matched[v] = true;

        if (matching[v] == -1 or match(matching[v])) {
            matching[v] = u;
            return true;
        }
    }

    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    while (m--) {
        int i, j;
        cin >> i >> j;
        isObstacle[i][j] = true;
    }

    int v1 = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = n; j >= 1; j--) {
            if (isObstacle[i][j] or rdDiag[i][j] != 0)
                continue;
            v1++;
            for (int ni = i, nj = j; ni <= n and nj <= n and not isObstacle[ni][nj]; ni++, nj++)
                rdDiag[ni][nj] = v1;
        }
    }

    matchList = vector(v1 + 1, vector<int>());
    int v2 = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (isObstacle[i][j] or ruDiag[i][j] != 0)
                continue;
            v2++;
            for (int ni = i, nj = j; ni <= n and nj >= 1 and not isObstacle[ni][nj]; ni++, nj--) {
                ruDiag[ni][nj] = v2;
                if (rdDiag[ni][nj] != 0)
                    matchList[rdDiag[ni][nj]].push_back(v2);
            }
        }
    }
    matching = vector(v2 + 1, -1);
    matched = vector(v2 + 1, false);

    int maxMatching = 0;
    for (int i = 1; i <= v1; i++) {
        fill(matched.begin(), matched.end(), false);
        maxMatching += match(i);
    }

    print("{}", maxMatching);
}