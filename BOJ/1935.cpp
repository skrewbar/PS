#include <bits/stdc++.h>
using namespace std;


int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    string expression;
    cin >> expression;

    vector<double> values(n);
    for (int i = 0; i < n; i++) cin >> values[i];

    stack<double> s;
    for (int i = 0; i < expression.size(); i++) {
        if ('A' <= expression[i] and expression[i] <= 'Z') {
            s.push(values[expression[i]-'A']);
            continue;
        }

        double b = s.top(); s.pop();
        double a = s.top(); s.pop();

        switch (expression[i]) {
            case '+':
                s.push(a + b);
                break;
            case '-':
                s.push(a - b);
                break;
            case '/':
                s.push(a / b);
                break;
            case '*':
                s.push(a * b);
                break;
        }
    }

    cout << fixed;
    cout.precision(2);
    cout << s.top();


    return 0;
}