#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

int idxA[101010], idxB[101010];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    for (int i = 0; i < N; i++) {
        int num;
        cin >> num;
        idxA[num] = i;
    }

    vector<int> lis;
    for (int i = 0; i < N; i++) {
        int num;
        cin >> num;
        
        int val = idxA[num];
        int idx = lower_bound(lis.begin(), lis.end(), val) - lis.begin();

        if (idx == lis.size())
            lis.push_back(val);
        else
            lis[idx] = val;
    }

    cout << lis.size();

    return 0;
}