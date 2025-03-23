#include <bits/stdc++.h>
using namespace std;

vector<int> parents;
stack<int> s;
vector<vector<int>> adj;
vector<bool> finished;

vector<vector<int>> SCCs;

int findSCC(int now, int &visitOrder) {
    s.push(now);
    parents[now] = visitOrder++;

    int parent = parents[now];
    for (int next : adj[now]) {
        if (parents[next] == -1) {
            parent = min(findSCC(next, visitOrder), parent);
        } else if (not finished[next]) {
            parent = min(parents[next], parent);
        }
    }

    if (parent == parents[now]) {
        SCCs.emplace_back();
        vector<int> &SCC = SCCs.back();
        while (true) {
            int top = s.top();
            s.pop();
            finished[top] = true;
            SCC.push_back(top);
            if (top == now) break;
        }
    }

    return parent;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<int> costs(n);
    for (int i = 0; i < n; i++) cin >> costs[i];

    adj.assign(n, vector<int>());
    for (int i = 0; i < n; i++) {
        string row;
        cin >> row;
        for (int j = 0; j < n; j++) {
            if (row[j] == '1') {
                adj[i].push_back(j);
            }
        }
    }

    parents.resize(n, -1);
    finished.resize(n);

    int visitOrder = 1;
    for (int i = 0; i < n; i++) {
        if (not finished[i]) findSCC(i, visitOrder);
    }

    int answer = 0;
    for (vector<int> SCC : SCCs) {
        int minCost = 1e6;
        for (int elem : SCC) {
            minCost = min(costs[elem], minCost);
        }
        answer += minCost;
    }
    print("{}", answer);
}