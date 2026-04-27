#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int H, W;
    cin >> H >> W;

    for (int i = 0; i < W; i++)
        cout << '#';
    cout << '\n';
    for (int i = 1; i < H - 1; i++) {
        cout << '#';
        
        for (int j = 1; j < W - 1; j++)
            cout << '.';

        cout << "#\n";
    }
    for (int i = 0; i < W; i++)
        cout << '#';
    cout << '\n';

    return 0;
}