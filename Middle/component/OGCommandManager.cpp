#include "OgreHeader.h"
#include "OGCommandManager.h"
#include "platform_log.h"
#include "OgreRoot.h"
#include "OgreTimer.h"
#include "OGSkeletonMeshActor.h"
#include "OGSkeletonMeshComponentCommand.h"


template<> Orphigine::CommandCacheManager* Ogre::Singleton<Orphigine::CommandCacheManager>::msSingleton = 0;

namespace Orphigine
{

#define _ENABLE_COMMAND_TIME_LOG_  1


CommandCache::CommandCache(unsigned long id):mCacheId(id),mCompleteTime(2),mOldRemanentCommandNum(0),mExecuteNumPerFrame(0), mBlockTime(0)
{
}
CommandCache::~CommandCache()
{
	clearCommand();
}
bool CommandCache::isEmpty()
{
	return mCommandQueue.empty();
}
bool CommandCache::pushCommand(Command* pCommand)
{
	if(pCommand)
	{	
		/*
		if (pCommand->getCommandType() == CMD_T_setLogicModelName2)
		{
			//先测试队列里是否是同样modelname的指令
			std::deque <Command* >::iterator iter;			
			for (iter = mCommandQueue.begin(); iter != mCommandQueue.end(); iter++)
			{
				Command * pCur = *iter;
				if (pCur->getCommandType() == CMD_T_setLogicModelName2)
				{
					LMsetLogicModelName2Command * psetLogicModel = (LMsetLogicModelName2Command *)pCur;
					LMsetLogicModelName2Command * psetLogicModel1 = (LMsetLogicModelName2Command *)pCommand;
					if (psetLogicModel->getModelName() == psetLogicModel1->getModelName())
					{
						return true;
					}
				}
			}
		}*/

		mCommandQueue.push_back(pCommand);	
		return true;
	}
	return false;
}
Command* CommandCache::popCommand()
{
	if(!isEmpty())
	{
		Command* pCommand = mCommandQueue.front();
		mCommandQueue.pop_front();
		return pCommand;
	}
	return NULL;
}
bool CommandCache::clearCommand()
{

		while(!mCommandQueue.empty())
		{
			Command* pCommand=mCommandQueue.front();
			if(pCommand)
				OGRE_DELETE pCommand;
			mCommandQueue.pop_front();			
		}


	return true;
}
unsigned int CommandCache::getCommandNum()
{
	return mCommandQueue.size();
}
bool CommandCache::setCommandCompleteTime(unsigned int TimeSec)
{
	mCompleteTime = TimeSec;
	return true;
}
int	CommandCache::getExecuteNumPerFrame()
{
	//测试，输出当前所有命令
	return mCommandQueue.size();
	int newCommandNum = mCommandQueue.size();
	if(mOldRemanentCommandNum < newCommandNum)//剩余命令序列在mCompleteTime时间内完成
	{
		mOldRemanentCommandNum = newCommandNum;
		float executeFrameNum = 60 ;
		mExecuteNumPerFrame = mOldRemanentCommandNum/executeFrameNum;
		mExecuteNumPerFrame = mExecuteNumPerFrame > 0 ? mExecuteNumPerFrame : 1;
	}
	mOldRemanentCommandNum-=mExecuteNumPerFrame;//减去本帧执行的命令数
	//测试，添加输出log
	//{
	//	static int FrameIndex = 0 ;
	//	char header[256]={0,0};
	//	sprintf(header,"CacheId=%d,FrameIndex=%d,OldRemanentCommandNum=%d,mExecuteNumPerFrame=%d",mCacheId,FrameIndex,mOldRemanentCommandNum,mExecuteNumPerFrame);
	//	String Msg(header);		
	//	WARNING_LOG(Msg,Ogre::LML_TRIVIAL);
	//	FrameIndex++;
	//}
	return mExecuteNumPerFrame;
}
/*
CommandResultEnum CommandCache::executeOneFrame()
{	
	if(isEmpty())
	{
		return CRE_NO_COMMAND; 
	}
	return executeCommandCache(getExecuteNumPerFrame());
}
*/
CommandResultEnum CommandCache::executeCommandCache(unsigned int exeComNum)
{
	if(isEmpty())
		return CRE_NO_COMMAND; 
	CommandResultEnum result = CRE_SUCCESS;
	int executeIndex = 0;
	while(!mCommandQueue.empty())
	{
		Command* pCommand = 0;
			pCommand = mCommandQueue.front();

		assert(pCommand);
		std::string cmdString;
		
		    cmdString = pCommand->getCommandString();
			result= pCommand->execute();
			++executeIndex;
			if(result==CRE_BLOCK)//阻塞队列		
			{
				if (pCommand->getWaitTime() > 1000 * 20)
				{
					//test only
#ifdef _ENABLE_TIME_LOG_
					//char Msg[1024];
					//sprintf(Msg,"CommandCache::executeCommandCache, The wait time is too long!, Command Cache Id=%d command=%s execute.\n",mCacheId, pCommand->getCommandString().c_str());
					//::OutputDebugString(Msg);					
#endif

					//end
				}

				if (pCommand->getBlockTime() > 10*1000)
				{
					//test only
#ifdef _ENABLE_TIME_LOG_
					char Msg[1024];
					sprintf(Msg,"CommandCache::executeCommandCache, The block time is too long!, Command Cache Id=%d command=%s execute Failed.\n",mCacheId, pCommand->getCommandString().c_str());
					//WARNING_LOG(Msg,Ogre::LML_TRIVIAL);

					::OutputDebugString(Msg);
#endif
					//end
				}
				return result;		
			}
			//执行失败，写log
			if(result==CRE_FAILED)
			{
				WARNING_LOG("Command Cache Id=%d command=%s execute Failed.", mCacheId, pCommand->getCommandString().c_str());
			}
	
	
			OGRE_DELETE pCommand;


			mCommandQueue.pop_front();

		if(executeIndex>=exeComNum)//执行指定个数命令		
			return result;					
	}
	return result;
}

CommandCacheManager* CommandCacheManager::getSingletonPtr(void)
{
	//assert(ms_Singleton);  
	return	(msSingleton);
}
CommandCacheManager& CommandCacheManager::getSingleton(void)
{ 
	assert(msSingleton);
	return (*msSingleton);
}
bool CommandCacheManager::frameStarted(const Ogre::FrameEvent& evt)
{
	return true;
}
bool CommandCacheManager::frameEnded(const Ogre::FrameEvent& evt)
{
	executeOneFrame();
	return true;
}
//实现函数
CommandCacheManager::CommandCacheManager(void):mCommandCacheId(0)
{
	init();
}
CommandCacheManager::~CommandCacheManager(void)
{
	destroy();
}
bool CommandCacheManager::init()
{	
	//侦听器,用于执行命令序列
	if(Ogre::Root::getSingletonPtr())
	{
		Ogre::Root::getSingletonPtr()->addFrameListener(this);
	}
	return true;
}
bool CommandCacheManager::clear()
{
	if(destroy())
		return init();
	return false;
}
bool CommandCacheManager::destroy()
{
	//删除所有command序列
	CommandCacheMapIterator itCommandCache = mCommandCacheMap.begin();
	while(itCommandCache!=mCommandCacheMap.end())
	{
		itCommandCache->second->clearCommand();
		OGRE_DELETE (itCommandCache->second);
		itCommandCache=mCommandCacheMap.erase(itCommandCache);
	}
	//侦听器,用于执行命令序列
	if(Ogre::Root::getSingletonPtr())
	{
		//Ogre::Root::getSingletonPtr()->removeFrameListener(this);
	}
	return true;
}
//接口函数
unsigned long CommandCacheManager::createCommandCache()
{
	mCommandCacheId++;
	CommandCache* pCommandCache = OGRE_NEW CommandCache(mCommandCacheId);
	mCommandCacheMap.insert(std::make_pair(mCommandCacheId,pCommandCache));
	return mCommandCacheId;
}
bool CommandCacheManager::clearCommandCache(unsigned long CacheHandle)
{
	CommandCacheMapIterator itCommandCache = mCommandCacheMap.find(CacheHandle);
	if(itCommandCache!=mCommandCacheMap.end())
	{
		itCommandCache->second->clearCommand();
		return true;
	}
	return false;
}
bool CommandCacheManager::deleteCommandCache(unsigned long CacheHandle)
{
	CommandCacheMapIterator itCommandCache = mCommandCacheMap.find(CacheHandle);
	if(itCommandCache!=mCommandCacheMap.end())
	{
		itCommandCache->second->clearCommand();
		OGRE_DELETE (itCommandCache->second);
		mCommandCacheMap.erase(itCommandCache);
		return true;
	}
	return false;
}
unsigned long CommandCacheManager::getCommandCacheNum()
{
	return mCommandCacheMap.size();
}
CommandCache* CommandCacheManager::getCommandCache(unsigned long CacheHandle)
{
	CommandCacheMapIterator itCommandCache = mCommandCacheMap.find(CacheHandle);
	if(itCommandCache!=mCommandCacheMap.end())
	{
		return itCommandCache->second;
	}
	return NULL;
}
bool CommandCacheManager::commandCacheisEmpty(unsigned long CacheHandle)
{
	CommandCacheMapIterator itCommandCache = mCommandCacheMap.find(CacheHandle);
	if(itCommandCache!=mCommandCacheMap.end())
	{
		return itCommandCache->second->isEmpty();
	}
	return true;
}
bool CommandCacheManager::pushCommand(unsigned long CacheHandle,Command* pCommand)
{	
	CommandCacheMapIterator itCommandCache = mCommandCacheMap.find(CacheHandle);
	if(itCommandCache!=mCommandCacheMap.end())
	{
		if(pCommand)
		{
			return itCommandCache->second->pushCommand(pCommand);
		}
	}
	return false;
}
Command* CommandCacheManager::popCommand(unsigned long CacheHandle)
{
	CommandCacheMapIterator itCommandCache = mCommandCacheMap.find(CacheHandle);
	if(itCommandCache!=mCommandCacheMap.end())
	{
		return itCommandCache->second->popCommand();		
	}
	return NULL;
}

bool CommandCacheManager::executeOneFrame()
{
	unsigned long startTime = Ogre::Root::getSingletonPtr()->getTimer()->getMilliseconds();
	unsigned long curTime = 0;
	bool executeOverTimeFlag=false;
	CommandCacheMapIterator itCommandCache = mCommandCacheMap.begin();
	while(itCommandCache!=mCommandCacheMap.end())
	{
		int blockTime = itCommandCache->second->getBlockTime();
		if (blockTime <= 0)
		{
			for(unsigned int executeIndex = 0 ; executeIndex != itCommandCache->second->getCommandNum(); ++executeIndex)
			{
				CommandResultEnum ret = itCommandCache->second->executeCommandCache(1);
				if (ret == CRE_BLOCK)
					break;

				curTime = Ogre::Root::getSingletonPtr()->getTimer()->getMilliseconds();
				if ((curTime - startTime) > 10) //超过时间不再继续处理
				{
					//test only output
					/*
					char buf[1024];
					sprintf(buf, "CommandCacheManager::executeOneFrame, executeCommandCache beyond 10 ms,%d\n", itCommandCache->first);
					::OutputDebugString(buf);
					*/
					//end

					executeOverTimeFlag = true;
					break;
				}
			}
		}
		else
		{
			//test only, output
			//char buf[1024];
			//sprintf(buf, "CommandCacheManager::executeOneFrame blocked,%d\n", itCommandCache->first);
			//::OutputDebugString(buf);
			//end

			//curTime = Ogre::Root::getSingletonPtr()->getTimer()->getMilliseconds();
			blockTime -= 1;
			itCommandCache->second->setBlockTime(blockTime);
		}
		if(executeOverTimeFlag)
			break;
		++itCommandCache;
	}
	return true;
}

CommandResultEnum CommandCacheManager::execute(unsigned long CacheHandle,int exeComNum)
{
	CommandCacheMapIterator itCommandCache = mCommandCacheMap.find(CacheHandle);
	if(itCommandCache!=mCommandCacheMap.end())
	{		
		return itCommandCache->second->executeCommandCache(exeComNum);
	}
	return CRE_FAILED;
}


}// namespace