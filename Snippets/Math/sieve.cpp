#include <array>
#include <numeric>
#include <vector>

/*
    Source: https://github.com/the-hyp0cr1t3/CC
    Usage:  Call setup_sieve() in main
*/

constexpr int MAX_PRIME_LIMIT = 2e7;
// There are 1270607 primes less than 2e7
constexpr int TOTAL_PRIME_COUNT = 1270607;
std::array<int, MAX_PRIME_LIMIT + 1> spf;
std::vector<int> primes;

void setup_sieve() {
    std::iota(spf.begin(), spf.end(), 0);
    primes.reserve(TOTAL_PRIME_COUNT);
    primes.push_back(2);
    for (int i = 4; i <= MAX_PRIME_LIMIT; i += 2)
        spf[i] = 2;
    for (int i = 3; i * i <= MAX_PRIME_LIMIT; i += 2) {
        if (spf[i] == i) {
            int inc = 2 * i;
            for (int j = i * i; j <= MAX_PRIME_LIMIT; j += inc) {
                if (spf[j] == j)
                    spf[j] = i;
            }
        }
    }
    for (int i = 3; i <= MAX_PRIME_LIMIT; i += 2)
        if (spf[i] == i)
            primes.push_back(i);
}
