#include <bits/stdc++.h>
using namespace std;

struct Query {
    bool add;
    int v;
    bool async;
};

constexpr int SZ = 1 << 20;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<Query> queries(n + 1);
    for (int i = 1; i <= n; i++) {
        char op;
        int v;
        string tok;

        cin >> op >> v >> tok;

        Query &q = queries[i];
        q.add = (op == '+');
        q.v = v;
        q.async = (tok == "async");
    }

    bitset<SZ> res;
    int lastAssign = -1;
    for (int i = 1; i <= n; i++) {
        if (queries[i].add) continue;

        if (queries[i].async) res[queries[i].v] = true;
        lastAssign = i;
    }

    if (lastAssign == -1) {
        cout << 1;
        return 0;
    }

    for (int i = 1; i <= n; i++) {
        if (not queries[i].add) continue;

        if (lastAssign < i) res <<= queries[i].v;
        else if (queries[i].async) res |= res << queries[i].v;
    }

    bitset<SZ> ans = res;
    for (int i = lastAssign + 1; i <= n; i++) {
        if (not queries[i].async) res >>= queries[i].v;
        else res |= res >> queries[i].v;

        ans |= res;
    }

    res.reset();
    res[queries[lastAssign].v] = true;
    for (int i = 1; i <= n; i++) {
        if (not queries[i].add) continue;

        if (lastAssign < i) res <<= queries[i].v;
        else if (queries[i].async) res |= res << queries[i].v;
    }

    ans |= res;

    cout << ans.count();

    return 0;
}
