#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif
using namespace std;

struct Trie {
    struct TrieNode {
        map<char, TrieNode*> childs;
        bool isEnd, canDelete;

        TrieNode() : childs(), isEnd(false), canDelete(true) {}
        ~TrieNode() {
            for (auto& [_, ptr] : childs)
                delete ptr;
        }

        void insert(const char* str) {
            if (*str == '\0') {
                isEnd = true;
                return;
            }

            char c = *str;
            if (not childs.contains(c))
                childs[c] = new TrieNode();
            childs[c]->insert(str + 1);
        }

        void preventErase(const char* str) {
            canDelete = false;

            char c = *str;
            if (childs.contains(c))
                childs[c]->preventErase(str + 1);
        }

        int getEraseCount() {
            if (canDelete)
                return 1;

            int ret = (isEnd ? 1 : 0);
            for (auto& [_, child] : childs)
                ret += child->getEraseCount();
            return ret;
        }
    };

    TrieNode* root;

    Trie() { root = new TrieNode(); }
    ~Trie() { delete root; }

    void insert(const string& s) { root->insert(s.c_str()); }
    void preventErase(const string& s) { root->preventErase(s.c_str()); }

    int getEraseCount() { return root->getEraseCount(); }
};

void solve() {
    Trie* trie = new Trie();

    int N1;
    cin >> N1;

    while (N1--) {
        string s;
        cin >> s;
        trie->insert(s);
    }

    int N2;
    cin >> N2;

    while (N2--) {
        string s;
        cin >> s;
        trie->preventErase(s);
    }

    cout << trie->getEraseCount() << '\n';

    delete trie;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--)
        solve();

    return 0;
}