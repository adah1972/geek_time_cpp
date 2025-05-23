#include "primes.h"   // extern declarations of primes_data and primes_size
#include <algorithm>  // std::copy
#include <array>      // std::array
#include <vector>     // std::vector
#include <stddef.h>   // size_t

using std::array;
using std::copy;
using std::vector;

constexpr vector<int> sieve_prime(int n)
{
    // vector<bool> is actually slower in compile-time computation
    vector<char> sieve(n + 1, true);
    for (int p = 2; p * p <= n; p++) {
        if (sieve[p]) {
            for (int i = p * p; i <= n; i += p) {
                sieve[i] = false;
            }
        }
    }
    vector<int> result;
    for (int p = 2; p <= n; p++) {
        if (sieve[p]) {
            result.push_back(p);
        }
    }
    return result;
}

constexpr size_t prime_count(int n)
{
    return sieve_prime(n).size();
}

template <int N>
constexpr auto get_prime_array()
{
    array<int, prime_count(N)> result{};
    // sieve_prime is called twice, as the resulting vector
    // cannot be stored, or be used at run time
    auto primes = sieve_prime(N);
    copy(primes.begin(), primes.end(), result.data());
    return result;
}

constinit auto primes = get_prime_array<1000>();
constinit int const* const primes_data = primes.data();
constinit size_t const primes_size = primes.size();
