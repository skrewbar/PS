#include <bits/stdc++.h>
using namespace std;

vector<vector<pair<int, int>>> prev_pos;

int distance(const pair<int, int> &p1, const pair<int, int> &p2) {
    return abs(p1.first - p2.first) + abs(p1.second - p2.second);
}


void update(int &dist, const int &newDist, const pair<int, int> &newPos, const pair<int, int> &prevPos) {
    if (newDist < dist) {
        dist = newDist;
        prev_pos[newPos.first][newPos.second] = prevPos;
    }
}


int main() {
    int n, w;
    cin >> n >> w;

    vector<pair<int, int>> cases(w+1);
    for (int i = 1; i <= w; i++) {
        auto &[first, second] = cases[i];
        cin >> first >> second;
    }
    
    vector<vector<int>> police1(w+1, vector<int>(w+1, 1e9));
    vector<vector<int>> police2 = police1;

    police1[1][0] = distance(pair{1, 1}, cases[1]);
    police2[1][0] = distance(pair{n, n}, cases[1]);

    prev_pos = vector<vector<pair<int, int>>>(w+1, vector<pair<int, int>>(w+1));
    

    for (int caseNum = 2; caseNum <= w; caseNum++) {
        for (int i = 0; i < caseNum - 1; i++) { // 0번째 케이스는 각자 초기 위치
            update(
                police1[caseNum][i],
                police1[caseNum-1][i] + distance(cases[caseNum], cases[caseNum-1]),
                pair{caseNum, i},
                pair{caseNum-1, i}
            );
            update(
                police1[caseNum][caseNum-1],
                police2[caseNum-1][i] + distance(cases[caseNum], (i != 0 ? cases[i] : pair{1, 1})),
                pair{caseNum, caseNum-1},
                pair{i, caseNum-1}
            );
            
            update(
                police2[caseNum][i],
                police2[caseNum-1][i] + distance(cases[caseNum], cases[caseNum-1]),
                pair{i, caseNum},
                pair{i, caseNum-1}
            );
            update(
                police2[caseNum][caseNum-1],
                police1[caseNum-1][i] + distance(cases[caseNum], (i != 0 ? cases[i] : pair{n, n})),
                pair{caseNum-1, caseNum},
                pair{caseNum-1, i}
            );
        }
    }

    pair<int, int> minPos;
    int minDist = 1e9;
    for (int i = 0; i < w; i++) {
        if (police1[w][i] < minDist) {
            minDist = police1[w][i];
            minPos = pair{w, i};
        }
        if (police2[w][i] < minDist) {
            minDist = police2[w][i];
            minPos = pair{i, w};
        }
    }
    cout << minDist << '\n';

    stack<int> answer;
    for (int i = 0; i < w; i++) {
        pair<int, int> nextPos = prev_pos[minPos.first][minPos.second];
        answer.push(minPos.first != nextPos.first ? 1 : 2);
        minPos = nextPos;
    }
    while (not answer.empty()) {
        cout << answer.top() << '\n';
        answer.pop();
    }
}