#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

constexpr int MOD = 1e9 + 9;

int nodeCnt = 0;

struct TrieNode;
vector<TrieNode*> nodes;

struct TrieNode {
    TrieNode *child[26], *fail;
    int matchMask;
    int id;

    TrieNode() : matchMask(0) {
        id = nodeCnt++;
        nodes.push_back(this);
        fill(child, child + 26, nullptr);
    }

    void insert(const char* str, int index) {
        if (*str == '\0') {
            matchMask |= (1 << index);
            return;
        }

        int next = *str - 'a';
        if (child[next] == nullptr)
            child[next] = new TrieNode();
        child[next]->insert(str + 1, index);
    }
};

struct Trie {
    TrieNode* root;

    Trie() { root = new TrieNode(); }

    void insert(const string& s, int index) { root->insert(s.c_str(), index); }

    void setupFail() {
        queue<TrieNode*> q;
        root->fail = root;
        for (int i = 0; i < 26; i++) {
            TrieNode* next = root->child[i];
            if (next == nullptr)
                continue;

            next->fail = root;
            q.push(next);
        }

        while (not q.empty()) {
            TrieNode* now = q.front();
            q.pop();

            for (int i = 0; i < 26; i++) {
                TrieNode* next = now->child[i];
                if (next == nullptr)
                    continue;

                TrieNode*& fail = next->fail;
                fail = now->fail;

                while (fail != root and fail->child[i] == nullptr)
                    fail = fail->fail;
                if (fail->child[i] != nullptr)
                    fail = fail->child[i];

                next->matchMask |= fail->matchMask;

                q.push(next);
            }
        }
    }
};

int getOneBitCount(int bits) {
    int answer = 0;
    for (int i = 0; i < 31; i++)
        if (bits & (1 << i))
            answer++;
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, c, l;
    cin >> n >> c >> l;

    Trie trie;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        trie.insert(s.c_str(), i);
    }

    trie.setupFail();

    vector<vector<vector<int>>> dp(l + 1, vector(nodeCnt, vector(1 << n, 0)));
    dp[0][trie.root->id][0] = 1;
    for (int i = 0; i < l; i++) {
        for (int j = 0; j < nodeCnt; j++) {
            for (int k = 0; k < (1 << n); k++) {
                if (dp[i][j][k] == 0)
                    continue;

                for (int x = 0; x < 26; x++) {
                    TrieNode* now = nodes[j];
                    while (now != trie.root and now->child[x] == nullptr)
                        now = now->fail;
                    if (now->child[x] != nullptr)
                        now = now->child[x];

                    int next_j = now->id;
                    int next_mask = k | now->matchMask;

                    dp[i + 1][next_j][next_mask] += dp[i][j][k];
                    dp[i + 1][next_j][next_mask] %= MOD;
                }
            }
        }
    }

    int answer = 0;
    for (int j = 0; j < nodeCnt; j++) {
        for (int k = 0; k < (1 << n); k++) {
            if (getOneBitCount(k) != c)
                continue;
            answer += dp[l][j][k];
            answer %= MOD;
        }
    }

    print("{}", answer);
    return 0;
}