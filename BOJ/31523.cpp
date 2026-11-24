#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(unused) ((void)0)
#endif
using namespace std;

enum class BracketType : uint8_t { ROUND, CURLY, SQUARE };
BracketType getBracketTypeOf(char bracket) {
    if (bracket == '(' or bracket == ')')
        return BracketType::ROUND;
    if (bracket == '{' or bracket == '}')
        return BracketType::CURLY;
    return BracketType::SQUARE;
}

bool isOpen(char bracket) {
    return bracket == '(' or bracket == '{' or bracket == '[';
}

int n;
string s;
vector<int> adj[5050];

bool visited[5050];
stack<char> stk;

int getCountOfBalancedPath(int from) {
    visited[from] = true;

    int count = stk.empty();

    for (int nxt : adj[from]) {
        if (visited[nxt])
            continue;
        if (not stk.empty() and isOpen(stk.top()) and not isOpen(s[nxt]) and
            getBracketTypeOf(stk.top()) != getBracketTypeOf(s[nxt]))
            continue;

        if (not stk.empty() and isOpen(stk.top()) and not isOpen(s[nxt]) and
            getBracketTypeOf(stk.top()) == getBracketTypeOf(s[nxt])) {
            char top = stk.top();
            stk.pop();
            count += getCountOfBalancedPath(nxt);
            stk.push(top);
        } else {
            stk.push(s[nxt]);
            count += getCountOfBalancedPath(nxt);
            stk.pop();
        }
    }
    visited[from] = false;

    return count;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    cin >> s;

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;

        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    int answer = 0;
    for (int i = 0; i < n; i++) {
        stk.push(s[i]);
        answer += getCountOfBalancedPath(i);
        stk.pop();
    }

    println("{}", answer);

    return 0;
}