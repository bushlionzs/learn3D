#ifndef OGImpactModuleFactory_h__
#define OGImpactModuleFactory_h__


namespace Orphigine
{
	class ImpactModule;
	class Engine;
}

namespace Orphigine
{

	class ImpactModuleFactory
	{		
	public:
		ImpactModuleFactory() {};
		virtual ~ImpactModuleFactory() {};

		/** Returns the name of the factory, the name which identifies the particle emitter type this factory creates. */
		virtual String getName() const = 0;

		/** Creates a new emitter instance.
		@remarks
		The subclass MUST add a pointer to the created instance to mEmitters.
		*/
		virtual ImpactModule *createElement() = 0;

		/** Destroys the emitter pointed to by the parameter (for early clean up if reauired). */
		virtual void destroyElement(ImpactModule *e);

		//typedef std::vector<EffectElement *> Elements;

		//protected:
		//	Elements mElements;
	};

	///////////////////////////////////////////////////////////////////////
	class ImpactParticleModuleFactory : public ImpactModuleFactory
	{
	public:

		ImpactParticleModuleFactory();
		~ImpactParticleModuleFactory();

		virtual String getName() const	{	return "Particle";	};
		virtual ImpactModule *createElement();
		static ImpactModuleFactory* getFactory();
	};

	///////////////////////////////////////////////////////////////////////
	class ImpactMeshModuleFactory : public ImpactModuleFactory
	{
	public:

		ImpactMeshModuleFactory();
		~ImpactMeshModuleFactory();

		virtual String getName() const	{	return "Mesh";	};
		virtual ImpactModule *createElement();
		static ImpactModuleFactory* getFactory();
	};

	///////////////////////////////////////////////////////////////////////
	class ImpactBillboardSetModuleFactory : public ImpactModuleFactory
	{
	public:

		ImpactBillboardSetModuleFactory();
		~ImpactBillboardSetModuleFactory();

		virtual String getName() const	{	return "BillboardSet";	};
		virtual ImpactModule *createElement();
		static ImpactModuleFactory* getFactory();
	};

	///////////////////////////////////////////////////////////////////////
	class ImpactProjectorModuleFactory : public ImpactModuleFactory
	{
	public:

		ImpactProjectorModuleFactory();
		~ImpactProjectorModuleFactory();

		virtual String getName() const	{	return "Projector";	};
		virtual ImpactModule *createElement();
		static ImpactModuleFactory* getFactory();
	};

	///////////////////////////////////////////////////////////////////////
	class ImpactBeamModuleFactory : public ImpactModuleFactory
	{
	public:

		ImpactBeamModuleFactory();
		~ImpactBeamModuleFactory();

		virtual String getName() const	{	return "Beam";	};
		virtual ImpactModule *createElement();
		static ImpactModuleFactory* getFactory();
	};

	///////////////////////////////////////////////////////////////////////
	class ImpactPointLightModuleFactory : public ImpactModuleFactory
	{
	public:

		ImpactPointLightModuleFactory();
		~ImpactPointLightModuleFactory();

		virtual String getName() const	{	return "PointLight";	};
		virtual ImpactModule *createElement();
		static ImpactModuleFactory* getFactory();
	};

	///
	class ImpactRibandModuleFactory : public ImpactModuleFactory
	{
	public:
		ImpactRibandModuleFactory();
		~ImpactRibandModuleFactory();

		virtual String getName() const	{	return "RibbonTrail";	};
		virtual ImpactModule *createElement();
		static ImpactModuleFactory* getFactory();
	};
}

#endif // OGImpactModuleFactory_h__