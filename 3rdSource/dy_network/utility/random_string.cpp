#include <stdlib.h>
#include <time.h>
#include "random_engine.h"
#include "random_string.h"


namespace dy_network
{

bool create_random_string(size_t len, const char *table, int table_size, std::string* out)
{
    out->resize(len);

    for (size_t i = 0; i < len; ++i)
    {
        out->at(i) = table[dy_network::RandomGenerator::create_id() % table_size];
    }

    return true;
}

std::string create_random_string(size_t len)
{
    std::string str;
    create_random_string(len, ALNUM_CHAR_TABLE, sizeof(ALNUM_CHAR_TABLE), &str);
    return str;
}

std::string create_base64_random_string(size_t len)
{
    std::string str;
    create_random_string(len, BASE64_CHAR_TABLE, sizeof(BASE64_CHAR_TABLE), &str);
    return str;
}

}
