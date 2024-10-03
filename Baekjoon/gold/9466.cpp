#include <bits/stdc++.h>
using namespace std;

vector<bool> visited;
vector<bool> done;
vector<int> nextStu;
int cnt;


void dfs(int stu) {
    visited[stu] = true;
    if (!visited[nextStu[stu]]) {
        dfs(nextStu[stu]);
    } else if (!done[nextStu[stu]]) {
        for (int i = nextStu[stu] ; i != stu ; i = nextStu[i]) {
            cnt++;
        }
        cnt++;
    }
    done[stu] = true;
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t; cin >> t;


    while (t--) {
        int n; cin >> n;
        cnt = 0;
        visited = vector<bool>(n+1, false);
        done = vector<bool>(n+1, false);
        nextStu = vector<int>(n+1, 0);
        for (int i = 1 ; i <= n ; i++) {
            cin >> nextStu[i];
        }

        for (int i = 1 ; i <= n ; i++) {
            if (!done[i]) dfs(i);
        }
        cout << n - cnt << '\n';
    }




    return 0;
}