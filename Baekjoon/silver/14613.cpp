#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cout.precision(8);
    cout << fixed;

    double w, l, d;
    cin >> w >> l >> d;

    vector<vector<double>> prob(3500, vector<double>(21));
    prob[2000][0] = 1;
    for (int k = 0; k < 20; k++) {
        for (int i = 1000; i <= 3000; i += 50) {
            prob[i + 50][k + 1] += prob[i][k] * w;
            prob[i - 50][k + 1] += prob[i][k] * l;
            prob[i][k + 1] += prob[i][k] * d;
        }
    }

    vector<double> answers(5);
    for (int i = 0; i < 5; i++) {
        int lb = 500 * (i + 2);
        for (int j = lb; j < lb + 500; j += 50)
            answers[i] += prob[j][20];
    }

    for (double p : answers)
        cout << p << '\n';
}