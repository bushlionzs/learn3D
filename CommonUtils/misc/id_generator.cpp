#include "id_generator.h"
#include <chrono>
#include <random>
#include <thread>
using namespace std;

namespace CommonUtils
{
    uint64_t generateObjectId()
    {
        static mt19937_64 eng{ random_device{}() };

        auto time_now = chrono::high_resolution_clock::now().time_since_epoch().count();
        auto thread_id = hash<thread::id>()(this_thread::get_id());
        auto random_value = eng();

        uint64_t a = static_cast<uint64_t>(time_now);
        uint64_t b = static_cast<uint64_t>(thread_id);
        uint64_t c = random_value;

        // mix function based on Knuth's multiplicative method
        // https://gist.github.com/badboy/6267743
        a *= 2654435761u;
        b *= 2654435761u;
        c *= 2654435761u;

        a ^= (a >> 16);
        b ^= (b >> 16);
        c ^= (c >> 16);

        return a + b + c;
    }
}