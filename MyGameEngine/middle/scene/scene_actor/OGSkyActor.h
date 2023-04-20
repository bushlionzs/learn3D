#ifndef OGSkyActor_h__
#define OGSkyActor_h__

#include "OGActor.h"

#include "OgrePlane.h"

namespace Orphigine
{
	class ActorFactory;
	class SkyPlaneActor : public Actor
	{
	protected:
		class Factory;

	public:
		SkyPlaneActor(void);
		virtual ~SkyPlaneActor();

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

		//////////////////////////////////////////////////////////////////////////

		static const String msType;
		static const String msCategory;

		static ActorFactory* getFactory(void);
		//////////////////////////////////////////////////////////////////////////

	protected:

		void updateRenderInstanceImpl(void);

	public:     // Intend for direct access by property commands only, DO NOT access outside
		//��д�����Ƶĳ����ļ�ʱ����������������ݳ�Ա��˳���λ�ã���������ı����ͺ͵���λ��
		// dscky add///////////////////////////////
		Ogre::String mMaterialName;
		int mLayer;
		Ogre::Plane mPlane;
		Ogre::Real mScale;
		Ogre::Real mTiling;
		Ogre::Real mBow;
		bool mDrawFirst;
		int mXsegments;
		int mYsegments;
		//��д�����Ƶĳ����ļ�ʱ����������������ݳ�Ա��˳���λ�ã���������ı����ͺ͵���λ��
		// dscky add///////////////////////////////
	};

	class SkyDomeActor : public Actor
	{
	protected:
		class Factory;

	public:
		SkyDomeActor(void);
		virtual ~SkyDomeActor();

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


		//////////////////////////////////////////////////////////////////////////

		static const String msType;
		static const String msCategory;

		static ActorFactory* getFactory(void);
		//////////////////////////////////////////////////////////////////////////


	protected:

		void updateRenderInstanceImpl(void);

	public:     // Intend for direct access by property commands only, DO NOT access outside
		//��д�����Ƶĳ����ļ�ʱ����������������ݳ�Ա��˳���λ�ã���������ı����ͺ͵���λ��
		// dscky add///////////////////////////////
		Ogre::String mMaterialName;
		int mLayer;
		Ogre::Real mCurvature;
		Ogre::Real mTiling;
		Ogre::Real mDistance;
		bool mDrawFirst;
		Ogre::Quaternion mOrientation;
		int mXsegments;
		int mYsegments;
		int mYsegments_keep;
		
		int mIndex;
	};


	class SkyBoxActor : public Actor
	{
	protected:
		class Factory;

	public:
		SkyBoxActor(void);
		virtual ~SkyBoxActor();

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

		//////////////////////////////////////////////////////////////////////////

		static const String msType;
		static const String msCategory;

		static ActorFactory* getFactory(void);
		//////////////////////////////////////////////////////////////////////////


	protected:

		void updateRenderInstanceImpl(void);

	public:     // Intend for direct access by property commands only, DO NOT access outside
		//��д�����Ƶĳ����ļ�ʱ����������������ݳ�Ա��˳���λ�ã���������ı����ͺ͵���λ��
		// dscky add///////////////////////////////
		Ogre::String mMaterialName;
		int mLayer;
		Ogre::Real mDistance;
		bool mDrawFirst;
		Ogre::Quaternion mOrientation;
		
		int mIndex;
	};
}


#endif // OGSkyActor_h__