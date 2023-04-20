#include "OgreHeader.h"
#include "OGMainSceneLight.h"

#include "OGLightActor.h"

#include <OgreLight.h>
#include <OgreSceneManager.h>
#include <OgreStringConverter.h>
#include <platform_log.h>
#include "engine_manager.h"

namespace Orphigine
{
    //---------------------------------------------------------------------
    MainSceneLight::MainSceneLight(Engine* system) :
    //mSystem(system),
    mMainSceneLightOne(NULL),
    mMainSceneLightTwo(NULL),
    mLastTime(0.0f),
    mFadeInTime(0.0f),
    mCurrentFadeInTime(0.0f),
    mFadeOutTime(0.0f),
    mCurrentFadeOutTime(0.0f),
    mCurrentTime(0.0f),
    mOriginOneLightColour(Ogre::ColourValue::Black),
    mOriginTwoLightColour(Ogre::ColourValue::Black),
    mOriginAmbientColour(Ogre::ColourValue::Black),
    mDestColour(Ogre::ColourValue::Black),
    mLightModifyPhase(LMP_IDLE)
    {
    }
    //---------------------------------------------------------------------
    void MainSceneLight::updateLight(float deltaTime)
    {
		try
		{
			if (mLightModifyPhase != LMP_IDLE)
			{
				if (mMainSceneLightTwo && mMainSceneLightOne)
				{
					mCurrentTime += deltaTime;

					// ÔÚfade in½×¶Î
					if (mCurrentTime < mFadeInTime)
					{     
						mLightModifyPhase = LMP_FADEIN;

						mCurrentFadeInTime += deltaTime;

						if (mCurrentFadeInTime >= mFadeInTime)
						{
							mMainSceneLightOne->setDiffuseColour(mDestColour);
							mMainSceneLightTwo->setDiffuseColour(mDestColour);
							EngineManager::getSingleton().getSceneManager()->setAmbientLight(mDestColour);
						}
						else
						{
							float per = mCurrentFadeInTime / mFadeInTime;

							// light one
							Ogre::ColourValue nowColour = (mDestColour - mOriginOneLightColour) * per +
								mOriginOneLightColour;

							mMainSceneLightOne->setDiffuseColour(nowColour);

							// light two
							nowColour = (mDestColour - mOriginTwoLightColour) * per +
								mOriginTwoLightColour;

							mMainSceneLightTwo->setDiffuseColour(nowColour);

							// ambient
							nowColour = (mDestColour - mOriginAmbientColour) * per +
								mOriginAmbientColour;

							EngineManager::getSingleton().getSceneManager()->setAmbientLight(nowColour);
						}
					}
					// ³ÖÐø½×¶Î
					else if (mCurrentTime >= mFadeInTime && mCurrentTime < mFadeInTime + mLastTime)
					{
						mLightModifyPhase = LMP_LAST;
					}
					// fade out
					else if (mCurrentTime >= mFadeInTime + mLastTime 
						&& mCurrentTime < mFadeInTime + mLastTime + mFadeOutTime)
					{
						mLightModifyPhase = LMP_FADEOUT;

						mCurrentFadeOutTime += deltaTime;

						if (mCurrentFadeOutTime >= mFadeOutTime)
						{
							mMainSceneLightOne->setDiffuseColour(mOriginOneLightColour);
							mMainSceneLightTwo->setDiffuseColour(mOriginTwoLightColour);
							EngineManager::getSingleton().getSceneManager()->setAmbientLight(mOriginAmbientColour);
						}
						else
						{
							float per = mCurrentFadeOutTime / mFadeOutTime;

							// light one
							Ogre::ColourValue nowColour = (mOriginOneLightColour - mDestColour) * per +
								mDestColour;

							mMainSceneLightOne->setDiffuseColour(nowColour);

							// light two
							nowColour = (mOriginTwoLightColour - mDestColour) * per +
								mDestColour;

							mMainSceneLightTwo->setDiffuseColour(nowColour);

							// ambient
							nowColour = (mOriginAmbientColour - mDestColour) * per +
								mDestColour;

							EngineManager::getSingleton().getSceneManager()->setAmbientLight(nowColour);
						}                    
					}
					else if (mCurrentTime >= mFadeInTime + mLastTime + mFadeOutTime)
					{
						mLightModifyPhase = LMP_IDLE;
						mCurrentTime = 0.0f;
						mCurrentFadeInTime = 0.0f;
						mCurrentFadeOutTime = 0.0f;
						mLastTime = 0.0f;
					}
				}
			}
		}
		catch(...)
		{
			WARNING_LOG("MainSceneLight::updateLight Failed --MainSceneLight::updateLight");
			//OGRE_EXCEPT(Ogre::Exception::ERR_INTERNAL_ERROR,"MainSceneLight::updateLight Failed!", "MainSceneLight::updateLight" );
			throw;
		}
    }
    //---------------------------------------------------------------------
    void MainSceneLight::updateLightInfo(void)
    {
     //   MapInfo* sceneInfo = gSystemPtr->getSceneInfo();

     //   const ActorPtr lightOneObject = sceneInfo->findObjectByName("#OrphigineMainLightOne");

     //   if (lightOneObject)
     //   {
     //       LightActor* lightObject = static_cast<LightActor*> (lightOneObject.get());

     //       mMainSceneLightOne = lightObject->getLight();

     //       if (mMainSceneLightOne)
     //           mOriginOneLightColour = mMainSceneLightOne->getDiffuseColour();
     //       else
     //       {
     //           WARNING_LOG("the light one hasn't been created!  "
     //               "Maybe it is a static light! "
					//"MainSceneLight::updateLightInfo",Ogre::LML_TRIVIAL);
     //       }
     //   }
     //   else
     //   {
     //       WARNING_LOG("can't find the light with the name '#OrphigineMainLightOne' "
     //           "MainSceneLight::updateLightInfo",Ogre::LML_TRIVIAL);

     //       mMainSceneLightOne = NULL;
     //   }

     //   const ActorPtr lightTwoObject = sceneInfo->findObjectByName("#OrphigineMainLightTwo");

     //   if (lightTwoObject)
     //   {
     //       LightActor* lightObject = static_cast<LightActor*> (lightTwoObject.get());

     //       mMainSceneLightTwo = lightObject->getLight();

     //       if (mMainSceneLightTwo)
     //           mOriginTwoLightColour = mMainSceneLightTwo->getDiffuseColour();
     //       else
     //       {
     //           WARNING_LOG("the light two hasn't been created!  "
     //               "Maybe it is a static light! "
     //               "MainSceneLight::updateLightInfo",Ogre::LML_TRIVIAL);
     //       }
     //   }
     //   else
     //   {
     //       WARNING_LOG("can't find the light with the name '#OrphigineMainLightTwo' "
     //           "MainSceneLight::updateLightInfo",Ogre::LML_TRIVIAL);

     //       mMainSceneLightTwo = NULL;
     //   }

     //   //mOriginAmbientColour = gSystemPtr->getSceneManager()->getAmbientLight();
     //   mOriginAmbientColour = gSystemPtr->getSceneManager()->getAmbientLight();
    }
}