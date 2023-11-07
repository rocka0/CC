#include <array>
#include <numeric>
#include <vector>

/*
    Source: https://github.com/the-hyp0cr1t3/CC
    Usage:  Call buildSieve() in main
*/

constexpr int sieveLimit = 2e7;
std::array<int, sieveLimit + 1> spf;
std::vector<int> primes;

void buildSieve() {
    std::iota(spf.begin(), spf.end(), 0);
    // There are 1270607 primes less than 2e7
    primes.reserve(1270607);
    primes.push_back(2);
    for (int i = 4; i <= sieveLimit; i += 2) {
        spf[i] = 2;
    }
    for (int i = 3; i * i <= sieveLimit; i += 2) {
        if (spf[i] == i) {
            int inc = 2 * i;
            for (int j = i * i; j <= sieveLimit; j += inc) {
                if (spf[j] == j) {
                    spf[j] = i;
                }
            }
        }
    }
    for (int i = 3; i <= sieveLimit; i += 2) {
        if (spf[i] == i) {
            primes.push_back(i);
        }
    }
}
