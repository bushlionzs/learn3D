// Copyright 2017-2021 Crytek GmbH / Crytek Group. All rights reserved.

struct IProtocolBuilder;

struct IManualFrameStepController
{
	//! Add message sinks to receive network events
	virtual void DefineProtocols(IProtocolBuilder* pBuilder) = 0;
};