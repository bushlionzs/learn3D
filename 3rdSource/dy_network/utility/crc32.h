
#ifndef crc32_h__
#define crc32_h__

#include <stdint.h>
#include <string>

namespace dy
{ 

namespace network
{ 

namespace utility
{ 
    int make_crc32_table();
    uint32_t ComputeCrc32(unsigned char *string, uint32_t size);
}
}

}
#endif // crc32_h__
