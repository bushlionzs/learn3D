#ifndef OGDetailActor_h__
#define OGDetailActor_h__

#include "OGPlacementActor.h"
#include "OGActorProxy.h"


namespace Orphigine
{
	class DetailActor;
	class ActorFactory;

	

	class DetailActor : public PlacementActor
	{
	protected:
		class Factory;
	public:
		DetailActor(void);
		~DetailActor(void);

		static ActorFactory* getFactory(void);
		static const String msType;
		static const String msCategory;

	public:
		virtual const String& getType(void) const;
		virtual const String& getCategory(void) const;
		virtual void createRenderInstance();
		virtual void destroyRenderInstance();
		virtual void updateRenderInstance();
		virtual bool loadFromStream(
			Serializer* pSerializer, 
			std::shared_ptr<DataStream>& stream,
			int32_t version);
		virtual bool saveToBinaryFile(Serializer* pSerializer);
		virtual std::size_t	calcSerializedSize();

		void	createDetailObject();
		void	destroyDetailObject();
		void	updateDetailObject();

		void	waveGrass(Ogre::Real nTimePass);

		const String&	getDetailFileName()	const {return mDetailFileName;}
		void	setDetailFileName( const String &sFilename );

		void	onPosChange();

	protected:
		//System*	mSystem;
		ActorProxy* mProxy;


	public:
		String	mMaterialName;		
		String  mDetailFileName;
		int			mSplitNumber;	///one split number
		float		mRandPos;
		float		mDensity;
		float		mDetailWidth;
		float		mDetailHeight;
		float		mDetailRandSize;
		float		mRegionWidth;
		float		mRegionHeight;


		Ogre::String	mImageName;
		Ogre::String	mOldImageName;

		float		mLightThrehold1;
		float		mLightThrehold2;
		float		mLightThrehold3;
		float		mLightThrehold4;

	protected:
		Ogre::Real xinc;
		Ogre::Real zinc;
		Ogre::Real xpos;
		Ogre::Real zpos;
		Ogre::Vector4 offset;

	};
}

#endif // OGDetailActor_h__