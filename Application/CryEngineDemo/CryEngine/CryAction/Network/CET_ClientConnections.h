// Copyright 2016-2021 Crytek GmbH / Crytek Group. All rights reserved.

#pragma once

#include "ClassRegistryReplicator.h"

void AddOnClientConnect(IContextEstablisher* pEst, EContextViewState state, bool isReset);
void AddOnClientEnteredGame(IContextEstablisher* pEst, EContextViewState state, bool isReset);