/**********************************************************************************************//**
 * @file	CommonClass\IPv4Address.h
 *
 * @brief	Declares the IPv4Address interface.
 **************************************************************************************************/

#ifndef IPADDRESS_H
#define IPADDRESS_H

#include <stdint.h>
#include <stdio.h>
#include <string>

std::string IPv4AddressConvertToString( uint32_t addr );
uint32_t IPv4AddressConvertToInteger( const char* ip );
bool is_valid_ipaddress(const char* ip);

#endif