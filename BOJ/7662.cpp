#include <bits/stdc++.h>
using namespace std;
using MinHeap = priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>>;
using MaxHeap = priority_queue<pair<int, int>, vector<pair<int, int>>, less<pair<int, int>>>;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    int t; cin >> t;
    while (t--) {
        int k; cin >> k;

        MinHeap minHeap;
        MaxHeap maxHeap;
        vector<bool> isDeleted(k, false);


        while (k--) {
            string cmd;
            cin >> cmd;

            if (cmd == "I") {
                int num; cin >> num;
                pair<int, int> temp = {num, k};
                maxHeap.push(temp);
                minHeap.push(temp);
            } else if (cmd == "D") {
                int type; cin >> type;
                if (type == 1) {
                    while (not maxHeap.empty() and isDeleted[maxHeap.top().second]) maxHeap.pop();
                    if (maxHeap.empty()) continue;

                    isDeleted[maxHeap.top().second] = true;
                    maxHeap.pop();

                } else {
                    while (not minHeap.empty() and isDeleted[minHeap.top().second]) minHeap.pop();
                    if (minHeap.empty()) continue;

                    isDeleted[minHeap.top().second] = true;
                    minHeap.pop();
                }
            }
        }

        while (not maxHeap.empty() and isDeleted[maxHeap.top().second]) maxHeap.pop();
        while (not minHeap.empty() and isDeleted[minHeap.top().second]) minHeap.pop();

        if (maxHeap.empty()) cout << "EMPTY\n";
        else {
            cout << maxHeap.top().first << ' ' << minHeap.top().first << '\n';
        }
    }


    return 0;
}