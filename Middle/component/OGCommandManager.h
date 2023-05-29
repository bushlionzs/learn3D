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

//����
class Command
{
public:	
	virtual ~Command(){}
	virtual CommandResultEnum execute()=0;
	//���ڲ���
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
	//�ӿں���
	unsigned long		getId() { return mCacheId; }
	bool				isEmpty();
	bool				pushCommand(Command* pCommand);
	Command*			popCommand();
	bool				clearCommand();
	unsigned int		getCommandNum();
	bool				setCommandCompleteTime(unsigned int TimeSec=2);//��ɵ�ʱ�䣬��λΪ��
	//virtual CommandResultEnum	executeOneFrame();
	virtual CommandResultEnum	executeCommandCache(unsigned int exeComNum);
	int getBlockTime() {return mBlockTime;}
	void setBlockTime(int time) {mBlockTime = time;}
protected:
	int					getExecuteNumPerFrame();//����ÿ֡��Ҫִ�е�������
	CommandCache(unsigned long id);
	//typedef std::queue <Command* >		CommandQueue;
	typedef std::deque <Command* >		CommandQueue;
	CommandQueue						mCommandQueue;
	unsigned long						mCacheId;
	unsigned int						mCompleteTime;//��ɵ�ʱ�䣬��λΪ��
	int									mOldRemanentCommandNum;
	int									mExecuteNumPerFrame;
	int									mBlockTime;
};

//����
class CommandCacheManager : public Ogre::Singleton<CommandCacheManager>,
public Ogre::FrameListener
{
public:	
	CommandCacheManager();
	~CommandCacheManager();
	//�̳���Ogre::Singleton�Ľӿ�(�ⲿ�ɵ���)
	static	CommandCacheManager&	getSingleton(void);
	static	CommandCacheManager*	getSingletonPtr(void);
	//�̳���Ogre::FrameListener�Ľӿ�(�ڲ�ʵ��)
	virtual bool					frameStarted(const Ogre::FrameEvent& evt);
	virtual bool					frameEnded(const Ogre::FrameEvent& evt);
	//�ӿں���
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
	//key��Id
	typedef std::map<unsigned long,CommandCache*>			CommandCacheMap;
	typedef std::map<unsigned long,CommandCache*>::iterator CommandCacheMapIterator;

	CommandCacheMap									mCommandCacheMap;
	unsigned long									mCommandCacheId;
};

} // namespace

#endif //OGCOMMANDMANAGER_H
