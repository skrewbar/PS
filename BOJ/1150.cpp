#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(_) ((void)0)
#endif
using namespace std;

template <typename T>
using MinHeap = priority_queue<T, vector<T>, greater<T>>;

int s[101010], l[101010], r[101010], lDist[101010], rDist[101010];
bool used[101010];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    MinHeap<tuple<int, int, int>> pq;

    cin >> s[0];
    r[0] = 1;
    for (int i = 1; i < n; i++) {
        cin >> s[i];

        l[i] = i - 1;
        r[i] = i + 1;
        lDist[i] = rDist[i - 1] = s[i] - s[i - 1];

        pq.emplace(lDist[i], i - 1, i);
    }

    int answer = 0;
    int count = 0;
    while (count < k) {
        auto [dist, i, j] = pq.top();
        pq.pop();

        if (used[i] or used[j])
            continue;

        answer += dist;
        count++;

        used[i] = used[j] = true;

        if (i == 0 or j == n - 1)
            continue;

        r[l[i]] = r[j];
        rDist[l[i]] += rDist[j] - dist;

        l[r[j]] = l[i];
        lDist[r[j]] += lDist[i] - dist;

        pq.emplace(lDist[i] + rDist[j] - dist, l[i], r[j]);
    }

    cout << answer;

    return 0;
}