#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

struct Team {
    string name;
    int solveCnt, penalty;

    Team() = default;

    Team(const string& _name, int _solveCnt, int _penalty)
        : name(_name), solveCnt(_solveCnt), penalty(_penalty) {}

    bool operator<(const Team& t) {
        if (solveCnt != t.solveCnt)
            return solveCnt < t.solveCnt;
        return penalty > t.penalty;
    }
};

unordered_map<string, vector<Team>> teamOfUniv;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, K;
    cin >> N >> K;

    for (int i = 1; i <= N; i++) {
        string univ, name;
        int solveCnt, penalty;

        cin >> univ >> name >> solveCnt >> penalty;
        teamOfUniv[univ].emplace_back(name, solveCnt, penalty);
    }

    vector<Team> tops;
    tops.reserve(teamOfUniv.size());
    for (auto& [univ, teams] : teamOfUniv)
        tops.push_back(*max_element(teams.begin(), teams.end()));

    sort(tops.rbegin(), tops.rend());
    for (int i = 0; i < K; i++)
        cout << tops[i].name << '\n';

    return 0;
}