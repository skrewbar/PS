#include <bits/stdc++.h>
using namespace std;

vector<bool> matched;
vector<int> matching;
vector<vector<int>> matchList;

/**
 * @param odd 홀수
 * @return 매칭에 성공하면 true, 실패하면 false
 */
bool match(int odd) {
    for (int even : matchList[odd]) {
        if (matched[even])
            continue;
        matched[even] = true;
        if (matching[even] == -1 or match(matching[even])) {
            matching[even] = odd;
            return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> odds, evens;

    int firstNum;
    cin >> firstNum;
    firstNum & 1 ? odds.push_back(firstNum) : evens.push_back(firstNum);
    for (int i = 1; i < n; i++) {
        int num;
        cin >> num;
        num & 1 ? odds.push_back(num) : evens.push_back(num);
    }

    if (~firstNum & 1)  // 편의상 firstNum이 홀수라고 생각하기
        swap(odds, evens);

    // 2000까지 소수 구하기
    vector<bool> isPrime(2001, true);
    isPrime[1] = false;
    for (int i = 2; i < isPrime.size(); i++) {
        if (not isPrime[i])
            continue;
        for (int j = i + i; j < isPrime.size(); j += i)
            isPrime[j] = false;
    }

    // odds를 evens에 매칭: matching[even] = odd
    matched = vector(1001, false);
    matching = vector(1001, -1);
    matchList = vector(1001, vector<int>());
    for (int odd : odds) {
        for (int even : evens) {
            if (isPrime[odd + even])
                matchList[odd].push_back(even);
        }
    }

    vector<int> answer;
    for (int even : matchList[firstNum]) {
        ranges::fill(matched, false);
        ranges::fill(matching, -1);

        int matchingCnt = 1;
        for (int j = 1; j < odds.size(); j++) {
            ranges::fill(matched, false);
            matched[even] = true;

            matchingCnt += match(odds[j]);
        }
        if (matchingCnt == n >> 1)
            answer.push_back(even);
    }

    ranges::sort(answer);
    for (int num : answer)
        cout << num << ' ';

    if (answer.empty())
        cout << -1;
}