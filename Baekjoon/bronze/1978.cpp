#include <iostream>
using namespace std;

bool isPrime(int n) {
    if (n == 1) return false;

    for (int i = 2 ; i < n ; i++) {
        if (n % i == 0) return false;
    }

    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, answer = 0;
    cin >> N;
    for (int i = 0 ; i < N ; i++) {
        int n;
        cin >> n;
        if (isPrime(n)) answer += 1;
    }
    cout << answer;

    return 0;
}