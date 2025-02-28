// Copyright 2014-2021 Crytek GmbH / Crytek Group. All rights reserved.

#pragma once

#include <CrySerialization/IArchiveHost.h>

namespace Serialization
{

IArchiveHost* CreateArchiveHost();
void RegisterArchiveHostCVars();
}
