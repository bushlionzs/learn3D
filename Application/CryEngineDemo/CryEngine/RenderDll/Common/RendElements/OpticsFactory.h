// Copyright 2012-2021 Crytek GmbH / Crytek Group. All rights reserved.

#pragma once

#include <CryRenderer/IFlares.h>

class COpticsFactory
{

private:
	COpticsFactory(){}

public:
	static COpticsFactory* GetInstance()
	{
		static COpticsFactory instance;
		return &instance;
	}

	IOpticsElementBase* Create(EFlareType type) const;
};
