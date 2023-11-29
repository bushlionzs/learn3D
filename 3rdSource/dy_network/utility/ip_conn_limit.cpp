#include "scoped_lock.h"
#include "ip_conn_limit.h"

IpConnLimit::IpConnLimit(uint32_t uiMaxConnPerIp)
    : m_uiMaxConnPerIp(uiMaxConnPerIp)
{
}

IpConnLimit::~IpConnLimit()
{
}

uint32_t IpConnLimit::GetConnCntInIp(uint32_t ip) const
{
    return GetConnCntInIp(dy_network::IPAddress(ip));
}

bool IpConnLimit::IsConnLimitInIp(uint32_t ip) const
{
    return IsConnLimitInIp(dy_network::IPAddress(ip));
}

bool IpConnLimit::AddIpConn(uint32_t ip)
{
    return AddIpConn(dy_network::IPAddress(ip));
}

void IpConnLimit::DecIpConn(uint32_t ip)
{
    DecIpConn(dy_network::IPAddress(ip));
}

uint32_t IpConnLimit::GetConnCntInIp(const std::string& ip) const
{
    auto ipaddr = dy_network::IPAddress();
    if (!ipaddr.from_string(ip.c_str()))
    {
        return 0;
    }
    
    return GetConnCntInIp(ipaddr);
}

bool IpConnLimit::IsConnLimitInIp(const std::string& ip) const
{
    auto ipaddr = dy_network::IPAddress();
    if (!ipaddr.from_string(ip.c_str()))
    {
        return false;
    }
    
    return IsConnLimitInIp(ipaddr);
}

bool IpConnLimit::AddIpConn(const std::string& ip)
{
    auto ipaddr = dy_network::IPAddress();
    if (!ipaddr.from_string(ip.c_str()))
    {
        return false;
    }

    return AddIpConn(ipaddr);
}

void IpConnLimit::DecIpConn(const std::string& ip)
{
    auto ipaddr = dy_network::IPAddress();
    if (!ipaddr.from_string(ip.c_str()))
    {
        return;
    }

    DecIpConn(ipaddr);
}

uint32_t IpConnLimit::GetConnCntInIp(const dy_network::IPAddress& ip) const
{
    if (ip.is_nil())
    {
        return 0;
    }
    
    ScopedLock<PlatformMutex> _lock(m_oIpConnMapMutex);
    auto oIt = m_mapIpConnCnt.find(ip);
    if (oIt == m_mapIpConnCnt.end())
    {
        return 0;
    }

    return oIt->second;
}

bool IpConnLimit::IsConnLimitInIp(const dy_network::IPAddress& ip) const
{
    uint32_t uiConnCntInIp = GetConnCntInIp(ip);
	
    return (uiConnCntInIp > GetMaxConnPerIp());
}

bool IpConnLimit::AddIpConn(const dy_network::IPAddress& ip)
{
    if (ip.is_nil())
    {
        return false;
    }

    uint32_t maxConn = GetMaxConnPerIp();
    ScopedLock<PlatformMutex> _lock(m_oIpConnMapMutex);
    auto oIt = m_mapIpConnCnt.find(ip);
    if (oIt == m_mapIpConnCnt.end())
    {
        m_mapIpConnCnt.insert(std::unordered_map<dy_network::IPAddress, uint32_t>::value_type(ip, 1));
    }
    else
    {
        if (oIt->second >= maxConn)
        {
            return false;
        }
        else
        {
            oIt->second++;
        }
    }

    return true;
}

void IpConnLimit::DecIpConn(const dy_network::IPAddress& ip)
{
    if (ip.is_nil())
    {
        return;
    }

    ScopedLock<PlatformMutex> _lock(m_oIpConnMapMutex);
    auto oIt = m_mapIpConnCnt.find(ip);
    if (oIt == m_mapIpConnCnt.end())
    {
        return;
    }
    else
    {
        if (oIt->second == 1)
        {
            m_mapIpConnCnt.erase(oIt);  
        }
        else
        {
            oIt->second--;
        }
    }
}

void IpConnLimit::SetMaxConnPerIp(uint32_t uiMaxConn) 
{
    ScopedLock<PlatformMutex> _lock(m_oIpConnMapMutex);
    m_uiMaxConnPerIp = uiMaxConn;
}

uint32_t IpConnLimit::GetMaxConnPerIp() const
{ 
    ScopedLock<PlatformMutex> _lock(m_oIpConnMapMutex);
    return m_uiMaxConnPerIp; 
}




