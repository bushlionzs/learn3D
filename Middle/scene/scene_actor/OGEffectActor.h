#ifndef OGEffectActor_h__
#define OGEffectActor_h__

#include "OGPlacementActor.h"

namespace Orphigine {

	class ActorFactory;
	class Impact;

	class  EffectActor : public PlacementActor
	{
	protected:
		class Factory;

	public:
		EffectActor(void);
		virtual ~EffectActor();

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

		void setEffectName( const String &name );

		const String &getEffectName(void) const
		{
			return mEffectName;
		}

		//////////////////////////////////////////////////////////////////////////
		Impact * getEffect(void) const
		{
			return mEffect;
		}

	protected:

		/// effect template name
		String mEffectName;
		Impact *mEffect;

	protected:

		void createEffect(void);
		void destroyEffect(void);
	};
}

#endif // OGEffectActor_h__