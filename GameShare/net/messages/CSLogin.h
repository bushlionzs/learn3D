#pragma once

#include "net/net_message.h"

class CSLogin : public NetPacket
{
public:
	CSLogin();
	virtual ~CSLogin();

	virtual bool process();
private:
	std::string mAcount;
	std::string mPasswd;
};