#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<int> answerList;
    queue<int> q;
    for (int i = 1 ; i <= n ; i++) q.push(i);
    while (not q.empty()) {
        for (int i = 0 ; i < k-1 ; i++) {
            q.push(q.front());
            q.pop();
        }
        answerList.push_back(q.front());
        q.pop();
    }
    cout << '<';
    for (int i = 0 ; i < answerList.size()-1 ; i++) {
        cout << answerList[i] << ", ";
    }
    cout << answerList.back();
    cout << '>';
}