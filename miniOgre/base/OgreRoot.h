#pragma once

#include "OgreSingleton.h"
#include "OgreTimer.h"
#include "engine_struct.h"
#include "OgreFrameListener.h"
class RenderSystem;
#define MAIN_SCENE_MANAGER "__main__"
#define MAIN_CAMERA "__main_camera__"

namespace utils
{
	class JobSystem;
}

namespace Ogre {
	class MovableObjectFactory;

	class Root : public Ogre::Singleton<Root>
	{
	public:
		typedef std::map<String, MovableObjectFactory*> MovableObjectFactoryMap;
	public:
		Root();
		~Root();

		void _initialise();
		RenderSystem* createRenderEngine(
			HWND wnd,
			EngineType et);
		RenderSystem* getRenderSystem();
		void addMovableObjectFactory(MovableObjectFactory* fact,
			bool overrideExisting = false);
		void removeMovableObjectFactory(MovableObjectFactory* fact);
		MovableObjectFactory* getMovableObjectFactory(const String& typeName);

		SceneManager* createSceneManger(const std::string& name);
		void destroySceneManager(SceneManager* sceneMgr);
		SceneManager* getSceneManager(const std::string& name);
		uint64_t getNextFrameNumber();
		uint64_t getCurrentFPS();
		bool _fireFrameStarted();
		bool _fireFrameEnded();
		void addFrameListener(FrameListener* newListener);
		void removeFrameListener(FrameListener* oldListener);
		void _syncAddedRemovedFrameListeners();

		Timer* getTimer(void)
		{
			return &mTimer;
		}

		bool renderOneFrame(void);

		Ogre::FrameEvent& getFrameEvent()
		{
			return mEvt;
		}

		utils::JobSystem* getJobSystem()
		{
			return mJobSystem;
		}
	private:
		uint32_t _allocateNextMovableObjectTypeFlag(void);
	private:
		MovableObjectFactoryMap mMovableObjectFactoryMap;
		uint32 mNextMovableObjectTypeFlag;

		uint64_t mNextFrame;
		uint64_t mCurrentFPS;

		uint64_t mLastFrame;
		double mLast;
		double mAccumulation;
		Timer mTimer;
		std::shared_ptr<RenderSystem> mRenderSystem;
		std::unordered_map<String, SceneManager*> mSceneManagerMap;

		/** Set of registered frame listeners */
		std::set<FrameListener*> mFrameListeners;

		/** Set of frame listeners marked for removal and addition*/
		std::set<FrameListener*> mRemovedFrameListeners;
		std::set<FrameListener*> mAddedFrameListeners;

		uint64_t mFrameCurrent, mFrameLast;

		RenderWindow* mAutoWindow = nullptr;

		Ogre::FrameEvent mEvt;

		utils::JobSystem* mJobSystem;
	};
}