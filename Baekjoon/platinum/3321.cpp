#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, M;
    cin >> N >> M;

    int ans = 0;

    vector<int> height(M), indices;

    for (int i = 0; i < N; i++) {
        string line;
        cin >> line;

        vector<int> newIndices;

        for (int j = 0; j < M; j++) {
            if (line[j] == '1')
                height[j]++;
            else
                height[j] = 0;
        }

        for (int j : indices) {
            if (height[j])
                newIndices.push_back(j);
        }
        for (int j = 0; j < M; j++) {
            if (height[j] == 1)
                newIndices.push_back(j);
        }

        swap(newIndices, indices);

        for (int j = 0; j < indices.size(); j++)
            ans = max(ans, (j + 1) * height[indices[j]]);
    }

    cout << ans;

    return 0;
}