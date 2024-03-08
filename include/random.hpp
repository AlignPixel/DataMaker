#ifndef RANDOM_HPP
#define RANDOM_HPP

#include <random>

namespace DATA_MAKER
{ // random
    class Random
    {
        // std::random_device rd;
        std::mt19937 engine{std::random_device()()};
        std::uniform_int_distribution<long long> dis; // [0,0x7fffffffffffffff]
        std::uniform_real_distribution<double> unif{0.0, 1.0};

    public:
        Random() {}
        Random(int l, int r) { dis = std::uniform_int_distribution<long long>(l, r); }
        double doub()
        {
            return unif(engine); // [0.0, 1.0]
        }

        long long operator()() { return dis(engine); }
        long long operator()(long long l, long long r) { return l == r ? l : dis(engine) % (r - l + 1) + l; }

        Random create(int l, int r) { return Random(l, r); }
    } RND;

} // namespace DATA_MAKER random

#endif // RANDOM_HPP
