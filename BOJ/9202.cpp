#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

constexpr int dr[] = {0, -1, -1, -1, 0, 1, 1, 1},
              dc[] = {1, 1, 0, -1, -1, -1, 0, 1},
              scoreMap[] = {0, 0, 0, 1, 1, 2, 3, 5, 11};

struct TrieNode {
    map<char, TrieNode*> child;
    bool isEnd;

    TrieNode() : isEnd(false) {}

    void insert(const char* str) {
        if (*str == '\0') {
            isEnd = true;
            return;
        }

        char nxt = *str;
        if (not child.contains(nxt))
            child[nxt] = new TrieNode();
        child[nxt]->insert(str + 1);
    }
} trie;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int w;
    cin >> w;

    for (int i = 0; i < w; i++) {
        string word;
        cin >> word;

        trie.insert(word.c_str());
    }

    int b;
    cin >> b;
    while (b--) {
        vector<string> boggle(4);
        for (int i = 0; i < 4; i++)
            cin >> boggle[i];

        vector<vector<bool>> visited(4, vector<bool>(4));
        string str;

        set<string> foundStr;

        function<void(TrieNode*, int, int)> find = [&](TrieNode* t, int r,
                                                       int c) {
            if (t->isEnd) {
                foundStr.insert(str);
            }

            for (int k = 0; k < 8; k++) {
                int nr = r + dr[k];
                int nc = c + dc[k];

                if (nr < 0 or nr >= 4 or nc < 0 or nc >= 4)
                    continue;
                if (visited[nr][nc])
                    continue;

                char nxt = boggle[nr][nc];
                if (not t->child.contains(nxt))
                    continue;

                visited[nr][nc] = true;
                str.push_back(boggle[nr][nc]);
                find(t->child[nxt], nr, nc);
                str.pop_back();
                visited[nr][nc] = false;
            }
        };

        for (int r = 0; r < 4; r++) {
            for (int c = 0; c < 4; c++) {
                if (not trie.child.contains(boggle[r][c]))
                    continue;

                visited[r][c] = true;
                str.push_back(boggle[r][c]);
                find(trie.child[boggle[r][c]], r, c);
                str.pop_back();
                visited[r][c] = false;
            }
        }

        string longest;
        int score = 0;
        for (const string& s : foundStr) {
            if (s.length() > longest.length() or
                (s.length() == longest.length() and s < longest)) {
                longest = s;
            }

            score += scoreMap[s.size()];
        }

        println("{} {} {}", score, longest, foundStr.size());
    }

    return 0;
}