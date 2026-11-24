#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

set<int> idxSet;
int getPrevIndex(int i) {
    if (idxSet.find(i) == idxSet.begin())
        return 0;
    return *--idxSet.find(i);
}
int getNextIndex(int i) {
    if (idxSet.find(i) == --idxSet.end())
        return 0;
    return *++idxSet.find(i);
}

vector<int> a, idx;
bool isMonotone(int i, int j, int k) {
    return (a[i] > a[j] and a[j] > a[k]) or (a[i] < a[j] and a[j] < a[k]);
}

long long n;
long long answer = 0;
void query(int i) {
    answer += i * (n - i + 1);

    int prev1 = getPrevIndex(i);
    int prev2 = getPrevIndex(prev1);

    int next1 = getNextIndex(i);
    int next2 = getNextIndex(next1);

    if (prev2 and next1 and isMonotone(prev2, prev1, next1))
        answer += prev2 * (n - next1 + 1);
    if (prev1 and next2 and isMonotone(prev1, next1, next2))
        answer += prev1 * (n - next2 + 1);

    if (prev2 and isMonotone(prev2, prev1, i))
        answer -= prev2 * (n - i + 1);
    if (prev1 and next1 and isMonotone(prev1, i, next1))
        answer -= prev1 * (n - next1 + 1);
    if (next2 and isMonotone(i, next1, next2))
        answer -= i * (n - next2 + 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    a = idx = vector<int>(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        idx[a[i]] = i;
    }

    for (int x = 1; x <= n; x++) {
        idxSet.insert(idx[x]);

        query(idx[x]);
        print("{}\n", answer);
    }

    return 0;
}