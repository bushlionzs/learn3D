// Copyright 2016-2021 Crytek GmbH / Crytek Group. All rights reserved.

#pragma once

#include "CrySchematyc/Script/IScriptElement.h"

namespace Schematyc
{
struct IScriptState : public IScriptElementBase<EScriptElementType::State>
{
	virtual ~IScriptState() {}

	virtual CryGUID GetPartnerGUID() const = 0;
};
} // Schematyc
