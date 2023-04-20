#ifndef OGParticleSystemActor_h__
#define OGParticleSystemActor_h__


#include "OGPlacementActor.h"

namespace Orphigine {

	class ActorFactory;

	class  ParticleSystemActor : public PlacementActor
	{
	protected:
		class Factory;

	public:
		ParticleSystemActor(void);
		virtual ~ParticleSystemActor();

		virtual const String& getType(void) const;
		virtual const String& getCategory(void) const;

		virtual void createRenderInstance();
		virtual void destroyRenderInstance(void);
		virtual bool loadFromStream(
			Serializer* pSerializer,
			std::shared_ptr<DataStream>& stream,
			int32_t version);
		virtual bool saveToBinaryFile(Serializer* pSerializer);
		virtual std::size_t	calcSerializedSize();

		//////////////////////////////////////////////////////////////////////////

		static const String msType;
		static const String msCategory;

		static ActorFactory* getFactory(void);

		void setParticleSystemName( const String &name );

		const String &getParticleSystemName(void) const
		{
			return mParticleSystemName;
		}

		//////////////////////////////////////////////////////////////////////////
		ParticleSystem * getParticleSystem(void)
		{
			return mParticleSystem;
		}

		void setParticleSystem(ParticleSystem *system)
		{
			assert (system);
			mParticleSystem = system;
		}

	protected:
		String mParticleSystemName;

		ParticleSystem *mParticleSystem;

	protected:

		void createParticleSystem(void);
		void destroyParticleSystem(void);
	};
}

#endif 