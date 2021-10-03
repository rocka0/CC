#include <bits/stdc++.h>
using namespace std;

/*
    Source: https://github.com/the-hyp0cr1t3/CC/

    Usage:  vector<int> facs = generateFactors(pf_vector);

    Note:   For long, change FACTORS_MAX to 161280 and use int64_t instead of int32_t
*/

const int FACTORS_MAX = 2304;

vector<int32_t> generateFactors(const vector<pair<int32_t, int>>& prime_factors, bool sorted = false) {
    static int32_t buffer[FACTORS_MAX];
    int product = 1;
    for (auto& pf : prime_factors) {
        product *= pf.second;
    }
    vector<int32_t> factors = {1};
    factors.reserve(product);
    for (auto& pf : prime_factors) {
        int32_t p = pf.first;
        int exponent = pf.second;
        int before_size = static_cast<int>(factors.size());
        for (int i = 0; i < exponent * before_size; i++) {
            factors.push_back(factors[factors.size() - before_size] * p);
        }
        if (sorted && factors[before_size - 1] > p) {
            for (int section = before_size; section < static_cast<int>(factors.size()); section *= 2) {
                for (int i = 0; i + section < static_cast<int>(factors.size()); i += 2 * section) {
                    int length = min(2 * section, static_cast<int>(factors.size()) - i);
                    merge(factors.begin() + i, factors.begin() + i + section, factors.begin() + i + section, factors.begin() + i + length, buffer);
                    copy(buffer, buffer + length, factors.begin() + i);
                }
            }
        }
    }
    return factors;
}
