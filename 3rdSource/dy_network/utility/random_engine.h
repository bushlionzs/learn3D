#pragma once
#include <stdint.h>
#include <random>

namespace dy_network
{

class RandomGenerator
{
public:
    virtual ~RandomGenerator() = default;

    virtual void seed(unsigned int seq) = 0;
    virtual unsigned int generate() = 0;

    static RandomGenerator& rng();
    static std::string create_string(size_t length);
    static bool create_string(size_t length, const char *table, size_t table_length, std::string *out);
    static uint32_t create_id();
    static uint64_t create_id64();
};



}


