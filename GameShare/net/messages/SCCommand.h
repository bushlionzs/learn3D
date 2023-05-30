#pragma once
#include "net/net_message.h"
class SCCommand : public NetPacket
{
public:
	SCCommand();
	~SCCommand();

	virtual bool process();

	void setUIIndex(int32_t uiIndex);
	void setParam(SXParam& param);
private:
	int32_t mUIIndex;
	SXParam mSXParam;
};