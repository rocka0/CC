// https://github.com/the-hyp0cr1t3/CC

const int nax = 2e7;
array<int, nax + 1> spf;
vi primes;

void initSieve()
{
    iota(all(spf), 0);
    // There are 1270607 primes less than 2e7
    primes.reserve(1270607);
    primes.pb(2);
    for (int i = 4; i <= nax; i += 2) {
        spf[i] = 2;
    }
    for (int i = 3; i * i <= nax; i += 2) {
        if (spf[i] == i) {
            int inc = 2 * i;
            for (int j = i * i; j <= nax; j += inc) {
                if (spf[j] == j) {
                    spf[j] = i;
                }
            }
        }
    }
    for (int i = 3; i <= nax; i += 2) {
        if (spf[i] == i) {
            primes.pb(i);
        }
    }
}