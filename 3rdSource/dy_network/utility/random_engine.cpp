#include "random_engine.h"
#include <mutex>
#include <thread>
#include <random>
#include <time.h>
#include "time_util.h"

namespace dy_network
{

uint32_t generate_seed()
{
    uint32_t seed = get_tick_count() & 0xFFFFFFFF;
    try {
        seed = std::random_device{}();
    }
    catch (...)
    {
    }
    return seed;
}

class DefaultRandomGenerator : public RandomGenerator
{
public:
    DefaultRandomGenerator() : _engine(generate_seed()) {}

    void seed(unsigned int seq) override
    {
        std::lock_guard<std::mutex> guard(_mu);
        _engine.seed(seq);
    }

    unsigned int generate() override
    {
        std::lock_guard<std::mutex> guard(_mu);
        return _engine();
    }

private:
    std::default_random_engine _engine;
    std::mutex _mu;
};

// static
RandomGenerator& RandomGenerator::rng()
{
    static DefaultRandomGenerator default_rand_generator;
    return default_rand_generator;
}

// static
uint32_t RandomGenerator::create_id()
{
    return static_cast<uint32_t>(rng().generate());
}

//static
uint64_t RandomGenerator::create_id64()
{
    return static_cast<uint64_t>(create_id()) << 32 | create_id();
}



}

