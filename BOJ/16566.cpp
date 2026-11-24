#include <bits/stdc++.h>
using namespace std;
int n, m, k;
int instead[4000001], cards[4000001];

int find(int n) {
    if (n == instead[n]) return n;
    return instead[n] = find(instead[n]);
}

void _union(int u, int v){
    // v = u + 1
    u = find(u), v = find(v);
    if( u == v )
        return ;
    instead[u] = v;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k;

    for (int i = 0 ; i < m ; i++) {
        cin >> cards[i];
        instead[i] = i;
    }
    sort(cards, cards + m);

    while (k--) {
        int card;
        cin >> card;

        int upper = find(upper_bound(cards, cards + m, card) - cards);
        cout << cards[upper] << '\n';
        instead[upper] = find(upper+1);
    }

    return 0;
}