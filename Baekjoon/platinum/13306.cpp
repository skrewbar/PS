#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(unused) ((void)0)
#endif
using namespace std;

struct DisjointSet {
    vector<int> parent;

    DisjointSet(int n) : parent(n) {
        for (int i = 0; i < n; i++)
            parent[i] = i;
    }

    int findParent(int x) {
        if (parent[x] != x)
            parent[x] = findParent(parent[x]);
        return parent[x];
    }

    void unionParent(int x, int y) {
        int xRoot = findParent(x);
        int yRoot = findParent(y);

        if (xRoot != yRoot)
            parent[yRoot] = xRoot;
    }

    bool isConnected(int x, int y) { return findParent(x) == findParent(y); }
};

struct Query {
    enum class Type : uint8_t {
        REMOVE_EDGE = 0,
        ASK_PATH = 1,
    };

    Type type;
    vector<int> args;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;

    vector<int> parent(N + 1);

    for (int i = 2; i <= N; i++) {
        cin >> parent[i];
    }

    vector<Query> queries(N - 1 + Q);
    vector<bool> answer(N - 1 + Q);
    for (int i = 0; i < N - 1 + Q; i++) {
        Query& query = queries[i];

        int x;
        cin >> x;

        query.type = Query::Type(x);
        if (query.type == Query::Type::REMOVE_EDGE) {
            query.args = vector<int>(1);
            cin >> query.args[0];
        } else {
            query.args = vector<int>(2);
            cin >> query.args[0] >> query.args[1];
        }
    }

    DisjointSet disjointSet(N + 1);
    for (int i = N - 1 + Q - 1; i >= 0; i--) {
        const Query& query = queries[i];

        if (query.type == Query::Type::REMOVE_EDGE) {
            int b = query.args[0];
            disjointSet.unionParent(b, parent[b]);
        } else {
            answer[i] = disjointSet.isConnected(query.args[0], query.args[1]);
        }
    }

    for (int i = 0; i < N - 1 + Q; i++) {
        const Query& query = queries[i];

        if (query.type == Query::Type::ASK_PATH) {
            if (answer[i])
                println("YES");
            else
                println("NO");
        }
    }

    return 0;
}