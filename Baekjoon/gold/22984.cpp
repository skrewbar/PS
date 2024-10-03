#include <bits/stdc++.h>
using namespace std;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);


    int n;
    cin >> n;
    vector<double> p;
    p.reserve(n+2);
    double e = 0;
    p.push_back(0);
    for (int i = 1 ; i <= n ; i++) {
        double p_i;
        cin >> p_i;
        p.push_back(p_i);
    }
    p.push_back(0);

    for (int i = 1 ; i <= n ; i++) {
        e += p[i] + (1-p[i])*(p[i-1] + p[i+1]);
    }

    cout << fixed;
    cout.precision(8);
    cout << e;


    return 0;
}