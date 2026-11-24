#include <iostream>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, x, y;
    cin >> n >> x >> y;
    
    cout << 4-(x==1)-(x==n)-(y==1)-(y==n);
}