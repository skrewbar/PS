#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
        arr[i] %= m;
    }

    vector<int> prefixSum = arr;
    for (int i = 1; i < n; i++)
        prefixSum[i] = (prefixSum[i] + prefixSum[i - 1]) % m;

    ll answer = 0;
    vector<int> remainderCnt(m);
    for (int i = 0; i < n; i++) {
        answer += remainderCnt[prefixSum[i]]++;
        if (prefixSum[i] == 0)
            answer++;
    }

    cout << answer;
}