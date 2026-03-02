#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(_) ((void)0)
#endif
using namespace std;

int N;

char op[202020];
int a[202020], leftChild[202020], rightChild[202020];

int plusCount = 0, minusCount = 0;
void dfs(int cur, bool plus) {
    if (cur <= N) {
        if (plus)
            plusCount++;
        else
            minusCount++;
        return;
    }

    dfs(leftChild[cur], plus);
    dfs(rightChild[cur], (op[cur] == '+' ? plus : not plus));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> N;

    for (int i = 1; i <= N; i++)
        cin >> a[i];
    for (int i = N + 1; i < 2 * N; i++) {
        cin >> op[i] >> leftChild[i] >> rightChild[i];
    }
    dfs(2 * N - 1, true);

    sort(a + 1, a + N + 1);

    int answer = 0;
    int i = 1;
    while (minusCount--)
        answer -= a[i++];

    i = N;
    while (plusCount--)
        answer += a[i--];

    println("{}", answer);

    return 0;
}