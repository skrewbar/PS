#include <bits/stdc++.h>
using namespace std;

int di[] = {0, -1, 0, 1};
int dj[] = {1, 0, -1, 0};

int n, m, V;

constexpr int MX = 1010101;

vector<int> adj[MX];
bool finished[MX];
int visitOrder[MX], sccNum[MX];
vector<int> stk;

int visitedCnt = 0, sccCnt = 0;
bool satisfiable = true;

void initVariables() {
    V = 4 * n * m;

    for (int i = 0; i < V; i++)
        adj[i].clear();
    fill(finished, finished + V, false);
    fill(visitOrder, visitOrder + V, -1);
    fill(sccNum, sccNum + V, -1);

    visitedCnt = sccCnt = 0;
    satisfiable = true;
}

int findSCC(int cur) {
    stk.push_back(cur);
    visitOrder[cur] = visitedCnt++;
    int lowLink = visitOrder[cur];

    for (int nxt : adj[cur]) {
        if (finished[nxt])
            continue;

        if (visitOrder[nxt] == -1)
            lowLink = min(lowLink, findSCC(nxt));
        else
            lowLink = min(lowLink, visitOrder[nxt]);
    }

    if (lowLink == visitOrder[cur]) {
        while (true) {
            int top = stk.back();
            stk.pop_back();
            finished[top] = true;
            sccNum[top] = sccCnt;

            if (top == cur)
                break;
        }

        sccCnt++;
    }

    return lowLink;
}

// (x1 or x2)
void addClause(int x1, int x2) {
    x1 = (abs(x1) << 1) + (x1 >= 0);
    x2 = (abs(x2) << 1) + (x2 >= 0);

    adj[x1 ^ 1].push_back(x2);
    adj[x2 ^ 1].push_back(x1);
}

char pattern[555][555];

void solve() {
    cin >> n >> m;

    initVariables();

    int blackCnt = 0, whiteCnt = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++)
            cin >> pattern[i][j];
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int id[4] = {
                (i - 1) * m + j - 1,          // R
                (i - 2) * m + j - 1 + n * m,  // U
                (i - 1) * m + j - 2,          // L
                (i - 1) * m + j - 1 + n * m   // D
            };

            bool isBlack[4] = {}, isWhite[4] = {};
            for (int k = 0; k < 4; k++) {
                isBlack[k] = (pattern[i + di[k]][j + dj[k]] == 'B');
                isWhite[k] = (pattern[i + di[k]][j + dj[k]] == 'W');
            }

            if (pattern[i][j] == 'B') {
                blackCnt++;

                for (int k = 0; k < 2; k++) {
                    if (isWhite[k] and isWhite[k + 2])
                        addClause(id[k], id[k + 2]),
                            addClause(-id[k], -id[k + 2]);
                    else if (isWhite[k])
                        addClause(id[k], id[k]);
                    else if (isWhite[k + 2])
                        addClause(id[k + 2], id[k + 2]);
                    else {
                        cout << "NO\n";
                        return;
                    };
                }
            } else if (pattern[i][j] == 'W') {
                whiteCnt++;

                for (int k = 1; k < 4; k++) {
                    for (int l = 0; l < k; l++) {
                        if (isBlack[k] and isBlack[l])
                            addClause(-id[k], -id[l]);
                    }
                }
            }
        }
    }

    for (int i = 0; i < V; i++) {
        if (finished[i])
            continue;
        findSCC(i);
    }
    for (int i = 0; i < V; i += 2) {
        if (sccNum[i ^ 1] == sccNum[i]) {
            satisfiable = false;
            break;
        }
    }

    if (whiteCnt == 2 * blackCnt and satisfiable)
        cout << "YES\n";
    else
        cout << "NO\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    while (T--)
        solve();

    return 0;
}