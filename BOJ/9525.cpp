#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

bool isPawn[110][110];
int rowNum[110][110];

vector<vector<int>> matchList;
vector<int> matching;
vector<bool> matched;

bool match(int u) {
    for (int v : matchList[u]) {
        if (matched[v])
            continue;
        matched[v] = true;

        if (matching[v] == -1 or match(matching[v])) {
            matching[v] = u;
            return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        char row[110];
        cin >> row;

        for (int j = 0; j < n; j++) {
            if (row[j] == 'X')
                isPawn[i][j] = true;
        }
    }

    int rowCnt = 0;
    for (int i = 0; i < n; i++) {
        int j = 0;
        while (j < n) {
            while (j < n and isPawn[i][j])
                j++;

            while (j < n and not isPawn[i][j])
                rowNum[i][j++] = rowCnt;
            rowCnt++;
        }
    }

    matchList.assign(rowCnt, vector<int>());
    int colCnt = 0;
    for (int j = 0; j < n; j++) {
        int i = 0;
        while (i < n) {
            while (i < n and isPawn[i][j])
                i++;

            while(i < n and not isPawn[i][j])
                matchList[rowNum[i++][j]].push_back(colCnt);
            colCnt++;
        }
    }

    matching.assign(colCnt, -1);
    matched.assign(colCnt, false);

    int maxMatching = 0;
    for (int i = 0; i < rowCnt; i++) {
        fill(matched.begin(), matched.end(), false);
        maxMatching += match(i);
    }

    print("{}", maxMatching);
    return 0;
}