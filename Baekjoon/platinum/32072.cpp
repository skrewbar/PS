#include <bits/stdc++.h>
using namespace std;

vector<int> weight;

struct compare {
    bool operator()(int a, int b) {
        return weight[a] > weight[b];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    vector<vector<int>> childs(n);
    for (int i = 1; i < n; i++) {
        int p;
        cin >> p;
        p--;
        childs[p].push_back(i);
    }

    weight = vector(n, 0);
    for (int i = 0; i < n; i++)
        cin >> weight[i];


    priority_queue<int, vector<int>, compare> pq;
    pq.push(0);

    while (not pq.empty()) {
        int root = pq.top();
        pq.pop();

        cout << weight[root] << '\n';

        for (int child : childs[root])
            pq.push(child);
    }
}