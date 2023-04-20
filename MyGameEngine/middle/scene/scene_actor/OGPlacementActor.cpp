#include "OgreHeader.h"
#include "OGPlacementActor.h"
#include "engine_manager.h"

namespace Orphigine
{
	

	PlacementActor::PlacementActor(void)
		: Actor()
		, mSceneNode(NULL)
		, mCreateLevel(50.0f)
		//, mSystem(NULL)
	{
	}
	//-----------------------------------------------------------------------
	PlacementActor::~PlacementActor()
	{

	}
	//-----------------------------------------------------------------------
	void PlacementActor::createRenderInstance()
	{
		assert(!mSceneNode);

		
		mSceneNode = EngineManager::getSingleton().getBaseSceneNode()->createChildSceneNode(mName);
		mSceneNode->setPosition(mTransform.mPosition);
		mSceneNode->setOrientation(mTransform.mRotation);
		mSceneNode->setScale(mTransform.mScale);
		mSceneNode->setInitialState();
	}
	//-----------------------------------------------------------------------
	void PlacementActor::destroyRenderInstance(void)
	{

	}
	
	//-----------------------------------------------------------------------
	void PlacementActor::setCreateLevel(Real level)
	{
		if (mCreateLevel != level)
		{
			mCreateLevel = level;
			_updateCreateLevel();
		}
	}
	//-----------------------------------------------------------------------
	void PlacementActor::_updateCreateLevel(void)
	{
		if (mSceneNode)
		{
			 //mSceneNode->setVisible( gSystemPtr->_determineCreateLevel(mCreateLevel) ); 
		}
	}
	//-----------------------------------------------------------------------
	void PlacementActor::addBaseProperty(void)
	{
		
	}
	
	
}
