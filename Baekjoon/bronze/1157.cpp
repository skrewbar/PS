#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>
using namespace std;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    unordered_map<char, int> counts;
    for (char c : "ABCDEFGHIJKLMNOPQRSTUVWXYZ") {
        counts.insert({c, 0});
    }

    string word;
    getline(cin, word);
    transform(word.begin(), word.end(), word.begin(), [](unsigned char c) { return toupper(c); });
    for (char c : word) {
        counts[c]++;
    }

    vector<pair<char, int>> v(counts.begin(), counts.end());
    sort(v.begin(), v.end(), [](pair<char, int> &a, pair<char, int> &b){ return a.second > b.second; });
    
    if (v[0].second == v[1].second) {
        cout << '?';
    } else {
        cout << v[0].first;
    }

    return 0;
}