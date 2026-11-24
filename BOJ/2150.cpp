#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> adj;
vector<int> parents;
vector<bool> finished;
stack<int> s;

set<set<int>> SCCs;


int findSCC(int x, int &visitOrder) {
    parents[x] = visitOrder++;
    s.push(x);

    int parent = parents[x];
    for (int next : adj[x]) {
        if (parents[next] == -1) {
            parent = min(findSCC(next, visitOrder), parent);
        } else if (not finished[next]) {
            parent = min(parents[next], parent);
        }
    }

    if (parent == parents[x]) { // 자식들이 내 부모에 도달 못한 경우
        set<int> SCC;
        while (true) {
            int top = s.top();
            s.pop();
            finished[top] = true;
            SCC.insert(top);
            if (top == x) break;
        }
        SCCs.insert(SCC);
    }

    return parent;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int v, e;
    cin >> v >> e;

    adj.assign(v, vector<int>());
    for (int i = 0; i < e; i++) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        adj[a].push_back(b);
    }

    parents.assign(v, -1);
    finished.assign(v, false);
    
    int visitOrder = 1;
    for (int i = 0; i < v; i++) {
        if (not finished[i]) findSCC(i, visitOrder);
    }

    println("{}", SCCs.size());
    for (set<int> SCC : SCCs) {
        for (int elem : SCC) {
            print("{} ", elem+1);
        }
        print("-1\n");
    }
}