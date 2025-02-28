// Copyright 2016-2021 Crytek GmbH / Crytek Group. All rights reserved.

#pragma once

#include "CrySchematyc/Env/IEnvElement.h"

namespace Schematyc
{

struct IEnvModule : public IEnvElementBase<EEnvElementType::Module>
{
	virtual ~IEnvModule() {}
};

} // Schematyc
