#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) (void(0))
#endif

using namespace std;
using ll = long long;

enum Operator : uint8_t {
    ADD,
    SUB,
    MUL,
    DIV,
    POWER,
    OPEN_BRACKET,
    CLOSE_BRACKET,
    SQRT,
    INPUT,
};

map<char, Operator> operatorMap = {
    {'+', ADD},           {'-', SUB},   {'*', MUL},
    {'/', DIV},           {'^', POWER}, {'(', OPEN_BRACKET},
    {')', CLOSE_BRACKET}, {'#', SQRT},  {'=', INPUT},
};
map<Operator, int> priority = {
    {ADD, 0},    {SUB, 0},  {MUL, 1},          {DIV, 1},
    {POWER, 2},  {SQRT, 3}, {OPEN_BRACKET, 4}, {CLOSE_BRACKET, -1},
    {INPUT, -1},
};
set<Operator> rTol = {SQRT, POWER};

ll power(ll base, ll exp) {
    ll res = 1;
    while (exp) {
        if (exp & 1)
            res *= base;
        base *= base;
        exp >>= 1;
    }
    return res;
}

stack<ll> clauses;
stack<Operator> operators;

ll calculate(ll left, Operator op, ll right) {
    switch (op) {
        case ADD:
            return left + right;
        case SUB:
            return left - right;
        case MUL:
            return left * right;
        case DIV:
            return left / right;
        case POWER:
            return power(left, right);
        default:
            ASSERT(false);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string expression;
    cin >> expression;

    int n = expression.size();

    for (int i = 0; i < n; i++) {
        if ('0' <= expression[i] and expression[i] <= '9') {
            ll num = 0;
            while ('0' <= expression[i] and expression[i] <= '9') {
                num *= 10;
                num += expression[i] - '0';
                i++;
            }

            clauses.push(num);
        }

        Operator op = operatorMap[expression[i]];
        while (not operators.empty() and operators.top() != OPEN_BRACKET) {
            if (rTol.contains(op)) {
                if (priority[operators.top()] <= priority[op])
                    break;
            } else if (priority[operators.top()] < priority[op])
                break;

            if (operators.top() == SQRT) {
                operators.pop();

                ll num = clauses.top();
                clauses.pop();
                clauses.push(floor(sqrtl(num)));
            } else {
                ll right = clauses.top();
                clauses.pop();
                ll left = clauses.top();
                clauses.pop();

                clauses.push(calculate(left, operators.top(), right));
                operators.pop();
            }
        }

        if (op == CLOSE_BRACKET) {
            ASSERT(operators.top() == OPEN_BRACKET);
            operators.pop();
        } else
            operators.push(op);
    }
    ASSERT(clauses.size() == 1);
    ASSERT(operators.size() == 1 and operators.top() == INPUT);

    print("{}", clauses.top());

    return 0;
}