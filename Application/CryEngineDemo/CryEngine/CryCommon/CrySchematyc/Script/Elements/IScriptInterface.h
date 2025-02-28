// Copyright 2016-2021 Crytek GmbH / Crytek Group. All rights reserved.

#pragma once

#include "CrySchematyc/Script/IScriptElement.h"

namespace Schematyc
{
struct IScriptInterface : public IScriptElementBase<EScriptElementType::Interface>
{
	virtual ~IScriptInterface() {}

	virtual const char* GetAuthor() const = 0;
	virtual const char* GetDescription() const = 0;
};
} // Schematyc
