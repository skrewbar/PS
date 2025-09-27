#include <bits/stdc++.h>
using namespace std;

using ll = long long;

vector<ll> fib(93);

vector<vector<ll>> primes = {
    {},
    {},
    {},
    {2LL},
    {3LL},
    {5LL},
    {2LL, 2LL, 2LL},
    {13LL},
    {3LL, 7LL},
    {2LL, 17LL},
    {5LL, 11LL},
    {89LL},
    {2LL, 2LL, 2LL, 2LL, 3LL, 3LL},
    {233LL},
    {13LL, 29LL},
    {2LL, 5LL, 61LL},
    {3LL, 7LL, 47LL},
    {1597LL},
    {2LL, 2LL, 2LL, 17LL, 19LL},
    {37LL, 113LL},
    {3LL, 5LL, 11LL, 41LL},
    {2LL, 13LL, 421LL},
    {89LL, 199LL},
    {28657LL},
    {2LL, 2LL, 2LL, 2LL, 2LL, 3LL, 3LL, 7LL, 23LL},
    {5LL, 5LL, 3001LL},
    {233LL, 521LL},
    {2LL, 17LL, 53LL, 109LL},
    {3LL, 13LL, 29LL, 281LL},
    {514229LL},
    {2LL, 2LL, 2LL, 5LL, 11LL, 31LL, 61LL},
    {557LL, 2417LL},
    {3LL, 7LL, 47LL, 2207LL},
    {2LL, 89LL, 19801LL},
    {1597LL, 3571LL},
    {5LL, 13LL, 141961LL},
    {2LL, 2LL, 2LL, 2LL, 3LL, 3LL, 3LL, 17LL, 19LL, 107LL},
    {73LL, 149LL, 2221LL},
    {37LL, 113LL, 9349LL},
    {2LL, 233LL, 135721LL},
    {3LL, 5LL, 7LL, 11LL, 41LL, 2161LL},
    {2789LL, 59369LL},
    {2LL, 2LL, 2LL, 13LL, 29LL, 211LL, 421LL},
    {433494437LL},
    {3LL, 43LL, 89LL, 199LL, 307LL},
    {2LL, 5LL, 17LL, 61LL, 109441LL},
    {139LL, 461LL, 28657LL},
    {2971215073LL},
    {2LL, 2LL, 2LL, 2LL, 2LL, 2LL, 3LL, 3LL, 7LL, 23LL, 47LL, 1103LL},
    {13LL, 97LL, 6168709LL},
    {5LL, 5LL, 11LL, 101LL, 151LL, 3001LL},
    {2LL, 1597LL, 6376021LL},
    {3LL, 233LL, 521LL, 90481LL},
    {953LL, 55945741LL},
    {2LL, 2LL, 2LL, 17LL, 19LL, 53LL, 109LL, 5779LL},
    {5LL, 89LL, 661LL, 474541LL},
    {3LL, 7LL, 7LL, 13LL, 29LL, 281LL, 14503LL},
    {2LL, 37LL, 113LL, 797LL, 54833LL},
    {59LL, 19489LL, 514229LL},
    {353LL, 2710260697LL},
    {2LL, 2LL, 2LL, 2LL, 3LL, 3LL, 5LL, 11LL, 31LL, 41LL, 61LL, 2521LL},
    {4513LL, 555003497LL},
    {557LL, 2417LL, 3010349LL},
    {2LL, 13LL, 17LL, 421LL, 35239681LL},
    {3LL, 7LL, 47LL, 1087LL, 2207LL, 4481LL},
    {5LL, 233LL, 14736206161LL},
    {2LL, 2LL, 2LL, 89LL, 199LL, 9901LL, 19801LL},
    {269LL, 116849LL, 1429913LL},
    {3LL, 67LL, 1597LL, 3571LL, 63443LL},
    {2LL, 137LL, 829LL, 18077LL, 28657LL},
    {5LL, 11LL, 13LL, 29LL, 71LL, 911LL, 141961LL},
    {6673LL, 46165371073LL},
    {2LL, 2LL, 2LL, 2LL, 2LL, 3LL, 3LL, 3LL, 7LL, 17LL, 19LL, 23LL, 107LL,
     103681LL},
    {9375829LL, 86020717LL},
    {73LL, 149LL, 2221LL, 54018521LL},
    {2LL, 5LL, 5LL, 61LL, 3001LL, 230686501LL},
    {3LL, 37LL, 113LL, 9349LL, 29134601LL},
    {13LL, 89LL, 988681LL, 4832521LL},
    {2LL, 2LL, 2LL, 79LL, 233LL, 521LL, 859LL, 135721LL},
    {157LL, 92180471494753LL},
    {3LL, 5LL, 7LL, 11LL, 41LL, 47LL, 1601LL, 2161LL, 3041LL},
    {2LL, 17LL, 53LL, 109LL, 2269LL, 4373LL, 19441LL},
    {2789LL, 59369LL, 370248451LL},
    {99194853094755497LL},
    {2LL, 2LL, 2LL, 2LL, 3LL, 3LL, 13LL, 29LL, 83LL, 211LL, 281LL, 421LL,
     1427LL},
    {5LL, 1597LL, 9521LL, 3415914041LL},
    {6709LL, 144481LL, 433494437LL},
    {2LL, 173LL, 514229LL, 3821263937LL},
    {3LL, 7LL, 43LL, 89LL, 199LL, 263LL, 307LL, 881LL, 967LL},
    {1069LL, 1665088321800481LL},
    {2LL, 2LL, 2LL, 5LL, 11LL, 17LL, 19LL, 31LL, 61LL, 181LL, 541LL, 109441LL},
    {13LL, 13LL, 233LL, 741469LL, 159607993LL},
    {3LL, 139LL, 461LL, 4969LL, 28657LL, 275449LL}};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    fib[1] = 1;
    for (int i = 2; i < 93; i++)
        fib[i] = fib[i - 1] + fib[i - 2];

    ll lo, hi;
    cin >> hex;

    while (cin >> lo >> hi) {
        if (lo >= hi)
            break;

        println("Range {} to {}:", lo, hi);

        int s = lower_bound(fib.begin(), fib.end(), lo) - fib.begin();
        int e = upper_bound(fib.begin(), fib.end(), hi) - fib.begin();

        if (s >= e) {
            print("No Fibonacci numbers in the range\n\n");
            continue;
        }

        for (int i = s; i < e; i++) {
            print("Fib({}) = {}, ", i, fib[i]);
            if (fib[i] == 0)
                println("lg does not exist");
            else
                println("lg is {:.6f}", log2l(fib[i]));

            if (primes[i].empty()) {
                println("No prime factors");
                continue;
            }

            print("Prime factors: ");
            for (ll p : primes[i])
                print("{} ", p);
            println();
        }
        println();
    }

    return 0;
}