#include <array>
#include <numeric>

constexpr int SIEVE_LIMIT = 2e7;
std::array<int, SIEVE_LIMIT + 1> spf;

void setup_sieve() {
    std::iota(spf.begin(), spf.end(), 0);

    for (int i = 4; i <= SIEVE_LIMIT; i += 2) spf[i] = 2;

    for (int i = 3; i * i <= SIEVE_LIMIT; i += 2)
        if (spf[i] == i)
            for (int j = i * i; j <= SIEVE_LIMIT; j += 2 * i)
                if (spf[j] == j) spf[j] = i;
}
