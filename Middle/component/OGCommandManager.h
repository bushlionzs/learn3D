#ifndef OGCOMMANDMANAGER_H
#define OGCOMMANDMANAGER_H

#include "OgreSingleton.h"
#include "OgreFrameListener.h"
#include "OGFactory.h"


namespace Orphigine 
{
	enum CommandResultEnum
	{
		CRE_UNKOWN	= 0,
		CRE_NO_COMMAND	= 1,
		CRE_SUCCESS		= 2,
		CRE_FAILED		= 3,
		CRE_BLOCK		= 4,
		CRE_BLOCK_TIMEOUT = 5,
		CRE_FUTURE	= 6
	};
	enum Command_Type
	{
		CMD_T_NORMAL,
		CMD_T_setLogicModelName2,
	};

//基类
class Command
{
public:	
	virtual ~Command(){}
	virtual CommandResultEnum execute()=0;
	//用于测试
	virtual std::string getCommandString()=0;
	virtual unsigned long getBlockTime() {return 0;}
	virtual unsigned long getWaitTime() {return 0;}
	virtual int getCommandType() {return CMD_T_NORMAL;}
protected:
	Command(){}
};

class CommandCache
{
public:
	friend class CommandCacheManager;
	virtual ~CommandCache();
	//接口函数
	unsigned long		getId() { return mCacheId; }
	bool				isEmpty();
	bool				pushCommand(Command* pCommand);
	Command*			popCommand();
	bool				clearCommand();
	unsigned int		getCommandNum();
	bool				setCommandCompleteTime(unsigned int TimeSec=2);//完成的时间，单位为秒
	//virtual CommandResultEnum	executeOneFrame();
	virtual CommandResultEnum	executeCommandCache(unsigned int exeComNum);
	int getBlockTime() {return mBlockTime;}
	void setBlockTime(int time) {mBlockTime = time;}
protected:
	int					getExecuteNumPerFrame();//计算每帧需要执行的命令数
	CommandCache(unsigned long id);
	//typedef std::queue <Command* >		CommandQueue;
	typedef std::deque <Command* >		CommandQueue;
	CommandQueue						mCommandQueue;
	unsigned long						mCacheId;
	unsigned int						mCompleteTime;//完成的时间，单位为秒
	int									mOldRemanentCommandNum;
	int									mExecuteNumPerFrame;
	int									mBlockTime;
};

//管理
class CommandCacheManager : public Ogre::Singleton<CommandCacheManager>,
public Ogre::FrameListener
{
public:	
	CommandCacheManager();
	~CommandCacheManager();
	//继承自Ogre::Singleton的接口(外部可调用)
	static	CommandCacheManager&	getSingleton(void);
	static	CommandCacheManager*	getSingletonPtr(void);
	//继承自Ogre::FrameListener的接口(内部实现)
	virtual bool					frameStarted(const Ogre::FrameEvent& evt);
	virtual bool					frameEnded(const Ogre::FrameEvent& evt);
	//接口函数
	unsigned long	createCommandCache();
	bool			clearCommandCache(unsigned long CacheHandle);
	bool			deleteCommandCache(unsigned long CacheHandle);
	unsigned long	getCommandCacheNum();
	CommandCache*	getCommandCache(unsigned long CacheHandle);
	bool			commandCacheisEmpty(unsigned long CacheHandle);
	bool			pushCommand(unsigned long CacheHandle,Command* pCommand);
	Command*		popCommand(unsigned long CacheHandle);
	CommandResultEnum		execute(unsigned long CacheHandle,int exeComNum);
	bool			init();
	bool			destroy();
protected:
	bool			executeOneFrame();
	bool			clear();
private:
	//key是Id
	typedef std::map<unsigned long,CommandCache*>			CommandCacheMap;
	typedef std::map<unsigned long,CommandCache*>::iterator CommandCacheMapIterator;

	CommandCacheMap									mCommandCacheMap;
	unsigned long									mCommandCacheId;
};

} // namespace

#endif //OGCOMMANDMANAGER_H
