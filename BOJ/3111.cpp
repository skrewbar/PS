#include <bits/stdc++.h>
#ifndef ONLINE_JUDGE
#define ASSERT(x) assert(x)
#else
#define ASSERT(ignore) ((void)0)
#endif

using namespace std;

bool isStrOnTop(stack<char>& stk, const string& s) {
    if (stk.size() < s.size())
        return false;

    string temp;
    for (int i = 0; i < (int)s.size(); i++) {
        temp.push_back(stk.top());
        stk.pop();
    }
    reverse(temp.begin(), temp.end());
    for (char c : temp)
        stk.push(c);

    return temp == s;
}

bool isStrOnBack(string& target, const string& pattern) {
    if (target.size() < pattern.size())
        return false;

    for (int i = 0; i < (int)pattern.size(); i++) {
        if (target[target.size() - i - 1] != pattern[pattern.size() - i - 1])
            return false;
    }
    return true;
}

void popMultiple(stack<char>& stk, int cnt) {
    ASSERT(cnt >= 0);

    while (cnt--)
        stk.pop();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string a, t;
    cin >> a >> t;

    string rev_a(a);
    reverse(rev_a.begin(), rev_a.end());

    deque<char> tdq;
    for (auto c : t)
        tdq.push_back(c);

    stack<char> front, back;

    while (true) {
        bool find = false;

        while (not tdq.empty() and not find) {
            front.push(tdq.front());
            tdq.pop_front();

            if (isStrOnTop(front, a)) {
                popMultiple(front, a.size());
                find = true;
            }
        }
        if (not find)
            break;

        find = false;
        while (not tdq.empty() and not find) {
            back.push(tdq.back());
            tdq.pop_back();

            if (isStrOnTop(back, rev_a)) {
                popMultiple(back, a.size());
                find = true;
            }
        }

        if (not find or tdq.empty())
            break;
    }

    string merged;
    while (not front.empty()) {
        merged.push_back(front.top());
        front.pop();
    }
    reverse(merged.begin(), merged.end());

    while (not back.empty()) {
        merged.push_back(back.top());
        back.pop();
        if (isStrOnBack(merged, a)) {
            int c = a.size();
            while (c--)
                merged.pop_back();
        }
    }

    print("{}", merged);

    return 0;
}