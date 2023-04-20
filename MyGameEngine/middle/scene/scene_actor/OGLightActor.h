#ifndef OGLightActor_h__
#define OGLightActor_h__

#include "OGActor.h"
#include "OgreColourValue.h"
#include "OgreSerializer.h"

namespace Orphigine
{
	class ActorFactory;

	class  LightActor : public Actor, public Serializer
	{
	protected:
		class Factory;

	public:
		LightActor(void);
		virtual ~LightActor();

		virtual const String& getType(void) const;
		virtual const String& getCategory(void) const;
		virtual void createRenderInstance();
		virtual void destroyRenderInstance(void);
		virtual void updateRenderInstance(void);
		virtual bool loadFromStream(
			Serializer* pSerializer,
			std::shared_ptr<DataStream>& stream,
			int32_t version);
		virtual bool saveToBinaryFile(Serializer* pSerializer);
		virtual std::size_t	calcSerializedSize();

		uint32_t getPropertyFlags(const String& name) const;

		//////////////////////////////////////////////////////////////////////////

		static const String msType;
		static const String msCategory;

		static ActorFactory* getFactory(void);

		Ogre::Light* getLight(void) const
		{
			return mLight;
		}

		Ogre::Quaternion getOrientation() const;
		void setOrientation(const Ogre::Quaternion& ori);

		Ogre::Vector3 getScale() const;
		void setScale(const Ogre::Vector3& scale);

	protected:


		void createLight(void);
		void destroyLight(void);
		void updateRenderInstanceImpl(void);

	public:     // Intend for direct access by property commands only, DO NOT access outside
		Ogre::ColourValue mDiffuse;
		Ogre::ColourValue mSpecular;
		Ogre::Vector3 mPosition;
		Ogre::Vector3 mDirection;
		Ogre::Real mRange;
		Ogre::Real mAttenuationConstant;
		Ogre::Real mAttenuationLinear;
		Ogre::Real mAttenuationQuadric;
		Ogre::Real mSpotOuterAngle;
		Ogre::Real mSpotInnerAngle;
		Ogre::Real mSpotFalloff;
		bool mCastShadows;
		bool mStaticLight;
		//cky-add 20080421<<<<<<<<
		bool mIsAreaLightShadowFlag;
		//cky-add 20080421<<<<<<<<

		Ogre::Light* mLight;
	};

}

#endif // OGLightActor_h__