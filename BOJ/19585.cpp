#include <bits/stdc++.h>
using namespace std;


struct TrieNode {
    bool end;
    map<int, TrieNode*> childs;
    // TrieNode *childs[26];

    TrieNode() {
        end = false;
    }


    void insert(const char *str) {
        if (*str == '\0') {
            end = true;
            return;
        }

        int cur = *str - 'a';
        if (childs.find(cur) == childs.end()) childs[cur] = new TrieNode();
        childs[cur]->insert(str + 1);
    }


    void find(const char *str, vector<int> &ends, int index, bool reversed) {
        if (*str == '\0') return;
        if (end) ends[index]++;

        int cur = *str - 'a';
        if (childs.find(cur) == childs.end()) return;
        childs[cur]->find(str + 1, ends, reversed ? index-1 : index+1, reversed);
    }
};


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    TrieNode *colorTrie = new TrieNode();
    TrieNode *nicknameTrie = new TrieNode();

    int c, n;
    cin >> c >> n;
    
    for (int i = 0 ; i < c ; i++) {
        string color;
        cin >> color;

        colorTrie->insert(color.c_str());
    }

    for (int i = 0 ; i < n ; i++) {
        string nickname;
        cin >> nickname;
        reverse(nickname.begin(), nickname.end());

        nicknameTrie->insert(nickname.c_str());
    }


    int q;
    cin >> q;
    while (q--) {
        string teamName;
        cin >> teamName;

        bool canWin = false;
        vector<int> ends(2001, 0);


        colorTrie->find(teamName.c_str(), ends, 0, false);
        reverse(teamName.begin(), teamName.end());
        nicknameTrie->find(teamName.c_str(), ends, teamName.size(), true);
        // ends에 기록될 곳을 오른쪽으로 한칸 당김


        for (int i = 0 ; i < teamName.size() ; i++) {
            if (ends[i] == 2) {
                canWin = true;
                break;
            }
        }


        if (canWin) cout << "Yes\n";
        else cout << "No\n";
    }


    return 0;
}