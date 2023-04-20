#ifndef OGSkyLayerActor_h__
#define OGSkyLayerActor_h__

#include "OGActor.h"


#include "OgrePlane.h"

namespace Orphigine
{
	class ActorFactory;
	
	class SkyLayerActor : public Actor
	{
	protected:
		class Factory;

	public:
		SkyLayerActor(void);
		virtual ~SkyLayerActor();

		virtual const String& getType(void) const;
		virtual const String& getCategory(void) const;
		virtual void createRenderInstance();
		virtual void destroyRenderInstance(void);
		virtual void updateRenderInstance(void);
		virtual bool loadFromStream(
			Ogre::Serializer* pSerializer,
			std::shared_ptr<Ogre::DataStream>& stream,
			int32_t version);
		virtual bool saveToBinaryFile(Ogre::Serializer* pSerializer);
		virtual std::size_t	calcSerializedSize();

		//////////////////////////////////////////////////////////////////////////

		static const String msType;
		static const String msCategory;

		static ActorFactory* getFactory(void);
		//////////////////////////////////////////////////////////////////////////


	protected:		

		void updateRenderInstanceImpl(void);

	public:     // Intend for direct access by property commands only, DO NOT access outside		
		int mLayerIndex;
		Ogre::String mMeshName;	
		bool   mDrawFirst;
		Real   mScale;
		Real   mYScale;
		Real   mAngle;
		Real   mHeightOffset;
		Real   mUScroll;
		Real   mVScroll;
		//Ogre::Vector3 mDir;
		bool mKeepDistance;
		bool mKeepHeight;
		bool mKeepOrient;	
		bool mEnableLight;
		bool mAffectByFog;

		int mIndex;
	};
}


#endif // OGSkyLayerActor_h__