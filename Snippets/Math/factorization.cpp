#include <vector>

std::vector<int> generate_factors(const std::vector<std::pair<int, int>>& prime_factors) {
    int total_factors = 1;
    for (const auto& pf : prime_factors) total_factors *= (pf.second + 1);

    std::vector<int> factors;
    factors.reserve(total_factors);
    factors.push_back(1);

    for (const auto& pf : prime_factors) {
        int p = pf.first;
        int exponent = pf.second;
        int current_size = static_cast<int>(factors.size());
        for (int i = 0; i < exponent * current_size; ++i)
            factors.push_back(factors[factors.size() - current_size] * p);
    }

    return factors;
}
