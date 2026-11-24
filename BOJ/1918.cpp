#include <bits/stdc++.h>
using namespace std;


int main() {
    string expression;
    cin >> expression;

    map<char, int> priority = { {'(', 3}, {'*', 2}, {'/', 2}, {'+', 1}, {'-', 1} };

    stack<char> s;

    for (int i = 0; i < expression.size(); i++) {
        if ('A' <= expression[i] and expression[i] <= 'Z') {
            cout << expression[i];
            continue;
        }

        if (expression[i] == ')') {
            while (s.top() != '(') {
                cout << s.top();
                s.pop();
            }
            s.pop();
            continue;
        }

        while (not s.empty() and priority[s.top()] >= priority[expression[i]] and s.top() != '(') {
            cout << s.top();
            s.pop();
        }

        s.push(expression[i]);
    }

    while (not s.empty()) {
        cout << s.top();
        s.pop();
    }

    return 0;
}