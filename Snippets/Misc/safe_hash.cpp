#include <chrono>
#include <cstddef>
#include <cstdint>
#include <utility>

struct safe_hash {
    static inline const uint64_t FIXED_RANDOM = std::chrono::steady_clock::now().time_since_epoch().count();

    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    template <typename T>
    size_t operator()(T x) const { return splitmix64(static_cast<uint64_t>(x) + FIXED_RANDOM); }

    template <typename T1, typename T2>
    size_t operator()(const std::pair<T1, T2>& p) const {
        return splitmix64(0x9e3779b97f4a7c15ULL * p.first + 0xbf58476d1ce4e5b9ULL * p.second + FIXED_RANDOM);
    }
};
