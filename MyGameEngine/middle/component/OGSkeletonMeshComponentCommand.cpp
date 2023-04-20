#include "OgreHeader.h"
#include"OGSkeletonMeshComponentCommand.h"

namespace Orphigine
{
	CommandResultEnum LMsetLogicModelName2Command::execute()
	{
		SkeletonMeshActor* pLogicModelObject = (Orphigine::SkeletonMeshActor*)EngineManager::getSingletonPtr()->getRegisterObject(mObjName);
		if(pLogicModelObject)
		{
			if(pLogicModelObject->mIsLoadingResFlag)//正在加载资源，阻塞队列
			{
				//mWaitTime = Ogre::Root::getSingletonPtr()->getTimer()->getMilliseconds() - mStartTime;
				return CRE_BLOCK;
			}

			if (mWaitTime > 0)
			{
				mWaitTime = 0;
				mStartTime = Ogre::Root::getSingletonPtr()->getTimer()->getMilliseconds();
			}				
			if(pLogicModelObject->setLogicModelName2(mModelName,mLoadResFlag))//失败表示阻塞队列
				return CRE_SUCCESS;		
			else
			{					
				//mBlockTime = Ogre::Root::getSingletonPtr()->getTimer()->getMilliseconds() - mStartTime;
				return CRE_BLOCK;
			}
		}
		return CRE_FAILED;
	}
}