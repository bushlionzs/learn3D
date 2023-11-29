
#ifndef __IP_CONN_LIMIT_H__
#define __IP_CONN_LIMIT_H__

#include <stdint.h>
#include <unordered_map>
#include <string>

#include "ip_address.h"
#include "platform_mutex.h"

class IpConnLimit
{
public:
	IpConnLimit(uint32_t uiMaxConnPerIp);
    ~IpConnLimit();

    uint32_t GetConnCntInIp(uint32_t ip) const;
	bool IsConnLimitInIp(uint32_t ip) const;      // true
    
    bool AddIpConn(uint32_t ip);
	void DecIpConn(uint32_t ip);

    uint32_t GetConnCntInIp(const std::string& ip) const;
	bool IsConnLimitInIp(const std::string& ip) const;
    
    bool AddIpConn(const std::string& ip);
	void DecIpConn(const std::string& ip);


    void SetMaxConnPerIp(uint32_t uiMaxConn);
    uint32_t GetMaxConnPerIp() const;

    uint32_t GetConnCntInIp(const dy_network::IPAddress& ip) const;
	bool IsConnLimitInIp(const dy_network::IPAddress& ip) const;
    
    bool AddIpConn(const dy_network::IPAddress& ip);
	void DecIpConn(const dy_network::IPAddress& ip);
private:
	uint32_t m_uiMaxConnPerIp;

    mutable PlatformMutex m_oIpConnMapMutex;
    std::unordered_map<dy_network::IPAddress, uint32_t> m_mapIpConnCnt;
};

#endif // end for __IP_CONN_LIMIT_H__



