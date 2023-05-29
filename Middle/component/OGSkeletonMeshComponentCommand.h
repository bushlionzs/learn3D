#ifndef OGSkeletonMeshComponentCommand_h__
#define OGSkeletonMeshComponentCommand_h__

#include "OGSkeletonMeshActor.h"
#include "OGCommandManager.h"

#include "OgreQuaternion.h"

#include"OgreRoot.h"
#include"OgreTimer.h"
#include "OGSkeletonMeshComponent.h"
#include "engine_manager.h"


namespace Orphigine 
{
	class CommandCacheFactory;
	class SkeletonMeshActor;
	//基类
	class LogicModelCommand : public Command
	{
	public:
		LogicModelCommand(std::string objName):mObjName(objName)
		{
			mBlockTime = 0; mWaitTime = 0;
			mStartTime = Ogre::Root::getSingletonPtr()->getTimer()->getMilliseconds();
		}
		virtual ~LogicModelCommand(){}
		virtual CommandResultEnum execute()=0;
		virtual std::string getCommandString()=0;
		virtual unsigned long getBlockTime() {return mBlockTime;}
		virtual unsigned long getWaitTime() {return mWaitTime;}
		virtual int getCommandType() {return CMD_T_NORMAL;}
	protected:
		std::string		mObjName;
		uint64_t   mBlockTime;
		uint64_t   mWaitTime;
		uint64_t   mStartTime;		
	private:
	};	
	//派生类，每个命令一个子类，当前共34个命令
	class LMsetLogicModelName2Command : public LogicModelCommand
	{
	public:
		LMsetLogicModelName2Command(std::string objName,std::string modelName,bool loadResFlag):LogicModelCommand(objName),
			mModelName(modelName),mLoadResFlag(loadResFlag)
		{			
			
		}
		virtual ~LMsetLogicModelName2Command(){}

		CommandResultEnum execute();
		
		std::string getCommandString() {
			char buf[2048];
			sprintf(buf, "setLogicModelName2, modelName:%s, objName:%s, waitTime:%lldd, blockTime:%lld\n", mModelName.c_str(), mObjName.c_str(), mWaitTime, mBlockTime);
			std::string cmdString = buf;
			return cmdString; 
		}
		virtual int getCommandType() {return CMD_T_setLogicModelName2;}
	public:
		std::string getModelName() {return mModelName;}
	private:
		LMsetLogicModelName2Command();
		std::string		mModelName;
		bool			mLoadResFlag;
		
	};
	class LMsetVisibleCommand : public LogicModelCommand
	{
	public:
		LMsetVisibleCommand(std::string objName,bool visible):LogicModelCommand(objName),mVisible(visible) {}
		virtual ~LMsetVisibleCommand(){}
		CommandResultEnum execute()
		{
			SkeletonMeshActor* pLogicModelObject = (Orphigine::SkeletonMeshActor*)EngineManager::getSingletonPtr()->getRegisterObject(mObjName);
			if(pLogicModelObject && pLogicModelObject->getLogicModel())
			{
				pLogicModelObject->getLogicModel()->setVisible(mVisible);
				return CRE_SUCCESS;					
			}
			return CRE_FAILED;
		}
		std::string getCommandString() { return "setVisible"; }
	private:
		LMsetVisibleCommand();
		bool	mVisible;
	};
	class LMchangeAttribute2Command : public LogicModelCommand
	{
	public:
		LMchangeAttribute2Command(std::string objName,const String &name, const String &value,bool LoadResFlag):LogicModelCommand(objName),
			mName(name),mValue(value),mLoadResFlag(LoadResFlag){}
			virtual ~LMchangeAttribute2Command(){}
			CommandResultEnum execute()
			{
				SkeletonMeshActor* pLogicModelObject = (Orphigine::SkeletonMeshActor*)EngineManager::getSingletonPtr()->getRegisterObject(mObjName);
				if(pLogicModelObject)
				{
					if(pLogicModelObject->mIsLoadingResFlag)//正在加载资源，阻塞队列
					{
						mWaitTime = Ogre::Root::getSingletonPtr()->getTimer()->getMilliseconds() - mStartTime;
						return CRE_BLOCK;
					}
					
					if (mWaitTime > 0)
					{
						mWaitTime = 0;
						mStartTime = Ogre::Root::getSingletonPtr()->getTimer()->getMilliseconds();
					}					
					if(pLogicModelObject->changeAttribute2(mName,mValue,mLoadResFlag))//失败表示阻塞队列
						return CRE_SUCCESS;	
					else
					{
						mBlockTime = Ogre::Root::getSingletonPtr()->getTimer()->getMilliseconds() - mStartTime;
						return CRE_BLOCK;
					}
				}
				return CRE_FAILED;
			}
			std::string getCommandString() { return "changeAttribute2"; }
	private:
		LMchangeAttribute2Command();
		String		mName;
		String		mValue;
		bool		mLoadResFlag;
	};
	class LMchangeAttributes2Command : public LogicModelCommand
	{
	public:
		LMchangeAttributes2Command(std::string objName,const std::vector<String> &names, const std::vector<String> &values,bool LoadResFlag):LogicModelCommand(objName),
			mNames(names),mValues(values),mLoadResFlag(LoadResFlag){}
			virtual ~LMchangeAttributes2Command(){}
			CommandResultEnum execute()
			{
				SkeletonMeshActor* pLogicModelObject = (Orphigine::SkeletonMeshActor*)EngineManager::getSingletonPtr()->getRegisterObject(mObjName);
				if(pLogicModelObject)
				{
					if(pLogicModelObject->mIsLoadingResFlag)//正在加载资源，阻塞队列
					{
						mWaitTime = Ogre::Root::getSingletonPtr()->getTimer()->getMilliseconds() - mStartTime;
						return CRE_BLOCK;
					}
					
					if (mWaitTime > 0)
					{
						mWaitTime = 0;
						mStartTime = Ogre::Root::getSingletonPtr()->getTimer()->getMilliseconds();
					}	

					if(pLogicModelObject->changeAttributes2(mNames,mValues,mLoadResFlag))//失败表示阻塞队列
						return CRE_SUCCESS;	
					else
					{
						mBlockTime = Ogre::Root::getSingletonPtr()->getTimer()->getMilliseconds() - mStartTime;
						return CRE_BLOCK;
					}
				}
				return CRE_FAILED;
			}
			std::string getCommandString() { return "changeAttributes2"; }
			
	private:
		LMchangeAttributes2Command();
		std::vector<String>		mNames;
		std::vector<String>		mValues;
		bool					mLoadResFlag;	
	};
	class LMsetAASMonitoringDegreeCommand : public LogicModelCommand
	{
	public:
		LMsetAASMonitoringDegreeCommand(std::string objName,SkeletonMeshComponent::AdvancedAnimationSystemMonitoringDegree monitoringDegreeType,Real degree):LogicModelCommand(objName),mMonitoringDegreeType(monitoringDegreeType),mDegree(degree) {}
		virtual ~LMsetAASMonitoringDegreeCommand(){}
		CommandResultEnum execute()
		{
			SkeletonMeshActor* pLogicModelObject = (Orphigine::SkeletonMeshActor*)EngineManager::getSingletonPtr()->getRegisterObject(mObjName);
			if(pLogicModelObject && pLogicModelObject->getLogicModel())
			{
				pLogicModelObject->getLogicModel()->setAASMonitoringDegree(mMonitoringDegreeType,mDegree);
				return CRE_SUCCESS;	
			}
			return CRE_FAILED;
		}
		std::string getCommandString() { return "setAASMonitoringDegree"; }
	private:
		LMsetAASMonitoringDegreeCommand();
		SkeletonMeshComponent::AdvancedAnimationSystemMonitoringDegree mMonitoringDegreeType;
		Real												mDegree;
	};
	class LMcreateSkillCommand : public LogicModelCommand
	{
	public:
		LMcreateSkillCommand(std::string objName,const String& skillName, const Ogre::Quaternion &rot, int nAnimFlag,bool loop,bool anim,Ogre::Real delayTime, int priority):
		  LogicModelCommand(objName),mTemplateSkillName(skillName),mNAnimFlag(nAnimFlag),mLoop(loop),mAnim(anim),mDelayTime(delayTime), mPriority(priority), mRot(rot) {}
		  virtual ~LMcreateSkillCommand(){}
		  CommandResultEnum execute()
		  {
			  SkeletonMeshActor* pLogicModelObject = (Orphigine::SkeletonMeshActor*)EngineManager::getSingletonPtr()->getRegisterObject(mObjName);
			  if(pLogicModelObject && pLogicModelObject->getLogicModel())
			  {
				  pLogicModelObject->getLogicModel()->createSkill(mTemplateSkillName, mRot, mNAnimFlag,mLoop,mAnim,mDelayTime,mPriority);
				  return CRE_SUCCESS;	
			  }
			  return CRE_FAILED;

		  }
		  std::string getCommandString() { return "createSkill"; }
	private:
		LMcreateSkillCommand();
		String				mTemplateSkillName;
		int					mNAnimFlag;
		bool				mLoop;
		bool				mAnim;
		Ogre::Real			mDelayTime;
		Ogre::Quaternion    mRot;
		int                 mPriority;
	};
	class LMsetGlobalAnimationRateCommand : public LogicModelCommand
	{
	public:
		LMsetGlobalAnimationRateCommand(std::string objName,Real rate):LogicModelCommand(objName),mRate(rate) {}
		virtual ~LMsetGlobalAnimationRateCommand(){}
		CommandResultEnum execute()
		{	
			SkeletonMeshActor* pLogicModelObject = (Orphigine::SkeletonMeshActor*)EngineManager::getSingletonPtr()->getRegisterObject(mObjName);
			if(pLogicModelObject && pLogicModelObject->getLogicModel())
			{
				pLogicModelObject->getLogicModel()->setGlobalAnimationRate(mRate);
				return CRE_SUCCESS;	
			}
			return CRE_FAILED;
		}
		std::string getCommandString() { return "setGlobalAnimationRate"; }
	private:
		LMsetGlobalAnimationRateCommand();
		Real				mRate;
	};
	class LMsetTransparentCommand : public LogicModelCommand
	{
	public:
		LMsetTransparentCommand(std::string objName,Real time, Real transparency):LogicModelCommand(objName),mTime(time),mTransparency(transparency){}
		virtual ~LMsetTransparentCommand(){}
		CommandResultEnum execute()
		{
			SkeletonMeshActor* pLogicModelObject = (Orphigine::SkeletonMeshActor*)EngineManager::getSingletonPtr()->getRegisterObject(mObjName);
			if(pLogicModelObject && pLogicModelObject->getLogicModel())
			{
				pLogicModelObject->getLogicModel()->setTransparent(mTime,mTransparency);
				return CRE_SUCCESS;	
			}
			return CRE_FAILED;
		}
		std::string getCommandString() { return "setTransparent"; }
	private:
		LMsetTransparentCommand();
		Real mTime;
		Real mTransparency;
	};
	class LMaddEffectCommand : public LogicModelCommand
	{
	public:
		LMaddEffectCommand(std::string objName,const String& effectName, const String& locatorName,SkeletonMeshComponent::GetTransformInfoType transformType,
			const Ogre::ColourValue& colour,Ogre::String name, int priority):LogicModelCommand(objName),mEffectName(effectName),mLocatorName(locatorName),mTransformType(transformType),
			mColour(colour),mName(name), mPriority(priority){}
			virtual ~LMaddEffectCommand(){}
			CommandResultEnum execute()
			{
				SkeletonMeshActor* pLogicModelObject = (Orphigine::SkeletonMeshActor*)EngineManager::getSingletonPtr()->getRegisterObject(mObjName);
				if(pLogicModelObject && pLogicModelObject->getLogicModel())
				{
					pLogicModelObject->getLogicModel()->addEffect(mEffectName,mLocatorName,mTransformType,mColour,mName.c_str(),mPriority);
					return CRE_SUCCESS;	
				}
				return CRE_FAILED;
			}
			std::string getCommandString() { return "addEffect"; }
	private:
		LMaddEffectCommand();
		String								mEffectName;
		String								mLocatorName; 
		SkeletonMeshComponent::GetTransformInfoType	mTransformType;
		Ogre::ColourValue					mColour;
		Ogre::String						mName;
		int									mPriority;
	};
	class LMdelEffectCommand : public LogicModelCommand
	{
	public:
		LMdelEffectCommand(std::string objName,Ogre::String name):LogicModelCommand(objName),mName(name){}
		virtual ~LMdelEffectCommand(){}
		CommandResultEnum execute()
		{		
			SkeletonMeshActor* pLogicModelObject = (Orphigine::SkeletonMeshActor*)EngineManager::getSingletonPtr()->getRegisterObject(mObjName);
			if(pLogicModelObject && pLogicModelObject->getLogicModel())
			{
				if(pLogicModelObject->getLogicModel()->delEffect(mName))
					return CRE_SUCCESS;
				else 
					return CRE_FAILED;
			}
			return CRE_FAILED;
		}
		std::string getCommandString() { return "delEffect"; }
	private:
		LMdelEffectCommand();
		Ogre::String		mName;
	};
	class LMdelAllEffectCommand : public LogicModelCommand
	{
	public:
		LMdelAllEffectCommand(std::string objName):LogicModelCommand(objName){}
		virtual ~LMdelAllEffectCommand(){}
		CommandResultEnum execute()
		{
			SkeletonMeshActor* pLogicModelObject = (Orphigine::SkeletonMeshActor*)EngineManager::getSingletonPtr()->getRegisterObject(mObjName);
			if(pLogicModelObject && pLogicModelObject->getLogicModel())
			{
				pLogicModelObject->getLogicModel()->delAllEffect();
				return CRE_SUCCESS;	
			}
			return CRE_FAILED;
		}
		std::string getCommandString() { return "delAllEffect"; }
	};
	class LMsetHairColourCommand : public LogicModelCommand
	{
	public:
		LMsetHairColourCommand(std::string objName,const Ogre::ColourValue& colour):LogicModelCommand(objName),mColour(colour){}
		virtual ~LMsetHairColourCommand(){}
		CommandResultEnum execute()
		{
			SkeletonMeshActor* pLogicModelObject = (Orphigine::SkeletonMeshActor*)EngineManager::getSingletonPtr()->getRegisterObject(mObjName);
			if(pLogicModelObject)
			{
				pLogicModelObject->getLogicModel()->setHairColour(mColour);
				return CRE_SUCCESS;		
			}
			return CRE_FAILED;
		}
		std::string getCommandString() { return "setHairColour"; }
	private:
		LMsetHairColourCommand();
		Ogre::ColourValue			mColour;
	};
	class LMsetAASAnimPlayCallbackCommand : public LogicModelCommand
	{
	public:
		LMsetAASAnimPlayCallbackCommand(std::string objName,SkeletonMeshComponent::AASAnimPlayCallback* callback,unsigned long info):LogicModelCommand(objName),mCallback(callback),mInfo(info){}
		virtual ~LMsetAASAnimPlayCallbackCommand(){}
		CommandResultEnum execute()
		{
			SkeletonMeshActor* pLogicModelObject = (Orphigine::SkeletonMeshActor*)EngineManager::getSingletonPtr()->getRegisterObject(mObjName);
			if(pLogicModelObject && pLogicModelObject->getLogicModel())
			{
				pLogicModelObject->getLogicModel()->setAASAnimPlayCallback(mCallback,mInfo);
				return CRE_SUCCESS;	
			}
			return CRE_FAILED;
		}
		std::string getCommandString() { return "setAASAnimPlayCallback"; }
	private:
		LMsetAASAnimPlayCallbackCommand();
		SkeletonMeshComponent::AASAnimPlayCallback*	mCallback;
		unsigned long						mInfo;
	};
	class LMsetAASAnimEndCallbackCommand : public LogicModelCommand
	{
	public:
		LMsetAASAnimEndCallbackCommand(std::string objName,SkeletonMeshComponent::AASAnimEndCallback* callback,unsigned long info):LogicModelCommand(objName),mCallback(callback),mInfo(info){}
		virtual ~LMsetAASAnimEndCallbackCommand(){}
		CommandResultEnum execute()
		{
			SkeletonMeshActor* pLogicModelObject = (Orphigine::SkeletonMeshActor*)EngineManager::getSingletonPtr()->getRegisterObject(mObjName);
			if(pLogicModelObject && pLogicModelObject->getLogicModel())
			{
				pLogicModelObject->getLogicModel()->setAASAnimEndCallback(mCallback,mInfo);
				return CRE_SUCCESS;	
			}
			return CRE_FAILED;
		}
		std::string getCommandString() { return "setAASAnimEndCallback"; }
	private:
		LMsetAASAnimEndCallbackCommand();
		SkeletonMeshComponent::AASAnimEndCallback*	mCallback;
		unsigned long						mInfo;
	};		
	class LMSetSkillBreakTimeListenerCommand : public LogicModelCommand
	{
	public:
		LMSetSkillBreakTimeListenerCommand(std::string objName,OnSkillBreakTime func, ulong info):LogicModelCommand(objName),mFunc(func),mInfo(info){}
		virtual ~LMSetSkillBreakTimeListenerCommand(){}
		CommandResultEnum execute()
		{
			SkeletonMeshActor* pLogicModelObject = (Orphigine::SkeletonMeshActor*)EngineManager::getSingletonPtr()->getRegisterObject(mObjName);
			if(pLogicModelObject && pLogicModelObject->getLogicModel())
			{
				pLogicModelObject->getLogicModel()->SetSkillBreakTimeListener(mFunc,mInfo);
				return CRE_SUCCESS;	
			}
			return CRE_FAILED;
		}
		std::string getCommandString() { return "SetSkillBreakTimeListener"; }
	private:
		LMSetSkillBreakTimeListenerCommand();
		OnSkillBreakTime						mFunc; 
		ulong									mInfo;
	};
	class LMSetSkillHitTimeListenerCommand : public LogicModelCommand
	{
	public:
		LMSetSkillHitTimeListenerCommand(std::string objName,OnSkillHitTime func, unsigned long info):LogicModelCommand(objName),mFunc(func),mInfo(info){}
		virtual ~LMSetSkillHitTimeListenerCommand(){}
		CommandResultEnum execute()
		{
			SkeletonMeshActor* pLogicModelObject = (Orphigine::SkeletonMeshActor*)EngineManager::getSingletonPtr()->getRegisterObject(mObjName);
			if(pLogicModelObject && pLogicModelObject->getLogicModel())
			{
				pLogicModelObject->getLogicModel()->SetSkillHitTimeListener(mFunc,mInfo);
				return CRE_SUCCESS;		
			}
			return CRE_FAILED;
		}
		std::string getCommandString() { return "SetSkillHitTimeListener"; }
	private:
		LMSetSkillHitTimeListenerCommand();
		OnSkillHitTime						mFunc; 
		ulong								mInfo;
	};
	class LMSetSkillShakeTimeListenerCommand : public LogicModelCommand
	{
	public:
		LMSetSkillShakeTimeListenerCommand(std::string objName,OnSkillShakeTime func, ulong info):LogicModelCommand(objName),mFunc(func),mInfo(info){}
		virtual ~LMSetSkillShakeTimeListenerCommand(){}
		CommandResultEnum execute()
		{
			SkeletonMeshActor* pLogicModelObject = (Orphigine::SkeletonMeshActor*)EngineManager::getSingletonPtr()->getRegisterObject(mObjName);
			if(pLogicModelObject && pLogicModelObject->getLogicModel())
			{
				pLogicModelObject->getLogicModel()->SetSkillShakeTimeListener(mFunc,mInfo);
				return CRE_SUCCESS;
			}
			return CRE_FAILED;
		}
		std::string getCommandString() { return "SetSkillShakeTimeListener"; }
	private:
		LMSetSkillShakeTimeListenerCommand();
		OnSkillShakeTime					mFunc; 
		ulong								mInfo;
	};
	class LMaddProjectorCommand : public LogicModelCommand
	{
	public:
		LMaddProjectorCommand(std::string objName,ModelProjectorType type,const String& projectorEffectName,bool show,float projectorSize)
			:LogicModelCommand(objName),mType(type),mProjectorEffectName(projectorEffectName),mShow(show),mProjectorSize(projectorSize){}
			virtual ~LMaddProjectorCommand(){}
			CommandResultEnum execute()
			{
				SkeletonMeshActor* pLogicModelObject = (Orphigine::SkeletonMeshActor*)EngineManager::getSingletonPtr()->getRegisterObject(mObjName);
				if(pLogicModelObject && pLogicModelObject->getLogicModel())
				{
					pLogicModelObject->getLogicModel()->addProjector(mType,mProjectorEffectName,mShow,mProjectorSize);
					return CRE_SUCCESS;
				}
				return CRE_FAILED;
			}
			std::string getCommandString() { return "addProjector"; }
	private:
		LMaddProjectorCommand();
		ModelProjectorType				mType;
		String							mProjectorEffectName;
		bool							mShow;
		float							mProjectorSize;
	};
	class LMremoveProjectorCommand : public LogicModelCommand
	{
	public:
		LMremoveProjectorCommand(std::string objName,ModelProjectorType type, const String& projectorEffectName):LogicModelCommand(objName),mType(type),mProjectorEffectName(projectorEffectName){}
		virtual ~LMremoveProjectorCommand(){}
		CommandResultEnum execute()
		{
			SkeletonMeshActor* pLogicModelObject = (Orphigine::SkeletonMeshActor*)EngineManager::getSingletonPtr()->getRegisterObject(mObjName);
			if(pLogicModelObject && pLogicModelObject->getLogicModel())
			{
				pLogicModelObject->getLogicModel()->removeProjector(mType,mProjectorEffectName);
				return CRE_SUCCESS;
			}
			return CRE_FAILED;
		}
		std::string getCommandString() { return "removeProjector"; }
	private:
		LMremoveProjectorCommand();
		ModelProjectorType	mType;
		String				mProjectorEffectName;
	};
	class LMattachModelCommand : public LogicModelCommand
	{
	public:
		LMattachModelCommand(std::string objName,const String& locatorName, String modelObjName):LogicModelCommand(objName),mLocatorName(locatorName),mModelObjName(modelObjName){ }
		virtual ~LMattachModelCommand(){}
		CommandResultEnum execute()
		{
			SkeletonMeshActor* pLogicModelObject = (Orphigine::SkeletonMeshActor*)EngineManager::getSingletonPtr()->getRegisterObject(mObjName);
			if(pLogicModelObject && pLogicModelObject->getLogicModel())
			{
				//查找对应的LogicModelObject
				SkeletonMeshActor* pObj = (SkeletonMeshActor*)EngineManager::getSingleton().getRegisterObject(mModelObjName);
				//人和马的命令序列存在前后依赖关系(马的attachModel命令必须在人的setPosition命令后执行)，这里必须阻塞等待人的命令序列执行完毕
				//if(pObj && Orphigine::CommandCacheManager::getSingleton().commandCacheisEmpty(pObj->mCommandCacheHandle))
				if(pObj && pObj->getLogicModel())
				{
					//执行之前，给人设置位置(因为马的attachModel命令必须在人的setPosition命令后执行)
					//pObj->getLogicModel()->setPosition(pObj->getModelPosition());
					pLogicModelObject->getLogicModel()->attachModel(mLocatorName,pObj->getLogicModel());	
					return CRE_SUCCESS;
				}
			}
			//如果执行失败的话，阻塞队列
			return CRE_FAILED;			
			//return CRE_BLOCK;			
		}
		std::string getCommandString() { return "attachModel"; }
	private:
		LMattachModelCommand();
		String					mLocatorName;
		String					mModelObjName;	//保存LogicModel对应的Object的名称
	};
	class LMdetachModelCommand : public LogicModelCommand
	{
	public:
		LMdetachModelCommand(std::string objName,String modelObjName):LogicModelCommand(objName),mModelObjName(modelObjName){}
		virtual ~LMdetachModelCommand(){}
		CommandResultEnum execute()
		{
			SkeletonMeshActor* pLogicModelObject = (Orphigine::SkeletonMeshActor*)EngineManager::getSingletonPtr()->getRegisterObject(mObjName);
			if(pLogicModelObject && pLogicModelObject->getLogicModel())
			{
				//查找对应的LogicModelObject
				SkeletonMeshActor* pObj = (SkeletonMeshActor*)EngineManager::getSingleton().getRegisterObject(mModelObjName);
				//人和马的命令序列存在前后依赖关系(马的detachModel命令必须在人的setPosition命令后执行)，这里必须阻塞等待人的命令序列执行完毕
				//if(pObj && Orphigine::CommandCacheManager::getSingleton().commandCacheisEmpty(pObj->mCommandCacheHandle))
				if(pObj && pObj->getLogicModel())
				{
					//执行之前，给人设置位置(因为马的detachModel命令必须在人的setPosition命令后执行)
					//pObj->getLogicModel()->setPosition(pObj->getModelPosition());
					pLogicModelObject->getLogicModel()->detachModel(pObj->getLogicModel());
					return CRE_SUCCESS;
				}
			}
			//如果执行失败的话，阻塞队列(测试)
			return CRE_FAILED;			
			//return CRE_BLOCK;			
		}
		std::string getCommandString() { return "detachModel"; }
	private:
		LMdetachModelCommand();
		String			mModelObjName;	//保存LogicModel对应的Object的名称
	};
	class LMsetVisibleFlagCommand : public LogicModelCommand
	{
	public:
		LMsetVisibleFlagCommand(std::string objName,uint32 flags):LogicModelCommand(objName),mFlags(flags){ }
		virtual ~LMsetVisibleFlagCommand(){}
		CommandResultEnum execute()
		{
			SkeletonMeshActor* pLogicModelObject = (Orphigine::SkeletonMeshActor*)EngineManager::getSingletonPtr()->getRegisterObject(mObjName);
			if(pLogicModelObject && pLogicModelObject->getLogicModel())
			{
				pLogicModelObject->getLogicModel()->setVisibleFlag(mFlags);
				return CRE_SUCCESS;
			}
			return CRE_FAILED;
		}
		std::string getCommandString() { return "setVisibleFlag"; }
	private:
		LMsetVisibleFlagCommand();
		uint32					mFlags;
	};
	class LMsetPositionCommand : public LogicModelCommand
	{
	public:
		LMsetPositionCommand(std::string objName,Ogre::Vector3& pos):LogicModelCommand(objName),mPos(pos) {}
		virtual ~LMsetPositionCommand(){}
		CommandResultEnum execute()
		{
			SkeletonMeshActor* pLogicModelObject = (Orphigine::SkeletonMeshActor*)EngineManager::getSingletonPtr()->getRegisterObject(mObjName);
			if(pLogicModelObject && pLogicModelObject->getLogicModel())
			{
				pLogicModelObject->getLogicModel()->setPosition(mPos);
				return CRE_SUCCESS;
			}
			return CRE_FAILED;
		}
		std::string getCommandString() { return "setPosition"; }
	private:
		LMsetPositionCommand();
		Ogre::Vector3			mPos;
	};
	class LMsetOrientationCommand : public LogicModelCommand
	{
	public:
		LMsetOrientationCommand(std::string objName,Ogre::Quaternion& orientation):LogicModelCommand(objName),mOrientation(orientation) {}
		virtual ~LMsetOrientationCommand(){}
		CommandResultEnum execute()
		{
			SkeletonMeshActor* pLogicModelObject = (Orphigine::SkeletonMeshActor*)EngineManager::getSingletonPtr()->getRegisterObject(mObjName);
			if(pLogicModelObject && pLogicModelObject->getLogicModel())
			{
				pLogicModelObject->getLogicModel()->setOrientation(mOrientation);
				return CRE_SUCCESS;
			}
			return CRE_FAILED;
		}
		std::string getCommandString() { return "setOrientation"; }
	private:
		LMsetOrientationCommand();
		Ogre::Quaternion		mOrientation;
	};
	class LMsetSelectedCommand : public LogicModelCommand
	{
	public:
		LMsetSelectedCommand(std::string objName,bool selected):LogicModelCommand(objName),mSelected(selected){}
		virtual ~LMsetSelectedCommand(){}
		CommandResultEnum execute()
		{
			SkeletonMeshActor* pLogicModelObject = (Orphigine::SkeletonMeshActor*)EngineManager::getSingletonPtr()->getRegisterObject(mObjName);
			if(pLogicModelObject && pLogicModelObject->getLogicModel())
			{
				pLogicModelObject->getLogicModel()->setSelected(mSelected);
				return CRE_SUCCESS;
			}
			return CRE_FAILED;
		}
		std::string getCommandString() { return "setSelected"; }
	private:
		LMsetSelectedCommand();
		bool			mSelected;
	};
	class LMsetScaleFactorCommand : public LogicModelCommand
	{
	public:
		LMsetScaleFactorCommand(std::string objName,const Ogre::Vector3& scaleFactor):LogicModelCommand(objName),mScaleFactor(scaleFactor){}
		virtual ~LMsetScaleFactorCommand(){}
		CommandResultEnum execute()
		{
			SkeletonMeshActor* pLogicModelObject = (Orphigine::SkeletonMeshActor*)EngineManager::getSingletonPtr()->getRegisterObject(mObjName);
			if(pLogicModelObject && pLogicModelObject->getLogicModel())
			{
				pLogicModelObject->getLogicModel()->setScaleFactor(mScaleFactor);
				return CRE_SUCCESS;
			}
			return CRE_FAILED;
		}
		std::string getCommandString() { return "setScaleFactor"; }
	private:
		LMsetScaleFactorCommand();
		Ogre::Vector3			mScaleFactor;
	};
	class LMsetWeaponTypeNameCommand : public LogicModelCommand
	{
	public:
		LMsetWeaponTypeNameCommand(std::string objName,const String& typeName):LogicModelCommand(objName),mTypeName(typeName) {}
		virtual ~LMsetWeaponTypeNameCommand(){}
		CommandResultEnum execute()
		{
			SkeletonMeshActor* pLogicModelObject = (Orphigine::SkeletonMeshActor*)EngineManager::getSingletonPtr()->getRegisterObject(mObjName);
			if(pLogicModelObject && pLogicModelObject->getLogicModel())
			{
				pLogicModelObject->getLogicModel()->setWeaponTypeName(mTypeName);
				return CRE_SUCCESS;
			}
			return CRE_FAILED;
		}
		std::string getCommandString() { return "setWeaponTypeName"; }
	private:
		LMsetWeaponTypeNameCommand();
		String						mTypeName;
	};

	class LMdelCurrentSkillCommand : public LogicModelCommand
	{
	public:
		LMdelCurrentSkillCommand(std::string objName):LogicModelCommand(objName){}
		virtual ~LMdelCurrentSkillCommand(){}
		CommandResultEnum execute()
		{
			SkeletonMeshActor* pLogicModelObject = (Orphigine::SkeletonMeshActor*)EngineManager::getSingletonPtr()->getRegisterObject(mObjName);
			if(pLogicModelObject && pLogicModelObject->getLogicModel())
			{
				pLogicModelObject->getLogicModel()->delCurrentSkill();
				return CRE_SUCCESS;
			}
			return CRE_FAILED;
		}
		std::string getCommandString() { return "delCurrentSkill"; }
	};
	class LMsetMoodAnimNameCommand : public LogicModelCommand
	{
	public:
		LMsetMoodAnimNameCommand(std::string objName,const String& name):LogicModelCommand(objName),mName(name) {}
		virtual ~LMsetMoodAnimNameCommand(){}
		CommandResultEnum execute()
		{
			SkeletonMeshActor* pLogicModelObject = (Orphigine::SkeletonMeshActor*)EngineManager::getSingletonPtr()->getRegisterObject(mObjName);
			if(pLogicModelObject && pLogicModelObject->getLogicModel())
			{
				pLogicModelObject->getLogicModel()->setMoodAnimName(mName);
				return CRE_SUCCESS;
			}
			return CRE_FAILED;
		}
		std::string getCommandString() { return "setMoodAnimName"; }
	private:
		LMsetMoodAnimNameCommand();
		String			mName;
	};	
	class LMforceUpdateBoundingBoxCommand : public LogicModelCommand
	{
	public:
		LMforceUpdateBoundingBoxCommand(std::string objName):LogicModelCommand(objName){}
		virtual ~LMforceUpdateBoundingBoxCommand(){}
		CommandResultEnum execute()
		{
			SkeletonMeshActor* pLogicModelObject = (Orphigine::SkeletonMeshActor*)EngineManager::getSingletonPtr()->getRegisterObject(mObjName);
			if(pLogicModelObject && pLogicModelObject->getLogicModel())
			{
				pLogicModelObject->getLogicModel()->forceUpdateBoundingBox();
				return CRE_SUCCESS;	
			}
			return CRE_FAILED;
		}
		std::string getCommandString() { return "forceUpdateBoundingBox"; }
	};

	class LMsetWeaponEffectCommand : public LogicModelCommand
	{
	public:
		LMsetWeaponEffectCommand(std::string objName,std::string EffectName,std::string LocatorName,SkeletonMeshComponent::WeaponEnum WeaponType, int priority):
		  LogicModelCommand(objName),mEffectName(EffectName),mLocatorName(LocatorName),mWeaponType(WeaponType), mPriority(priority) {}
		  virtual ~LMsetWeaponEffectCommand(){}
		  CommandResultEnum execute()
		  {
			  SkeletonMeshActor* pLogicModelObject = (Orphigine::SkeletonMeshActor*)EngineManager::getSingletonPtr()->getRegisterObject(mObjName);
			  if(pLogicModelObject && pLogicModelObject->getLogicModel())
			  {
				  if(pLogicModelObject->getLogicModel()->setWeaponEffect(mEffectName.c_str(),mLocatorName.c_str(),mWeaponType, mPriority))
					  return CRE_SUCCESS;
				  else
					  return CRE_FAILED;
			  }
			  return CRE_FAILED;
		  }
		  std::string getCommandString() { return "setWeaponEffect"; }
	private:
		LMsetWeaponEffectCommand();
		String  				mEffectName;
		String					mLocatorName;
		SkeletonMeshComponent::WeaponEnum  mWeaponType;
		int                     mPriority;
	};

	class LMclearWeaponEffectCommand : public LogicModelCommand
	{
	public:
		LMclearWeaponEffectCommand(std::string objName,SkeletonMeshComponent::WeaponEnum WeaponType):
		  LogicModelCommand(objName),mWeaponType(WeaponType) {}
		  virtual ~LMclearWeaponEffectCommand(){}
		  CommandResultEnum execute()
		  {
			  SkeletonMeshActor* pLogicModelObject = (Orphigine::SkeletonMeshActor*)EngineManager::getSingletonPtr()->getRegisterObject(mObjName);
			  if(pLogicModelObject && pLogicModelObject->getLogicModel())
			  {
				  if(pLogicModelObject->getLogicModel()->clearWeaponEffect(mWeaponType))
					  return CRE_SUCCESS;
				  else 
					  return CRE_FAILED;
			  }
			  return CRE_FAILED;
		  }
		  std::string getCommandString() { return "clearWeaponEffect"; }
	private:
		LMclearWeaponEffectCommand();	
		SkeletonMeshComponent::WeaponEnum  mWeaponType;
	};


	class LMchangeWeaponActionCommand : public LogicModelCommand
	{
	public:
		LMchangeWeaponActionCommand(std::string objName,SkeletonMeshComponent::AdvancedAnimationSystemMonitoringDegree eAction, float fDegree,SkeletonMeshComponent::WeaponEnum WeaponType):
		  LogicModelCommand(objName),mAction(eAction),mDegree(fDegree),mWeaponType(WeaponType) {}
		  virtual ~LMchangeWeaponActionCommand(){}
		  CommandResultEnum execute()
		  {
			  SkeletonMeshActor* pLogicModelObject = (Orphigine::SkeletonMeshActor*)EngineManager::getSingletonPtr()->getRegisterObject(mObjName);
			  if(pLogicModelObject && pLogicModelObject->getLogicModel())
			  {
				  if(pLogicModelObject->getLogicModel()->changeWeaponAction(mAction,mDegree,mWeaponType))
					  return CRE_SUCCESS;
				  else
					  return CRE_FAILED;
			  }
			  return CRE_FAILED;
		  }
		  std::string getCommandString() { return "changeWeaponAction"; }
	private:
		LMchangeWeaponActionCommand();	
		SkeletonMeshComponent::AdvancedAnimationSystemMonitoringDegree mAction;
		float												mDegree;
		SkeletonMeshComponent::WeaponEnum								mWeaponType;
	};


	class LMchangeWeaponActionSpeedCommand : public LogicModelCommand
	{
	public:
		LMchangeWeaponActionSpeedCommand(std::string objName,float fRate,SkeletonMeshComponent::WeaponEnum WeaponType):
		  LogicModelCommand(objName),mRate(fRate),mWeaponType(WeaponType) {}
		  virtual ~LMchangeWeaponActionSpeedCommand(){}
		  CommandResultEnum execute()
		  {
			  SkeletonMeshActor* pLogicModelObject = (Orphigine::SkeletonMeshActor*)EngineManager::getSingletonPtr()->getRegisterObject(mObjName);
			  if(pLogicModelObject && pLogicModelObject->getLogicModel())
			  {
				  if(pLogicModelObject->getLogicModel()->changeWeaponActionSpeed(mRate,mWeaponType))
					  return CRE_SUCCESS;
				  else
					  return CRE_FAILED;
			  }
			  return CRE_FAILED;
		  }
		  std::string getCommandString() { return "changeWeaponActionSpeed"; }
	private:
		LMchangeWeaponActionSpeedCommand();	
		float												mRate;
		SkeletonMeshComponent::WeaponEnum								mWeaponType;
	};

	class LMsetAASGlobalAnimRateCommand : public LogicModelCommand
	{
	public:
		LMsetAASGlobalAnimRateCommand(std::string objName,Real rate):LogicModelCommand(objName),mRate(rate) {}
		virtual ~LMsetAASGlobalAnimRateCommand(){}
		CommandResultEnum execute()
		{
			SkeletonMeshActor* pLogicModelObject = (Orphigine::SkeletonMeshActor*)EngineManager::getSingletonPtr()->getRegisterObject(mObjName);
			if(pLogicModelObject && pLogicModelObject->getLogicModel())
			{
				pLogicModelObject->getLogicModel()->setAASGlobalAnimRate(mRate);
				return CRE_SUCCESS;
			}
			return CRE_FAILED;
		}
		std::string getCommandString() { return "setAASGlobalAnimRate"; }
	private:
		LMsetAASGlobalAnimRateCommand();
		Real				mRate;
	};

	class LMsetSkillRateCommand : public LogicModelCommand
	{
	public:
		LMsetSkillRateCommand(std::string objName,Real rate):LogicModelCommand(objName),mRate(rate) {}
		virtual ~LMsetSkillRateCommand(){}
		CommandResultEnum execute()
		{
			SkeletonMeshActor* pLogicModelObject = (Orphigine::SkeletonMeshActor*)EngineManager::getSingletonPtr()->getRegisterObject(mObjName);
			if(pLogicModelObject && pLogicModelObject->getLogicModel())
			{
				pLogicModelObject->getLogicModel()->setSkillRate(mRate);
				return CRE_SUCCESS;
			}
			return CRE_FAILED;
		}
		std::string getCommandString() { return "setSkillRate"; }
	private:
		LMsetSkillRateCommand();
		Real				mRate;
	};
	class LMsetForceIgnoreAAS : public LogicModelCommand
	{
	public:
		LMsetForceIgnoreAAS(std::string objName,bool val):LogicModelCommand(objName),mValue(val) {}
		virtual ~LMsetForceIgnoreAAS(){}
		CommandResultEnum execute()
		{
			SkeletonMeshActor* pLogicModelObject = (Orphigine::SkeletonMeshActor*)EngineManager::getSingletonPtr()->getRegisterObject(mObjName);
			if(pLogicModelObject && pLogicModelObject->getLogicModel())
			{
				pLogicModelObject->getLogicModel()->setForceIgnoreAAS(mValue);
				return CRE_SUCCESS;
			}
			return CRE_FAILED;
		}
		std::string getCommandString() { return "setForceIgnoreAAS"; }
	private:
		LMsetForceIgnoreAAS();
		bool			mValue;
	};


	class LMsetCommandListFlagListenerCommand : public LogicModelCommand
	{
	public:
		LMsetCommandListFlagListenerCommand(std::string objName,LogicModelCommandListFlagCallback* pLMCLFC,int value1,int value2,int value3):
		  LogicModelCommand(objName),mLMCLFCfun(pLMCLFC),mValue1(value1),mValue2(value2),mValue3(value3) {}
		  virtual ~LMsetCommandListFlagListenerCommand(){}
		  CommandResultEnum execute()
		  {
			  SkeletonMeshActor* pLogicModelObject = (Orphigine::SkeletonMeshActor*)EngineManager::getSingletonPtr()->getRegisterObject(mObjName);
			  if(pLogicModelObject && mLMCLFCfun)
			  {
				  mLMCLFCfun->onLogicModelCommandListFlag(mValue1,mValue2,mValue3);
				  return CRE_SUCCESS;
			  }
			  return CRE_FAILED;
		  }
		  std::string getCommandString() { return "setCommandListFlagListener"; }
	private:
		LMsetCommandListFlagListenerCommand();
		LogicModelCommandListFlagCallback*	mLMCLFCfun;
		int									mValue1;
		int									mValue2;
		int									mValue3;
	};




} // namespace
#endif // OGSkeletonMeshComponentCommand_h__
