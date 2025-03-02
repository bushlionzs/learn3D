// Copyright 2004-2021 Crytek GmbH / Crytek Group. All rights reserved.

#include "StdAfx.h"
#include "BasicArea.h"
CBasicArea::~CBasicArea()
{
	delete m_pObjectsTree;
	m_pObjectsTree = NULL;
}
