#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

int strToInt(string s) {
    int ret = 0;
    for (int i = 1; i < (int)s.size(); i++)
        ret = ret * 10 + s[i] - '0';
    return ret;
}

vector<int> matching;
vector<bool> matched;
vector<vector<int>> matchingList;

bool canBeMatched(int cat) {
    for (int dog : matchingList[cat]) {
        if (matched[dog])
            continue;
        matched[dog] = true;

        if (matching[dog] == -1 or canBeMatched(matching[dog])) {
            matching[dog] = cat;
            return true;
        }
    }
    return false;
}

struct Vote {
    bool preferCat;
    int up, down;
};

void solve() {
    int c, d, v;
    cin >> c >> d >> v;

    vector<Vote> catVotes;
    vector<Vote> dogVotes;

    for (int i = 0; i < v; i++) {
        string up, down;
        cin >> up >> down;
        Vote vote;

        vote.preferCat = (up[0] == 'C');
        vote.up = strToInt(up);
        vote.down = strToInt(down);
        if (vote.preferCat)
            catVotes.push_back(vote);
        else
            dogVotes.push_back(vote);
    }

    matching = vector(dogVotes.size(), -1);
    matched = vector(dogVotes.size(), false);
    matchingList = vector(catVotes.size(), vector<int>());

    for (int i = 0; i < (int)catVotes.size(); i++) {
        Vote catVote = catVotes[i];
        for (int j = 0; j < (int)dogVotes.size(); j++) {
            Vote dogVote = dogVotes[j];
            if (catVote.up == dogVote.down or catVote.down == dogVote.up) {
                matchingList[i].push_back(j);
            }
        }
    }

    int answer = v;
    for (int i = 0; i < (int)catVotes.size(); i++) {
        ranges::fill(matched, false);
        if (canBeMatched(i))
            answer--;
    }

    cout << answer << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--)
        solve();
}