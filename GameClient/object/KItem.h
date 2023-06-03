#pragma once
#include "KObject.h"

class KItem : public KObject
{
public:
	KItem();
	~KItem();

	void setRule(int32_t nRuleID);
	int32_t getRule();
private:
	int32_t mRuleId;
};