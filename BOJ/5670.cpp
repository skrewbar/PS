#include <bits/stdc++.h>
using namespace std;

struct TrieNode {
    bool root;
    bool end;
    map<int, TrieNode*> childs;

    TrieNode(bool root): root(root), end(false) {}

    ~TrieNode() {
        for (pair<int, TrieNode*> child : childs) {
            delete child.second;
        }
    }


    void insert(const char *str) {
        if (*str == '\0') {
            end = true;
            return;
        }

        int next = *str - 'a';
        if (childs.find(next) == childs.end()) childs[next] = new TrieNode(false);
        childs[next]->insert(str + 1);
    }


    int count(const char *str) {
        if (*str == '\0') return 0;


        int next = *str - 'a';
        if (not end and childs.size() == 1 and not root) return childs[next]->count(str + 1);
        return childs[next]->count(str + 1) + 1;
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout << fixed;
    cout.precision(2);


    int n = 1;
    while (cin >> n) {
        if (n == 0) break;
        TrieNode *trie = new TrieNode(true);
        vector<string> dict(n);
        for (int i = 0 ; i < n ; i++) {
            cin >> dict[i];
            trie->insert(dict[i].c_str());
        }

        double sum = 0;
        for (int i = 0 ; i < n ; i++) {
            sum += trie->count(dict[i].c_str());
        }

        cout << sum/dict.size() << '\n';

        delete trie;
    }


    return 0;
}