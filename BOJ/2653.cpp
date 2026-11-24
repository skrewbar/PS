#include <bits/stdc++.h>
using namespace std;

int n;
vector<vector<bool>> bHate;
vector<bool> visited;


void findGroup(int p, set<int> &group) {
    for (int i = 0; i < n; i++) {
        if (visited[i] or bHate[p][i]) continue;
        visited[i] = true;
        group.insert(i);
        findGroup(i, group);
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    bHate.assign(n, vector<bool>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int hate;
            cin >> hate;
            bHate[i][j] = hate;
        }
    }

    for (int i = 0; i < n; i++) {
        bool like = false;
        for (int j = 0; j < n; j++) {
            if (i == j) continue;

            if (bHate[i][j] != bHate[j][i]) {
                print("0");
                return 0;
            }

            if (not bHate[j][i]) like = true;
        }
        if (not like) {
            print("0");
            return 0;
        }
    }

    vector<set<int>> groups;

    visited.assign(n, false);
    for (int i = 0; i < n; i++) {
        if (visited[i]) continue;
        visited[i] = true;
        set<int> group = {i};
        findGroup(i, group);
        groups.push_back(group);
    }

    println("{}", groups.size());
    for (auto group : groups) {
        for (auto person : group) print("{} ", person+1);
        print("\n");
    }
}