#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n; cin >> n;
    vector<int> compressed_coord;
    for (int i = 0 ; i < n ; i++) {
        int x; cin >> x;
        compressed_coord.push_back(x);
    }
    vector<int> coord(compressed_coord);
    sort(compressed_coord.begin(), compressed_coord.end());
    compressed_coord.erase(unique(compressed_coord.begin(), compressed_coord.end()), compressed_coord.end());

    for (int i = 0 ; i < n ; i++) {
        cout << lower_bound(compressed_coord.begin(), compressed_coord.end(), coord[i]) - compressed_coord.begin() << " ";
    }

    return 0;
}