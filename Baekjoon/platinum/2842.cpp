#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

constexpr int deltaRow[] = {0, -1, -1, -1, 0, 1, 1, 1},
              deltaCol[] = {1, 1, 0, -1, -1, -1, 0, 1};

int N;
char village[55][55];
int height[55][55];

pair<int, int> postOffice(-1, -1);

int deliveryCnt = 0;

bool canDelivery(int minHeight, int maxHeight) {
    int officeHeight = height[postOffice.first][postOffice.second];
    if (officeHeight < minHeight or officeHeight > maxHeight)
        return false;

    vector<vector<bool>> visited(N, vector(N, false));
    queue<pair<int, int>> q;

    visited[postOffice.first][postOffice.second] = true;
    q.push(postOffice);

    int remainDelivery = deliveryCnt;

    while (not q.empty()) {
        auto [r, c] = q.front();
        q.pop();

        if (village[r][c] == 'K')
            remainDelivery--;

        for (int k = 0; k < 8; k++) {
            int nr = r + deltaRow[k];
            int nc = c + deltaCol[k];

            if (nr < 0 or nr >= N or nc < 0 or nc >= N)
                continue;
            if (visited[nr][nc])
                continue;
            if (height[nr][nc] < minHeight or height[nr][nc] > maxHeight)
                continue;

            visited[nr][nc] = true;
            q.push(pair(nr, nc));
        }
    }

    return remainDelivery == 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;

    for (int i = 0; i < N; i++) {
        cin >> village[i];

        for (int j = 0; j < N; j++) {
            if (village[i][j] == 'K')
                deliveryCnt++;
            if (village[i][j] == 'P')
                postOffice = pair(i, j);
        }
    }

    vector<int> allHeights;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cin >> height[i][j];
            allHeights.push_back(height[i][j]);
        }
    }

    sort(allHeights.begin(), allHeights.end());
    allHeights.erase(unique(allHeights.begin(), allHeights.end()), allHeights.end());

    int ans = allHeights.back() - allHeights.front();
    for (int i = 0; i < allHeights.size(); i++) {
        int lo = i, hi = allHeights.size();

        while (lo < hi) {
            int mid = (lo + hi) / 2;

            if (canDelivery(allHeights[i], allHeights[mid]))
                hi = mid;
            else
                lo = mid + 1;
        }

        if (lo == allHeights.size())
            continue;

        ans = min(ans, allHeights[lo] - allHeights[i]);
    }

    println("{}", ans);

    return 0;
}