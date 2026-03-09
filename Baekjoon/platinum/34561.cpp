#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(_) ((void)0)
#endif
using namespace std;

int parent[303030], A[303030], rootOf[303030];

int findParent(int x) {
    if (x != parent[x])
        parent[x] = findParent(parent[x]);
    return parent[x];
}

void changeValue(int from, int to) {
    if (from == to)
        return;

    int fromRoot = rootOf[from];
    rootOf[from] = -1;

    if (rootOf[to] != -1) {
        parent[fromRoot] = rootOf[to];
    } else {
        rootOf[to] = fromRoot;
        A[fromRoot] = to;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N;
    cin >> N;

    fill(rootOf, rootOf + 300'030, -1);

    for (int i = 1; i <= N; i++) {
        cin >> A[i];

        if (rootOf[A[i]] == -1) {
            parent[i] = i;
            rootOf[A[i]] = i;
        } else {
            parent[i] = rootOf[A[i]];
        }
    }

    int M;
    cin >> M;
    while (M--) {
        int type;
        cin >> type;

        if (type == 1) {
            int x, y;
            cin >> x >> y;

            changeValue(x, y);
        } else {
            int z;
            cin >> z;

            println("{}", A[findParent(z)]);
        }
    }

    return 0;
}