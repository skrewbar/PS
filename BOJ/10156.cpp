#include <iostream>
using namespace std;

int main() {
    int K, N, M;
    cin >> K >> N >> M;
    cout << max(K*N-M, 0);
}