#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

struct TrieNode {
    map<char, TrieNode*> child;
    TrieNode* fail;
    bool end;

    TrieNode() : end(false) {}

    ~TrieNode() {
        for (auto& [_, ptr] : child)
            delete ptr;
    }

    void insert(const char* str) {
        if (*str == '\0') {
            end = true;
            return;
        }

        char next = *str;
        if (not child.contains(next))
            child[next] = new TrieNode();
        child[next]->insert(str + 1);
    }
};

struct Trie {
    TrieNode* root;

    Trie() { root = new TrieNode(); }
    ~Trie() { delete root; }

    void insert(const string& str) { root->insert(str.c_str()); }

    void setupFail() {
        root->fail = root;
        queue<TrieNode*> q;

        for (auto& [_, node] : root->child) {
            node->fail = root;
            q.push(node);
        }

        while (not q.empty()) {
            TrieNode* now = q.front();
            q.pop();

            for (auto& [chr, next] : now->child) {
                TrieNode*& fail = next->fail;
                fail = now->fail;

                while (fail != root and not fail->child.contains(chr))
                    fail = fail->fail;
                if (fail->child.contains(chr))
                    fail = fail->child[chr];

                if (fail->end)
                    next->end = true;

                q.push(next);
            }
        }
    }

    int eraseEmoticons(string& s) {
        int ret = 0;
        TrieNode* now = root;

        for (int i = 0; i < (int)s.size(); i++) {
            while (now != root and not now->child.contains(s[i]))
                now = now->fail;
            if (now->child.contains(s[i]))
                now = now->child[s[i]];

            if (now->end) {
                ret++;
                now = root;
            }
        }

        return ret;
    }
};

void solve(int n, int m) {
    Trie trie;

    for (int i = 0; i < n; i++) {
        string emoticon;
        cin >> emoticon;
        trie.insert(emoticon);
    }
    trie.setupFail();

    cin.ignore();
    int answer = 0;
    for (int i = 0; i < m; i++) {
        string text;
        getline(cin, text);
        answer += trie.eraseEmoticons(text);
    }

    print("{}\n", answer);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    for (cin >> n >> m; n != 0; cin >> n >> m)
        solve(n, m);

    return 0;
}