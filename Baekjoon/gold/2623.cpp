#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<vector<int>> next_singers;
vector<int> indegree;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    cin >> n >> m;
    next_singers.resize(n+1);
    indegree.resize(n+1, 0);
    for (int i = 0 ; i < m ; i++) {
        int singer_count;
        cin >> singer_count;
        
        int singer1;
        cin >> singer1;
        singer_count--;

        while (singer_count--) {
            int singer2;
            cin >> singer2;

            next_singers[singer1].push_back(singer2);
            indegree[singer2]++;
            singer1 = singer2;
        }
    }

    queue<int> q;
    vector<int> ans;
    for (int singer = 1 ; singer <= n ; singer++) {
        if (indegree[singer] == 0) {
            q.push(singer);
        }
    }

    while (not q.empty()) {
        int singer = q.front();
        ans.push_back(q.front());
        q.pop();

        for (int next_singer : next_singers[singer]) {
            indegree[next_singer]--;

            if (indegree[next_singer] == 0) {
                q.push(next_singer);
            }
        }
    }

    if (ans.size() != n) {
        cout << 0;
    } else {
        for (int i = 0 ; i < n ; i++) {
            cout << ans[i] << '\n';
        }
    }

    return 0;
}