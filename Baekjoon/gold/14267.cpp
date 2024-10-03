#include <bits/stdc++.h>
using namespace std;

vector<vector<int>> subordinates;
vector<int> praise_amount;


void praise(int i, int w) {
    praise_amount[i] += w;

    for (int sub : subordinates[i]) {
        praise(sub, praise_amount[i]);
    }
}


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    int n, m;
    cin >> n >> m;
    subordinates.resize(n+1);
    for (int i = 1 ; i <= n ; i++) {
        int boss;
        cin >> boss;
        if (boss == -1) continue;

        subordinates[boss].push_back(i);
    }

    praise_amount.resize(n+1, 0);
    for (int i = 0 ; i < m ; i++) {
        int num, w;
        cin >> num >> w;

        praise_amount[num] += w;
    }

    praise(1, 0);

    for (int i = 1 ; i <= n ; i++) {
        cout << praise_amount[i] << ' ';
    }


    return 0;
}