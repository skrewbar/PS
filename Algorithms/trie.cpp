#include <bits/stdc++.h>

struct TrieNode {
    bool end;
    TrieNode *childs[26];

    TrieNode() {
        end = false;
        for (int i = 0 ; i < 26 ; i++) childs[i] = nullptr;
    }


    void insert(char *str) {
        if (*str == '\0') {
            end = true;
            return;
        }

        int cur = *str - 'A';
        if (childs[cur] == nullptr) childs[cur] = new TrieNode();
        childs[cur]->insert(str + 1);
    }


    bool find(char *str) {
        if (*str == '\0') {
            if (end) return true;
            else return false;
        }

        int cur = *str - 'A';
        if (childs[cur] == nullptr) return false;
        else return childs[cur]->find(str + 1);
    }
};


int main() {
    return 0;
}