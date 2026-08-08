#include <bits/stdc++.h>
using namespace std;

vector<int> adj[2020];
int in[2020];

stack<int> s;
bool onStack[2020];

int sccCnt;
int sccNum[2020];

bool impossible;

int findSCC(int cur) {
    s.push(cur);
    onStack[cur] = true;

    int lowLink = in[cur];

    for (int next : adj[cur]) {
        if (in[next] == -1) {
            in[next] = in[cur] + 1;
            lowLink = min(lowLink, findSCC(next));
        } else if (onStack[next]) lowLink = min(lowLink, in[next]);
    }

    if (lowLink == in[cur]) {
        while (true) {
            int top = s.top();
            s.pop();

            onStack[top] = false;
            sccNum[top] = sccCnt;

            if (sccNum[top ^ 1] == sccNum[top]) impossible = true;

            if (top == cur) break;
        }

        sccCnt++;
    }

    return lowLink;
}

int n, m;
void solve() {
    fill(adj, adj + 2*n + 2, vector<int>());
    fill(in, in + 2 * n + 2, -1);
    sccCnt = 0;
    fill(sccNum, sccNum + 2 * n + 2, -1);
    impossible = false;

    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;

        a = abs(2 * a) + (a > 0);
        b = abs(2 * b) + (b > 0);

        adj[a ^ 1].push_back(b);
        adj[b ^ 1].push_back(a);
    }
    adj[0b10].push_back(0b11);

    for (int i = 2; i <= 2 * n + 1; i++) {
        if (in[i] == -1) findSCC(i);
    }

    if (impossible) {
        cout << "no\n";
    } else cout << "yes\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    while (cin >> n >> m) solve();

    return 0;
}