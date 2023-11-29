#include <stdio.h>
#include <string.h>

#include "ipv4address.h"
#ifdef _WIN32
#include <WinSock.h>
#else
#include <arpa/inet.h>
#endif

std::string IPv4AddressConvertToString( uint32_t addr )
{
	char tmpArray[20] = {0};
	uint8_t* p = (uint8_t*)&addr;
	uint8_t tmpByte1 = p[0];
	uint8_t tmpByte2 = p[1];
	uint8_t tmpByte3 = p[2];
	uint8_t tmpByte4 = p[3];

	sprintf(tmpArray,"%d.%d.%d.%d", tmpByte1,tmpByte2,tmpByte3,tmpByte4);

	return std::string(tmpArray);
}

uint32_t IPv4AddressConvertToInteger(const char* ip)
{
    return inet_addr(ip);
}

bool is_valid_ipaddress(const char* ip)
{
	bool isValid = true;

	int 			n, ip1, ip2, ip3, ip4;
	char 			dummy;

	n = sscanf(ip, "%3d.%3d.%3d.%3d%1c", &ip1, &ip2, &ip3, &ip4, &dummy);

	if (n != 4 || ip1 > 0xff || ip2 > 0xff || ip3 > 0xff || ip4 > 0xff) 
	{
		isValid = false;
	}
	
	return isValid;
}
