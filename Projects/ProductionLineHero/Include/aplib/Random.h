#ifndef APLIB_RANDOM
#define APLIB_RANDOM

// std
#include <cassert>
#include <chrono>
#include <random>
#include <set>

extern long long const g_Seed(std::chrono::high_resolution_clock::now().time_since_epoch().count());

extern std::mt19937 g_MarsenneTwister(g_Seed);

extern std::uniform_real_distribution<double> const g_UniformUNormDist  (0.0, 1.0);
extern std::uniform_int_distribution<int>     const g_UniformBooleanDist(0, 1);

extern inline double randUNorm()
{
    return g_UniformUNormDist(g_MarsenneTwister);
}

template <typename NumType>
extern NumType randValue(NumType i_Min, NumType i_Max)
{
    assert(i_Min <= i_Max);
    return randUNorm() * abs(static_cast<double>(i_Max - i_Min)) + i_Min;
}

extern inline bool randBool()
{
    return g_UniformBooleanDist(g_MarsenneTwister) == 1;
}

extern inline std::set<int32_t> randIntSet(int32_t i_Min, int32_t i_Max, uint32_t i_NumSamples)
{
    // TEST ME BEFORE USE !!
    assert(false);

    assert(i_Max >= i_Min);
    uint32_t range = i_Max - i_Min + 1;
    assert(range >= i_NumSamples);

    // Create set of available choices
    std::vector<int32_t> available(range);
    for (uint32_t i = 0; i < range; ++i)
    {
        available[i] = i + i_Min;
    }

    // Pick among remaining choices
    std::set<int32_t> set;
    for (uint32_t i = 0; i < i_NumSamples; ++i)
    {
        uint32_t picked = randUNorm() * (range - i) + i_Min;
        set.emplace(available[picked]);
        available[picked] = available[range - i - 1];
    }

    return set;
}

#endif //APLIB_RANDOM