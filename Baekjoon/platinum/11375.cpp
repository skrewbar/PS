#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> jobs;
vector<int> matching;
vector<bool> matched;

// returns whether p(erson) can be matched with a job.
bool canBeMatched(int p) {
    for (int job : jobs[p]) {
        if (matched[job]) continue;

        matched[job] = true;
        if (matching[job] == -1 or canBeMatched(matching[job])) {
            matching[job] = p;
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
    jobs = vector(n, vector<int>());
    matching = vector(m, -1);
    matched = vector(m, false);

    for (int i = 0; i < n; i++) {
        int count;
        cin >> count;
        while (count--) {
            jobs[i].emplace_back();
            cin >> jobs[i].back();
            jobs[i].back()--;
        }
    }

    int answer = 0;
    for (int i = 0; i < n; i++) {
        fill(matched.begin(), matched.end(), false);
        answer += canBeMatched(i);
    }

    cout << answer;
}