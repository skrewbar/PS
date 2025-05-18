#include <bits/stdc++.h>
using namespace std;

vector<bool> matched;
vector<int> matching;
vector<vector<int>> matchList;

bool match(int cow) {
    for (int barn : matchList[cow]) {
        if (matched[barn]) continue;
        matched[barn] = true;
        if (matching[barn] == -1 or match(matching[barn])) {
            matching[barn] = cow;
            return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    matchList = vector(n, vector<int>());
    for (auto &list : matchList) {
        int s;
        cin >> s;
        while (s--) {
            int barn;
            cin >> barn;
            list.push_back(barn - 1);
        }
    }

    matched = vector(m, false);
    matching = vector(m, -1);
    int answer = 0;
    for (int i = 0; i < n; i++) {
        ranges::fill(matched, false);
        answer += match(i);
    }

    cout << answer;
}