// Copyright 2018 Crytek GmbH / Crytek Group. All rights reserved.
#include <CryPhysics/physinterface.h>

// Queries the simulation parameters of an entity, for example to check current gravitational influence or mass.
void GetSimulationParameters(IPhysicalEntity& physicalEntity)
{
	pe_simulation_params simulationParameters;
	if (physicalEntity.GetParams(&simulationParameters))
	{
		/* simulationParameters can now be used */
	}
}