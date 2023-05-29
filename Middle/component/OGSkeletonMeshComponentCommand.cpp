#include "OgreHeader.h"
#include"OGSkeletonMeshComponentCommand.h"

namespace Orphigine
{
	CommandResultEnum LMsetLogicModelName2Command::execute()
	{
		SkeletonMeshActor* pLogicModelObject = (Orphigine::SkeletonMeshActor*)EngineManager::getSingletonPtr()->getRegisterObject(mObjName);
		if(pLogicModelObject)
		{
			if(pLogicModelObject->mIsLoadingResFlag)//���ڼ�����Դ����������
			{
				//mWaitTime = Ogre::Root::getSingletonPtr()->getTimer()->getMilliseconds() - mStartTime;
				return CRE_BLOCK;
			}

			if (mWaitTime > 0)
			{
				mWaitTime = 0;
				mStartTime = Ogre::Root::getSingletonPtr()->getTimer()->getMilliseconds();
			}				
			if(pLogicModelObject->setLogicModelName2(mModelName,mLoadResFlag))//ʧ�ܱ�ʾ��������
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