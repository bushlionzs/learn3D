#ifndef OGPlacementActor_h__
#define OGPlacementActor_h__

#include "OGActor.h"
#include "OGImpact.h"

namespace Orphigine
{
	class Engine;

	class PlacementActor : public Actor
	{
	public:
		PlacementActor(void);
		virtual ~PlacementActor();

		virtual void createRenderInstance();
		virtual void createRenderInstanceFromLoadThread(){}
		virtual void destroyRenderInstance(void);
		virtual void destroyRenderInstanceFromLoadThread(void){}
		virtual bool loadFromStream(
			Serializer* pSerializer,
			std::shared_ptr<DataStream>& stream,
			int32_t version)=0;
		virtual bool saveToBinaryFile(Serializer* pSerializer)=0;
		virtual std::size_t	calcSerializedSize()=0;



		//////////////////////////////////////////////////////////////////////////

		SceneNode* getSceneNode(void) const
		{
			return mSceneNode;
		}

		Real getCreateLevel(void) const
		{
			return mCreateLevel;
		}

		void setCreateLevel(Real level);

		virtual void onPosChange()	{}

	protected:
		void addBaseProperty(void);


		void _updateCreateLevel(void);

		SceneNode* mSceneNode;



		//System* mSystem;

	public:     // Intend for direct access by property commands only, DO NOT access outside
		Orphigine::TransformInfo mTransform;
	protected:
		Real mCreateLevel;
	};

}
#endif // OGPlacementActor_h__