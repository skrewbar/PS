#include <bits/stdc++.h>
using namespace std;
using ll = long long;

class Picture {
public:
    ll x1, y1, x2, y2;
};

template <typename T>
void compress(vector<T> &values) {
    sort(values.begin(), values.end());
    values.erase(unique(values.begin(), values.end()), values.end());
}


int main() {
    int t;
    cin >> t;

    while (t--) {
        int n;
        cin >> n;

        vector<Picture> pictures;
        vector<ll> unqx;
        vector<ll> unqy;
        while (n--) {
            ll x1, y1, x2, y2;
            cin >> x1 >> y1 >> x2 >> y2;
            pictures.push_back({x1, y1, x2, y2});

            unqx.push_back(x1);
            unqx.push_back(x2);
            unqy.push_back(y1);
            unqy.push_back(y2);
        }

        compress(unqx);
        compress(unqy);

        vector<vector<ll>> earth(unqx.size(), vector<ll>(unqy.size()));
        for (auto [x1, y1, x2, y2] : pictures) {
            x1 = lower_bound(unqx.begin(), unqx.end(), x1) - unqx.begin();
            x2 = lower_bound(unqx.begin(), unqx.end(), x2) - unqx.begin() - 1;
            y1 = lower_bound(unqy.begin(), unqy.end(), y1) - unqy.begin();
            y2 = lower_bound(unqy.begin(), unqy.end(), y2) - unqy.begin() - 1;

            earth[x1][y1]++;
            earth[x1][y2+1]--;
            earth[x2+1][y1]--;
            earth[x2+1][y2+1]++;
        }

        for (int x = 0; x < unqx.size()-1; x++) {
            for (int y = 0; y < unqy.size()-1; y++) {
                earth[x][y+1] += earth[x][y];
            }
        }
        for (int x = 0; x < unqx.size()-1; x++) {
            for (int y = 0; y < unqy.size()-1; y++) {
                earth[x+1][y] += earth[x][y];
            }
        }

        ll ans = 0;
        for (int x = 0; x < unqx.size()-1; x++) {
            for (int y = 0; y < unqy.size()-1; y++) {
                if (earth[x][y]) {
                    ans += (unqx[x+1] - unqx[x]) * (unqy[y+1] - unqy[y]);
                }
            }
        }
        cout << ans << '\n';
    }
}