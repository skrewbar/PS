#include <bits/stdc++.h>
using namespace std;

vector<int> bukkits[317];
vector<int> arr;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    int n;
    cin >> n;

    int size = (int)sqrt(n);

    arr.reserve(n);
    for (int i = 0 ; i < n ; i++) {
        int a;
        cin >> a;

        arr.push_back(a);
        bukkits[i / size].push_back(a);
    }

    for (int i = 0 ; i < 317 ; i++) {
        sort(bukkits[i].begin(), bukkits[i].end());
    }

    
    int m;
    cin >> m;
    while (m--) {
        int q;
        cin >> q;

        if (q == 1) {
            int i, v;
            cin >> i >> v;
            i--;

            int group = i / size;
            bukkits[group].erase(lower_bound(bukkits[group].begin(), bukkits[group].end(), arr[i]));
            bukkits[group].insert(lower_bound(bukkits[group].begin(), bukkits[group].end(), v), v);
            arr[i] = v;
        } else {
            int l, r, k;
            cin >> l >> r >> k;
            l--; r--;

            int lGroup = l / size;
            int rGroup = r / size;

            int ans = 0;

            if (lGroup == rGroup) {
                auto start = next(bukkits[lGroup].begin(), l % size);
                auto end = next(bukkits[lGroup].begin(), r % size + 1);
                ans += end - upper_bound(start, end, k);
            } else {
                for (int i = l ; i < (lGroup+1) * size ; i++) {
                    if (k < arr[i]) ans++;
                }
                for (int i = rGroup*size ; i <= r ; i++) {
                    if (k < arr[i]) ans++;
                }
                for (int group = lGroup+1 ; group < rGroup ; group++) {
                    ans += bukkits[group].end() - upper_bound(bukkits[group].begin(), bukkits[group].end(), k);
                }
            }

            cout << ans << '\n';
        }
    }


    return 0;
}