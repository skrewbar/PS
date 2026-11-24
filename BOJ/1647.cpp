#include <bits/stdc++.h>
using namespace std;
using increasing_pq = priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>>;
using ll = long long;

int parent[100001];


int findParent(int x) {
    if (parent[x] == x) return x;
    return parent[x] = findParent(parent[x]);
}


void unionParent(int x, int y) {
    x = findParent(x);
    y = findParent(y);

    if (x != y) parent[x] = y;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    int n, m, mstLine = 0;
    ll mstCost = 0;

    cin >> n >> m;

    for (int i = 1 ; i <= n ; i++) {
        parent[i] = i;
    }

    increasing_pq pq;
    for (int i = 0 ; i < m ; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        pq.push({c, a, b});
    }
    
    while (mstLine != n-2) {
        vector<int> line = pq.top();
        pq.pop();
        int a = line[1], b = line[2], c = line[0];
        
        if (findParent(a) != findParent(b)) {
            mstCost += c;
            mstLine++;
            unionParent(a, b);
        }
    }

    cout << mstCost;


    return 0;
}