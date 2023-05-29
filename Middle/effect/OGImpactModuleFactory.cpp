#include "OgreHeader.h"
#include "OGImpactModuleFactory.h"
#include "OGImpactModule.h"
#include "OGImpactParticleModule.h"
#include "OGImpactMeshModule.h"
#include "OGImpactBillboardSetModule.h"
#include "OGImpactProjectorModule.h"
#include "OGImpactBeamModule.h"
#include "OGImpactPointLightModule.h"
#include "OGImpactRibandModule.h"

namespace Orphigine	{

	void ImpactModuleFactory::destroyElement(ImpactModule *e)
	{
		OGRE_DELETE e;
		/*
		assert (e);
		for ( Elements::iterator i = mElements.begin();
		i != mElements.end();	++i	)
		{
		if ((*i) == e)
		{
		OGRE_DELETE e;
		e = NULL;
		mElements.erase(i);
		}
		}
		*/
	}

	///////////////////////////////////////////////////////////
	ImpactParticleModuleFactory::ImpactParticleModuleFactory()
	{}

	ImpactParticleModuleFactory::~ImpactParticleModuleFactory()
	{
	}

	ImpactModule* ImpactParticleModuleFactory::createElement()
	{
		ImpactModule *element = OGRE_NEW ImpactParticleModule("Particle");
		//assert (element);
		//mElements.push_back(element);
		return element;
	}
	ImpactModuleFactory* ImpactParticleModuleFactory::getFactory()
	{
		static ImpactParticleModuleFactory factory;
		return &factory;
	}


	//////////////////////////////////////////////////////////
	ImpactMeshModuleFactory::ImpactMeshModuleFactory()
	{}

	ImpactMeshModuleFactory::~ImpactMeshModuleFactory()
	{
	}

	ImpactModule *ImpactMeshModuleFactory::createElement()
	{
		ImpactModule *element = OGRE_NEW ImpactMeshModule("Mesh");
		//assert (element);
		//mElements.push_back(element);
		return element;
	}
	ImpactModuleFactory* ImpactMeshModuleFactory::getFactory()
	{
		static ImpactMeshModuleFactory factory;
		return &factory;
	}

	//////////////////////////////////////////////////////////
	ImpactBillboardSetModuleFactory::ImpactBillboardSetModuleFactory()
	{}

	ImpactBillboardSetModuleFactory::~ImpactBillboardSetModuleFactory()
	{
	}

	ImpactModule *ImpactBillboardSetModuleFactory::createElement()
	{
		ImpactModule *element = OGRE_NEW ImpactBillboardSetModule("BillboardSet");
		//assert (element);
		//mElements.push_back(element);
		return element;
	}
	ImpactModuleFactory* ImpactBillboardSetModuleFactory::getFactory()
	{
		static ImpactBillboardSetModuleFactory factory;
		return &factory;
	}

	//////////////////////////////////////////////////////////
	ImpactProjectorModuleFactory::ImpactProjectorModuleFactory()
	{}

	ImpactProjectorModuleFactory::~ImpactProjectorModuleFactory()
	{
	}

	ImpactModule *ImpactProjectorModuleFactory::createElement()
	{
		ImpactModule *element = OGRE_NEW ImpactProjectorModule("Projector");
		//assert (element);
		//mElements.push_back(element);
		return element;
	}
	ImpactModuleFactory* ImpactProjectorModuleFactory::getFactory()
	{
		static ImpactProjectorModuleFactory factory;
		return &factory;
	}

	//////////////////////////////////////////////////////////
	ImpactBeamModuleFactory::ImpactBeamModuleFactory()
	{}

	ImpactBeamModuleFactory::~ImpactBeamModuleFactory()
	{
	}

	ImpactModule *ImpactBeamModuleFactory::createElement()
	{
		ImpactModule *element = OGRE_NEW ImpactBeamModule("Beam");
		//assert (element);
		//mElements.push_back(element);
		return element;
	}
	ImpactModuleFactory* ImpactBeamModuleFactory::getFactory()
	{
		static ImpactBeamModuleFactory factory;
		return &factory;
	}

	//////////////////////////////////////////////////////////
	ImpactPointLightModuleFactory::ImpactPointLightModuleFactory()
	{}

	ImpactPointLightModuleFactory::~ImpactPointLightModuleFactory()
	{
	}

	ImpactModule *ImpactPointLightModuleFactory::createElement()
	{
		ImpactModule *element = OGRE_NEW ImpactPointLightModule("PointLight");
		//assert (element);
		//mElements.push_back(element);
		return element;
	}
	ImpactModuleFactory* ImpactPointLightModuleFactory::getFactory()
	{
		static ImpactPointLightModuleFactory factory;
		return &factory;
	}

	//////////////////////////////////////////////////////////
	ImpactRibandModuleFactory::ImpactRibandModuleFactory()
	{
	}

	ImpactRibandModuleFactory::~ImpactRibandModuleFactory()
	{
	}

	ImpactModule *ImpactRibandModuleFactory::createElement()
	{
		ImpactModule *element = OGRE_NEW ImpactRibbonModule("RibbonTrail");
		//assert (element);
		//mElements.push_back(element);
		return element;
	}
	ImpactModuleFactory* ImpactRibandModuleFactory::getFactory()
	{
		static ImpactRibandModuleFactory factory;
		return &factory;
	}
}