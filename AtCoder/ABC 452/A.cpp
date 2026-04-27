#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int M, D;
    cin >> M >> D;

    if (M == 1) {
        if (D == 7)
            println("Yes");
        else
            println("No");
        return 0;
    }

    if (M % 2 == 1 and M <= 9 and M == D)
        println("Yes");
    else
        println("No");

    return 0;
}