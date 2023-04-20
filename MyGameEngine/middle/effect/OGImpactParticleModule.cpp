#include "OgreHeader.h"
#include "OGImpactParticleModule.h"
#include "OGImpactManager.h"
#include "OGProjector.h"

#include "engine_manager.h"
#include "OgreString.h"
#include "terrain.h"
// ogre header
#include <OgreParticleSystem.h>
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreStringConverter.h>
#include <OgreParticleEmitter.h>
#include <OgreParticleAffector.h>
#include <OgreParticleSystemManager.h>
#include <OgreBillboardParticleRenderer.h>
#include <OgreParticle.h>
#include <OgreRoot.h>
#include <OgreMaterialManager.h>
#include <OgreTextureManager.h>
#include <platform_log.h>
#include "OGImpactSerializer.h"

#include "OgreMeshComponentParticleRenderer.h"

namespace Orphigine	{

	ImpactParticleModule::CmdParticleSystem ImpactParticleModule::msParticleSystemCmd;
	ImpactParticleModule::CmdParticleSystemRenderQueueLevel	ImpactParticleModule::ms_particleSystemRenderQueueLevelCmd;
	ImpactParticleModule::CmdIsProjector ImpactParticleModule::msIsProjector;

	ImpactParticleModule::ImpactParticleModule(const String &type) :
	ImpactModule(type),
		mParticleSystem(NULL),
		mParticleSystemName(""),
		mIsEmitterEnabled(false),
		mNeedUpdateColour(false),
		mCurrentColour(Ogre::ColourValue::White),
		m_particleSystemRenderQueueLevel(0),
		mIsProjector(false)
	{
		if ( initDefaults(mElementType) )
		{
			Ogre::ParamDictionary* dict = getParamDictionary();

			// Custom params,参数包括:名称，渲染层次
			dict->addParameter(Ogre::ParameterDef("ParticleSystem", 
				"the name of particle system.",
				Ogre::PT_STRING),&msParticleSystemCmd);   

			dict->addParameter(Ogre::ParameterDef("RenderQueueLevel",
				"The level of render queue",
				Ogre::PT_INT),&ms_particleSystemRenderQueueLevelCmd);

			dict->addParameter(Ogre::ParameterDef("IsProjector","is a projector?",Ogre::PT_BOOL),&msIsProjector);
		}
	}
	//---------------------------------------------------------------------
	ImpactParticleModule::~ImpactParticleModule()
	{
		destroyRenderInstance();
	}	
	//---------------------------------------------------------------------
	bool ImpactParticleModule::createRenderInstance(void)
	{

		return _createParticleSystem();
	}
	//---------------------------------------------------------------------
	void ImpactParticleModule::destroyRenderInstance(void)
	{
		_destroyParticleSystem();
		if ( mIsProjector )
		{
			_destroyProjector();
		}


		ImpactModule::destroyRenderInstance();
	}
	//---------------------------------------------------------------------
	void ImpactParticleModule::updateRenderInstance( Real time, TransformInfo &info )
	{
		if ( false == mIsEmitterEnabled )
		{
			if (mParticleSystem)
			{
				for ( unsigned short i = 0; i < mParticleSystem->getNumEmitters(); ++i )
				{
					Ogre::ParticleEmitter* emitter = mParticleSystem->getEmitter(i);

					if (emitter && false == emitter->getEnabled())
						emitter->setEnabled(true);
				}
			}

			mIsEmitterEnabled = true;
		}

		// 真正地进行颜色的改变
		if (mNeedUpdateColour)
		{
			_setAffectorColour();
			mNeedUpdateColour = false;
		}

		//if ( mIsProjector && gSystemPtr->getTerrain()->isTerrainLoaded() )
		if ( mIsProjector && EngineManager::getSingleton().getTerrain()->isTerrainLoaded() )
		{
			const std::vector<Particle*>& activeParticles = mParticleSystem->_getActiveParticles();
			if ( activeParticles.size() > mProjectors.size() )
			{
				for ( int i = (int)mProjectors.size(); i < (int)activeParticles.size(); i++ )
				{
					_createProjector();
				}
			}
			else if ( activeParticles.size() < mProjectors.size() )
			{
				for ( int i = (int)activeParticles.size(); i < (int)mProjectors.size(); i++ )
				{
					mProjectors[i]->setVisible(false);
				}
			}

			auto it = activeParticles.begin();
			for ( int i = 0; it != activeParticles.end(); it++,i++ )
			{
				mProjectors[i]->setVisible(true);
				_updateProjectorFromParticle(mProjectors[i],*it);
			}
		}
	} 
	//---------------------------------------------------------------------
	void ImpactParticleModule::destroyMe(void)
	{
		ImpactModule::destroyMe();
		//	if (mParticleSystem)
		//		mParticleSystem->removeAllEmitters();
	}
	//---------------------------------------------------------------------
	void ImpactParticleModule::sleep(void)
	{
		if (mParticleSystem)
		{
			// detach from parent first
			if (mParticleSystem->getParentNode() &&
				mParticleSystem->getParentNode() == mParticleSystem->getParentSceneNode())
			{
				mParticleSystem->getParentSceneNode()->detachObject(mParticleSystem);
			}

			for ( unsigned short i = 0; i < mParticleSystem->getNumEmitters(); ++i )
			{
				Ogre::ParticleEmitter* emitter = mParticleSystem->getEmitter(i);

				if (emitter && emitter->getEnabled())
					emitter->setEnabled(false);
			}

			mIsEmitterEnabled = false;

			mParticleSystem->clear();

			// 消除MeshParticleRenderer残留的粒子
			Ogre::ParticleSystemRenderer *renderer = mParticleSystem->getRenderer();

			assert (renderer);

			if (renderer->getType() == "mesh")
			{
				static_cast<Ogre::MeshComponentParticleRenderer *>(renderer)->removeAllMeshParticle();
			}

			if ( mIsProjector )
			{
				setAllProjectorVisible(false);
			}
		}

		mCurrentColour = Ogre::ColourValue::White;
		mNeedUpdateColour = false;

		ImpactModule::sleep();		
	}
	//---------------------------------------------------------------------
	void ImpactParticleModule::active(void)
	{
		// attach to basic scene node in case if wake up from sleeping
		if (mParticleSystem && !mParticleSystem->getParentNode() && mBasicNode)
		{
			mBasicNode->attachObject(mParticleSystem);
		}

		if ( mIsProjector )
		{
			setAllProjectorVisible(true);
		}
		//end

		ImpactModule::active();

		// 先不激活emitter，因为现在可能还没到start time，如果现在激活，会使粒子播放时间减少，应在到start time
		// 时才激活
		/*if (mParticleSystem)
		{
		for ( unsigned short i = 0; i < mParticleSystem->getNumEmitters(); ++i )
		{
		mParticleSystem->getEmitter(i)->setEnabled(true);
		}
		}*/
	}	
	//---------------------------------------------------------------------
	void ImpactParticleModule::setParticleSystemName(const String &name)
	{	
		mParticleSystemName = name;

		_destroyParticleSystem();

		mIsRenderInstanceCreated = false;
	}		
	//---------------------------------------------------------------------
	bool ImpactParticleModule::_createParticleSystem(void)
	{
		assert( mParticleSystem == NULL );
		//assert( false == mParticleSystemName.empty() );

		if ( false == mParticleSystemName.empty() )
		{
			Ogre::SceneNode* parent = mBasicNode;

			if (parent)
			{
				
				mParticleSystem = parent->getCreator()->createParticleSystem( parent->getName(), mParticleSystemName );
				
				assert(mParticleSystem);

				Ogre::ParticleSystem* pTemplate = Ogre::ParticleSystemManager::getSingleton().getTemplate( mParticleSystemName );

				ImpactManager& effectMgr = ImpactManager::getSingleton();

				ImpactLevel effectLevel = effectMgr.getEffectLevel();

				if (effectLevel == EL_MID)
				{
					// 中级特效，quota为原来的50%，特效不迭代
					size_t newQuota = (size_t)(pTemplate->getParticleQuota() * 0.5);

					if (newQuota == 0)
						newQuota = 1;

					mParticleSystem->setParticleQuota(newQuota);

					mParticleSystem->setIterationInterval(0.0f);
				}
				else if (effectLevel == EL_LOW)
				{
					// 中级特效，quota为原来的10%，特效不迭代
					size_t newQuota = (size_t)(pTemplate->getParticleQuota() * 0.1);

					if (newQuota == 0)
						newQuota = 1;

					mParticleSystem->setParticleQuota(newQuota);

					mParticleSystem->setIterationInterval(0.0f);
				}

				

				mParticleSystem->setCastShadows(false);

				mParticleSystem->setVisible(mVisible);

				parent->attachObject(mParticleSystem);


				if ( mIsProjector && EngineManager::getSingleton().getTerrain()->isTerrainLoaded() )
				{
					mParticleSystem->setVisible(false);
				}

				return true;
			}
		}       

		return false;
	}
	//---------------------------------------------------------------------
	void ImpactParticleModule::_destroyParticleSystem(void)
	{
 
	}
	//---------------------------------------------------------------------
	bool ImpactParticleModule::existVisualElements(void)
	{
		if (mParticleSystem)
		{
			return (mParticleSystem->getNumParticles() > 0);
		}
		else
			return false;
	}
	//---------------------------------------------------------------------
	void ImpactParticleModule::shutdown(void)
	{
		if (mParticleSystem)
		{
			for ( unsigned short i = 0; i < mParticleSystem->getNumEmitters(); ++i )
			{
				Ogre::ParticleEmitter* emitter = mParticleSystem->getEmitter(i);

				if (emitter && emitter->getEnabled())
					emitter->setEnabled(false);
			}
		}

		if ( mIsProjector )
		{
			setAllProjectorVisible(false);
		}
		//end
	}
	//---------------------------------------------------------------------
	void ImpactParticleModule::setColour( const Ogre::ColourValue& colour )
	{
		mCurrentColour = colour;
		mNeedUpdateColour = true;        
	}
	//---------------------------------------------------------------------
	void ImpactParticleModule::_setAffectorColour(void)
	{
		// 改变colour fader影响器中的颜色
		if (mParticleSystem)
		{
			for ( unsigned short i = 0; i < mParticleSystem->getNumAffectors(); ++i )
			{
				Ogre::ParticleAffector* affector = mParticleSystem->getAffector(i);

				assert (affector);
				if (affector->getType() == "ColourFading")
				{
					for ( unsigned short num = 0; num < 6; ++num )
					{
						String paraName = "colour" + Ogre::StringConverter::toString(num);

						ColourMap::iterator i = mColourMap.find(paraName);

						Ogre::ColourValue originColour;

						// 如果之前已经保存过原来的颜色，就直接获取
						if (i != mColourMap.end())
						{
							originColour = i->second;
						}
						else
						{
							originColour = 
								Ogre::StringConverter::parseColourValue( affector->getParameter(paraName) );

							/// 保存原来的颜色
							mColourMap.insert( ColourMap::value_type(paraName, originColour) );
						}

						/// 用原来的颜色与要设定的颜色进行相乘
						affector->setParameter( paraName, 
							Ogre::StringConverter::toString(originColour * mCurrentColour) );
					}

				}
			}
		}
	}
	//-----------------------------------------------------------------------
	void ImpactParticleModule::setVisibleFlag(uint32 flags)
	{
		if (mParticleSystem)
			mParticleSystem->setVisibilityFlags(flags);
	}
	//-----------------------------------------------------------------------
	void ImpactParticleModule::setVisible(bool visible)
	{
		if (mParticleSystem)
		{
			if (visible)
			{
				// 如果要重新显示,就把粒子重新挂接上去
				if (!mParticleSystem->getParentNode() && mBasicNode)
				{
					mBasicNode->attachObject(mParticleSystem);
				}
			}
			else
			{
				// 如果要隐藏这个粒子系统,要先把它从父节点上解挂,这样,就不会调用粒子系统的update()
				if (mParticleSystem->getParentNode() &&
					mParticleSystem->getParentNode() == mParticleSystem->getParentSceneNode())
				{
					mParticleSystem->getParentSceneNode()->detachObject(mParticleSystem);
				}

				// 对于mesh粒子,要隐藏它生成的mesh particle
				Ogre::ParticleSystemRenderer *renderer = mParticleSystem->getRenderer();

				assert (renderer);

				if (renderer->getType() == "mesh")
				{
					static_cast<Ogre::MeshComponentParticleRenderer *>(renderer)->removeAllMeshParticle();
				}
			}
		}

	
		if ( mIsProjector && 
			EngineManager::getSingleton().getTerrain()->isTerrainLoaded() && 
			mParticleSystem != NULL )
		{
			mParticleSystem->setVisible(false);
			return;
		}
		ImpactBasic::setVisible(visible);        
	}

	int ImpactParticleModule::getParticleSystemRenderQueueLevel() const
	{
		return m_particleSystemRenderQueueLevel;
	}

	void ImpactParticleModule::setParticleSystemRenderQueueLevel( int val )
	{
		
	}
	bool ImpactParticleModule::_createProjector()
	{

		Ogre::SceneNode* parent = mBasicNode;

		if (parent)
		{
			//int nProjectorNum = (int)mProjectors.size();
			static int nProjectorNum = 0;
			String strName = "Projector_" + parent->getName();
			strName += Ogre::StringConverter::toString(nProjectorNum);
			auto sceneMgr = EngineManager::getSingleton().getSceneManager();
			Projector * projector = static_cast<Projector*>(sceneMgr->createMovableObject(strName, ProjectorFactory::FACTORY_TYPE_NAME, nullptr) );
			projector->setProjectionType(Ogre::PT_ORTHOGRAPHIC);

			nProjectorNum++;

			projector->setNearClipDistance(100.0f);
			projector->setFarClipDistance(2000.0f);

			Real nearClip = projector->getNearClipDistance();

			Ogre::Radian fovy = Ogre::Math::ATan(mParticleSystem->getDefaultWidth() / (nearClip * 2) ) * 2.0f;

			projector->setFOVy(fovy);
			//projector->setTerrain(gSystemPtr->getTerrain());
			projector->setTerrain(EngineManager::getSingleton().getTerrain());
			projector->setAspectRatio(mParticleSystem->getDefaultWidth()/mParticleSystem->getDefaultHeight());
			projector->setShowFrustum(false);
			projector->setEnableClipPlanes(false);
			projector->setPatchMaterial(mParticleSystem->getMaterialName());
			projector->setCastShadows(false);

			projector->setVisible(true);

			parent->attachObject(projector);
			parent->setDirection(Ogre::Vector3::NEGATIVE_UNIT_Y, parent->TS_WORLD);


			mProjectors.push_back(projector);

			mParticleSystem->setVisible(false);

			return true;
		}

		return false;
	}

	void ImpactParticleModule::_destroyProjector()
	{
		for ( int i = 0; i < (int)mProjectors.size(); i++ )
		{
			Projector * p = mProjectors[i];
			Ogre::SceneNode* parent = p->getParentSceneNode();
			assert(parent);
			Ogre::SceneManager* creator = parent->getCreator();
			assert(creator);

			parent->detachObject(p->getName());

			EngineManager::getSingleton().getSceneManager()->destroyMovableObject(p);
		}
		mProjectors.clear();
	}

	void ImpactParticleModule::_updateProjectorFromParticle(Projector * pProjector,Ogre::Particle * pParticle)
	{
		if (true)
		{
			Real nearClip = pProjector->getNearClipDistance();
			Ogre::Radian fovy = Ogre::Math::ATan(pParticle->mWidth / (nearClip * 2) ) * 2.0f;
			pProjector->setFOVy(fovy);
			pProjector->setAspectRatio(pParticle->mWidth/pParticle->mHeight);
		}

		if ( pParticle->mRotation != Ogre::Radian(0) && mBasicNode != NULL )
		{
			Ogre::Quaternion q;
			q.FromAngleAxis(Ogre::Radian(Ogre::Degree(-90.0f)),Ogre::Vector3::UNIT_X);

			Ogre::Quaternion q1;
			q1.FromAngleAxis(pParticle->mRotation, Ogre::Vector3::UNIT_Y);

			q = q1 * q;
			mBasicNode->setOrientation(q);
		}


		pProjector->setColour(pParticle->mColour.getAsBYTE());
	}

	void ImpactParticleModule::setAllProjectorVisible(bool bVisible)
	{
		for ( int i = 0; i < (int)mProjectors.size(); i++ )
		{
			Projector * p = mProjectors[i];
			p->setVisible(bVisible);
		}
	}
	///*
	char * ImpactParticleModule::readFromBuffer(char * pCurrent)
	{

		pCurrent = ImpactModule::readFromBuffer(pCurrent);

		int length = sizeof(int) * 2;
		memcpy(&m_particleSystemRenderQueueLevel,pCurrent,length);
		pCurrent += length;


		String particleSystemName;
		Ogre::StringUtil::loadStringFromMemory(particleSystemName,pCurrent);

		setParticleSystemName(particleSystemName);


		return pCurrent;
	}

	void ImpactParticleModule::saveToFile(std::ofstream & of)
	{
		ImpactModule::saveToFile(of);
		of.write((const char *)(&m_particleSystemRenderQueueLevel),sizeof(int) * 2);
		//particleSystemName在编辑器里存储，因为particleSystemName需要做一些修正
		//详见Tool\NewParticleEditor\ParticleEditor\EffectPane.cpp 478行
	}
	//*/
	bool ImpactParticleModule::loadFromStream(Ogre::Serializer* pSerializer,Ogre::DataStreamPtr& stream)
	{
		if(pSerializer && stream->eof() == false)
		{
			unsigned short id = pSerializer->readChunk(stream);
			if(id != ImpactSerializer::EFF_PARTICLE_ELEMENT)
			{
				WARNING_LOG("Load ParticleElement From Stream Failed. ChunkId Error");
				// 因为不读取，所以直接跳过相应数据段长
				pSerializer->skipChunk(stream);
				return false;
			}
			//基类成员
			pSerializer->readData(stream,&mStartTime,1,sizeof(Ogre::Real));
			pSerializer->readData(stream,&mLifeTime,1,sizeof(Ogre::Real));
			pSerializer->readData(stream,&mRelPos,1,sizeof(Ogre::Vector3));
			pSerializer->readData(stream,&mRelOrientation,1,sizeof(Ogre::Quaternion));
			//自身成员
			pSerializer->readData(stream,&m_particleSystemRenderQueueLevel,1,sizeof(int));
			pSerializer->readData(stream,&mIsProjector,1,sizeof(bool));
			String particleSystemName = pSerializer->readStringBin(stream);
			setParticleSystemName(particleSystemName);
			return true;
		}
		return false;
	}
	bool ImpactParticleModule::saveToBinaryFile(Ogre::Serializer* pSerializer)
	{
		return false;
	}
	std::size_t	ImpactParticleModule::calcSerializedSize()
	{
		size_t tmpSize = Ogre::Serializer::STREAM_OVERHEAD_SIZE;
		//基类成员
		tmpSize += sizeof(mStartTime);
		tmpSize += sizeof(mLifeTime);
		tmpSize += sizeof(mRelPos);
		tmpSize += sizeof(mRelOrientation);
		//自身成员
		tmpSize += sizeof(m_particleSystemRenderQueueLevel);
		tmpSize += sizeof(mIsProjector);
		tmpSize += mParticleSystemName.length() + 1;	
		return tmpSize;
	}
	///////////////////////////////////////////
	String ImpactParticleModule::CmdParticleSystem::doGet(const void* target) const
	{
		return static_cast<const ImpactParticleModule*>(target)->getParticleSystemName();
	}
	void ImpactParticleModule::CmdParticleSystem::doSet(void* target, const String& val)
	{
		static_cast<ImpactParticleModule *>(target)->setParticleSystemName(val);
	}  
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void ImpactParticleModule::CmdParticleSystem::doCopy(void* target, const void* source)
	{
		static_cast<ImpactParticleModule *>(target)->setParticleSystemName(
			static_cast<const ImpactParticleModule*>(source)->getParticleSystemName() );
	}
#endif

	Ogre::String ImpactParticleModule::CmdParticleSystemRenderQueueLevel::doGet( const void* target ) const
	{
		return	Ogre::StringConverter::toString(
			static_cast<const ImpactParticleModule*>(target)->getParticleSystemRenderQueueLevel());	
	}

	void ImpactParticleModule::CmdParticleSystemRenderQueueLevel::doSet( void* target, const String& val )
	{
		static_cast<ImpactParticleModule*>(target)->setParticleSystemRenderQueueLevel(
			Ogre::StringConverter::parseInt(val));
	}
#if OGRE_STRING_INTERFACE_COPY
	void ImpactParticleModule::CmdParticleSystemRenderQueueLevel::doCopy( void* target, const void* source )
	{
		static_cast<ImpactParticleModule*>(target)->setParticleSystemRenderQueueLevel(
			static_cast<const ImpactParticleModule*>(source)->getParticleSystemRenderQueueLevel());
	}
#endif

	Ogre::String ImpactParticleModule::CmdIsProjector::doGet(const void * target) const
	{
		return Ogre::StringConverter::toString(static_cast<const ImpactParticleModule *>(target)->getIsProjector());
	}

	void ImpactParticleModule::CmdIsProjector::doSet(void* target, const String& val)
	{
		static_cast<ImpactParticleModule *>(target)->setIsProjector(Ogre::StringConverter::parseBool(val));
	}

#if OGRE_STRING_INTERFACE_COPY
	void ImpactParticleModule::CmdIsProjector::doCopy(void* target, const void* source)
	{
		static_cast<ImpactParticleModule *>(target)->setIsProjector(static_cast<const ImpactParticleModule *>(source)->getIsProjector());
	}
#endif
}