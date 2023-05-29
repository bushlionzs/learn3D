#ifndef OGModelActor_h__
#define OGModelActor_h__

#include "OGPlacementActor.h"

namespace Orphigine
{
	class ModelComponent;
	class ActorFactory;
	class ActorProxy;

	class  ModelActor : public PlacementActor
	{
	protected:
		class Factory;

	public:
		ModelActor(void);
		virtual ~ModelActor();

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


		void  setTransparency( Real &newTrans );
		Real  getTransparency() const;
		//////////////////////////////////////////////////////////////////////////

		static const String msType;
		static const String msCategory;

		static ActorFactory* getFactory(void);

		//////////////////////////////////////////////////////////////////////////

		ModelComponent* getModel(void) const
		{
			return mModel;
		}

		const String& getModelName(void) const
		{
			return mModelName;
		}

		void setModelName(const String& actorName);

		Real getAnimationLevel(void) const
		{
			return mAnimationLevel;
		}

		void setAnimationLevel(Real level);

		bool getCastShadows(void) const
		{
			return mCastShadows;
		}

		void setCastShadows(bool castShadows);

	protected:
		ActorProxy*		mProxy;
		ModelComponent*	mModel;
		Ogre::String	mModelName;
		Real			mAnimationLevel;
		Real			mTransparent;
		bool			mCastShadows;

		void createModel(void);
		void destroyModel(void);

	public:
		Real			mTransparentTime;
		bool			mBEnableTransparent;
	};

}

#endif // OGModelActor_h__