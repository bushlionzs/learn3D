#ifndef OGActor_h__
#define OGActor_h__

#include "OgreSceneManager.h"
#include "OgreSceneNode.h"
#include "OGPropertyInterface.h"
#include "OgreRay.h"

namespace Orphigine
{
	class ResourceCollection;
	struct ActorSetIndices;

	typedef std::list<Entity*> EntityList;

	class  Actor : public PropertyInterface, public std::enable_shared_from_this<Actor>
	{
		// Allow ActorSetIndices access mName to simply multi-index container adaptor
		friend struct ActorSetIndices;
	protected:
		String mName;
		uint64_t  mData;
		SceneManager* mSceneManager;
	public:
		Actor(void);
		virtual ~Actor();

		//½Ó¿Úº¯Êý
		virtual void setName(const String& name);
		virtual const String& getType(void) const = 0;
		virtual const String& getCategory(void) const = 0;
		virtual void queryReferenceResources(ResourceCollection* resourceCollection);
		virtual void queryBakableEntities(EntityList& entities);
		virtual void createRenderInstance()=0;
		virtual void createRenderInstanceFromLoadThread(){};
		virtual void destroyRenderInstance(void)=0;
		virtual void destroyRenderInstanceFromLoadThread(void){}; 
		virtual bool loadFromStream(Serializer* pSerializer, std::shared_ptr<DataStream>& stream, int32_t version)=0;
		virtual std::size_t	calcSerializedSize()=0;
		virtual void OnSceneManagerChagned() {}

		const String& getName(void) const
		{
			return mName;
		}

		uint64_t getData(void) const
		{
			return mData;
		}
		void setData(uint64_t data);

		virtual std::pair<bool, Real> queryIntersect(Ogre::Ray& ray)
		{
			return std::pair<bool, Real>(false, 0.0f);
		}

		void setSceneManager(SceneManager* sceneManager);
	};

	typedef std::shared_ptr<Actor> ActorPtr;
	typedef std::weak_ptr<Actor> ActorWeakPtr;

}

#endif // OGActor_h__