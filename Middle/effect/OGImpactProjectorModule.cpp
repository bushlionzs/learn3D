#include "OgreHeader.h"
#include "OGImpactProjectorModule.h"
#include "OGProjector.h"

// ogre header
#include <OgreSceneNode.h>
#include <OgreStringConverter.h>
#include <OgreParticleEmitter.h>
#include <OgreSceneManager.h>
#include <OgreMaterial.h>
#include <OgreParticleAffector.h>
#include <platform_log.h>
#include "OGImpactSerializer.h"
#include "engine_manager.h"
#include "OgreMoveObject.h"
#include "OgreString.h"
#include "OgreTextureUnit.h"

namespace Orphigine	{

	ImpactProjectorModule::CmdMaterialName       ImpactProjectorModule::msMaterialNameCmd;
	ImpactProjectorModule::CmdProjectionSize     ImpactProjectorModule::msProjectionSizeCmd;

	ImpactProjectorModule::CmdScaleAdjust		ImpactProjectorModule::msScaleCmd[MAX_STAGES];
	ImpactProjectorModule::CmdScaleTimeAdjust	ImpactProjectorModule::msScaleTimeCmd[MAX_STAGES];
	ImpactProjectorModule::CmdScaleChangeTime    ImpactProjectorModule::msScaleChangeTime;

	ImpactProjectorModule::CmdColourAdjust		ImpactProjectorModule::msColourCmd[MAX_STAGES];
	ImpactProjectorModule::CmdColourTimeAdjust	ImpactProjectorModule::msColourTimeCmd[MAX_STAGES];
	ImpactProjectorModule::CmdColourChangeTime   ImpactProjectorModule::msColourChangeTime;
	ImpactProjectorModule::CmdShowFrustum        ImpactProjectorModule::msShowFrustumCmd;

	ImpactProjectorModule::CmdNearClipDistance   ImpactProjectorModule::msNearClipDistanceCmd;
	ImpactProjectorModule::CmdFarClipDistance    ImpactProjectorModule::msFarClipDistanceCmd;

	ImpactProjectorModule::ImpactProjectorModule(const String &type) :
	ImpactModule(type),
		mProjector(NULL),
		m_bUsingProjScene(false),
		mMaterialName(""),
		mProjectionSize(200.0f),
		mTextureUnitUScale(1.0f),
		mTextureUnitVScale(1.0f),
		mProjectorColour(Ogre::ColourValue::White),
		mScaleChangeTime(0.0f),
		mColourChangeTime(0.0f),
		mShowFrustum(false),
		mNearClipDistance(100.0f),
		mFarClipDistance(1000.0f),
		mTerrainGridLimit(32)
	{
		for (int i=0;i<MAX_STAGES;i++)
		{
			mScaleAdj[i]	= Ogre::Vector3(1.0f, 1.0f, 1.0f);
			mScaleTimeAdj[i]		= 1.0f;

			mColourAdj[i]	= Ogre::ColourValue::White;
			mColourTimeAdj[i]		= 1.0f;
		}

		if ( initDefaults(mElementType) )
		{
			Ogre::ParamDictionary* dict = getParamDictionary();

			dict->addParameter(Ogre::ParameterDef("Material", 
				"the name of material of the projector.",
				Ogre::PT_STRING),&msMaterialNameCmd);      

			dict->addParameter(Ogre::ParameterDef("ProjectionSize", 
				"the size of projected terrain or object.",
				Ogre::PT_REAL),&msProjectionSizeCmd);  

			for (int i=0;i<MAX_STAGES;i++)
			{
				msScaleCmd[i].mIndex	= i;
				msScaleTimeCmd[i].mIndex		= i;

				std::stringstream stage;
				stage << i;
				String	scale_title	= String("Scale") + stage.str();
				String	time_title		= String("ScaleTime") + stage.str();
				String	scale_descr	= String("Stage ") + stage.str() + String(" Scale.");
				String	time_descr		= String("Stage ") + stage.str() + String(" ScaleTime.");

				dict->addParameter(Ogre::ParameterDef(scale_title, scale_descr, Ogre::PT_VECTOR3), &msScaleCmd[i]);
				dict->addParameter(Ogre::ParameterDef(time_title,   time_descr,   Ogre::PT_REAL),		 &msScaleTimeCmd[i]);
			}

			dict->addParameter(Ogre::ParameterDef("ScaleChangeTime", 
				"the size of projected terrain or object.",
				Ogre::PT_REAL),&msScaleChangeTime);  

			for (int i=0;i<MAX_STAGES;i++)
			{
				msColourCmd[i].mIndex	= i;
				msColourTimeCmd[i].mIndex		= i;

				std::stringstream stage;
				stage << i;
				String	colour_title	= String("Colour") + stage.str();
				String	time_title		= String("ColourTime") + stage.str();
				String	colour_descr	= String("Stage ") + stage.str() + String(" Colour.");
				String	time_descr		= String("Stage ") + stage.str() + String(" ColourTime.");

				dict->addParameter(Ogre::ParameterDef(colour_title, colour_descr, Ogre::PT_COLOURVALUE), &msColourCmd[i]);
				dict->addParameter(Ogre::ParameterDef(time_title,   time_descr,   Ogre::PT_REAL),		 &msColourTimeCmd[i]);
			}

			dict->addParameter(Ogre::ParameterDef("ColourChangeTime", 
				"the size of projected terrain or object.",
				Ogre::PT_REAL),&msColourChangeTime); 

			dict->addParameter(Ogre::ParameterDef("ShowFrustum", 
				"show the shape of the frustum that used in this projector.",
				Ogre::PT_BOOL),&msShowFrustumCmd);

			dict->addParameter(Ogre::ParameterDef("NearClipDistance", 
				"set the near clip distance of the projector.",
				Ogre::PT_REAL),&msNearClipDistanceCmd);

			dict->addParameter(Ogre::ParameterDef("FarClipDistance", 
				"set the far clip distance of the projector.",
				Ogre::PT_REAL),&msFarClipDistanceCmd);
		}
	}
	//---------------------------------------------------------------------
	ImpactProjectorModule::~ImpactProjectorModule()
	{
		destroyRenderInstance();
	}	
	//---------------------------------------------------------------------
	bool ImpactProjectorModule::createRenderInstance(void)
	{
		return _createProjector();
	}
	//---------------------------------------------------------------------
	void ImpactProjectorModule::destroyRenderInstance(void)
	{
		_destroyProjector();

		ImpactModule::destroyRenderInstance();
	}
	//---------------------------------------------------------------------
	void ImpactProjectorModule::updateRenderInstance( Real time, TransformInfo &info )
	{
		mCurrentLifeTime += time;

		_updateProjectorMaterial();
	}
	//---------------------------------------------------------------------
	void ImpactProjectorModule::_updateProjectorMaterial(void)
	{
		if (mProjector)
		{
			_updateProjectorScale();
			_updateProjectorColour();

			Ogre::MaterialPtr matPtr = mProjector->_getPatchMaterial();

			if (matPtr)
			{

				int32_t texCount = matPtr->getTextureUnitCount();
				for (int32_t i = 0; i < texCount; i++)
				{
					auto& tex = matPtr->getTextureUnit(i);
					tex->setTextureScale(mTextureUnitUScale, mTextureUnitVScale);
				}
			}
		}
	}    
	//---------------------------------------------------------------------
	bool ImpactProjectorModule::_createProjector(void)
	{
		assert(mProjector == NULL);  // 在Release版本下断言不起作用，反馈的崩溃报告显示，确实有mProjector未销毁的情况下重复创建的情况

		Ogre::SceneManager* pSceneMgr = EngineManager::getSingletonPtr()->getSceneManager();
		Ogre::SceneNode* pSceneNode = mBasicNode;

		if(pSceneMgr && pSceneNode)
		{
			String projectorName = "Projector_" + pSceneNode->getName();  // 构造投影体的名字，通过追加场景结点名字来实现

			// 先销毁旧的投影体，如果存在的话

	
			if(pSceneNode->numAttachedObjects() > 0)
			{
				pSceneNode->detachObject(projectorName);
			}
			pSceneMgr->destroyMovableObject(projectorName, ProjectorFactory::FACTORY_TYPE_NAME);

			// 现在可以创建新的投影体了
			mProjector = static_cast<Projector*>(pSceneMgr->createMovableObject(projectorName, ProjectorFactory::FACTORY_TYPE_NAME, nullptr));
			// 设置属性
			mProjector->enableUsingProjScene(m_bUsingProjScene);
			mProjector->setProjectionType(Ogre::PT_ORTHOGRAPHIC);
			mProjector->setFOVy( _getFovFromProjectionSize() );
			mProjector->setTerrain(EngineManager::getSingletonPtr()->getTerrain());
			mProjector->setAspectRatio(1);
			mProjector->setShowFrustum(mShowFrustum);
			mProjector->setEnableClipPlanes(false);
			mProjector->setPatchMaterial(mMaterialName);
			mProjector->setCastShadows(false);

			mProjector->setNearClipDistance(mNearClipDistance);
			mProjector->setFarClipDistance(mFarClipDistance);

			mProjector->setVisible(mVisible);

			mProjector->setTerrainGridLimit(mTerrainGridLimit); 

			//非粒子系统的投影只有在位置发生变化才需要更新
			mProjector->setForceUpdate(false); 

			pSceneNode->attachObject(mProjector);
			pSceneNode->setPosition(Ogre::Vector3(0, 200, 0));
			pSceneNode->setDirection(Ogre::Vector3::NEGATIVE_UNIT_Y, pSceneNode->TS_WORLD);

			return true;
		}

		return false;
	}
	//---------------------------------------------------------------------
	void ImpactProjectorModule::setProjectionTerrainGridLimit(int size)
	{
		mTerrainGridLimit = size;
		if (mProjector)
		{
			mProjector->setTerrainGridLimit(size); 
		}
	}

	//---------------------------------------------------------------------
	void ImpactProjectorModule::shutdown(void)
	{
		if (mProjector) 
		{
			mProjector->setVisible(false);
		}

		_destroyProjector();
	}
	//---------------------------------------------------------------------
	void ImpactProjectorModule::active(void)
	{
		ImpactModule::active();

		if (mProjector)
		{ 
			mProjector->setDirty(true);
			mProjector->setVisible(true);
		}

		_createProjector();
	}
	//end

	void ImpactProjectorModule::sleep(void)
	{
		ImpactModule::sleep();

		if(mProjector)
		{
			mProjector->setVisible(false);
		}

		_destroyProjector();
	}

	void ImpactProjectorModule::enableUsingProjScene(bool bEnable)
	{
		m_bUsingProjScene = bEnable;
		if(mProjector)
		{
			mProjector->enableUsingProjScene(m_bUsingProjScene);
		}
	}

	//---------------------------------------------------------------------
	void ImpactProjectorModule::_destroyProjector(void)
	{
		if (mProjector)
		{
			Ogre::SceneNode* parent = mProjector->getParentSceneNode();
			if(parent)
			{
				parent->detachObject(mProjector->getName());
			}

			EngineManager::getSingletonPtr()->getSceneManager()->destroyMovableObject(mProjector);

			mProjector = NULL;
		} 
	}
	//---------------------------------------------------------------------
	void ImpactProjectorModule::_updateProjectorScale(void)
	{
		if (mCurrentLifeTime > 0.0f && mScaleChangeTime > 0.0f)
		{
			Real			projector_time	= fmod( mCurrentLifeTime / mScaleChangeTime, 1.0f );

			if (projector_time <= mScaleTimeAdj[0])
			{
				_setTextureUnitScale(mScaleAdj[0].x, mScaleAdj[0].y);
			} 
			else if (projector_time >= mScaleTimeAdj[MAX_STAGES - 1])
			{
				_setTextureUnitScale(mScaleAdj[MAX_STAGES-1].x, mScaleAdj[MAX_STAGES-1].y);
			}
			else
			{
				for (int i=0;i<MAX_STAGES-1;i++)
				{
					if (projector_time >= mScaleTimeAdj[i] && projector_time < mScaleTimeAdj[i + 1])
					{
						projector_time -= mScaleTimeAdj[i];
						projector_time /= (mScaleTimeAdj[i+1]-mScaleTimeAdj[i]);

						_setTextureUnitScale(
							(mScaleAdj[i+1].x * projector_time) + (mScaleAdj[i].x * (1.0f - projector_time)),
							(mScaleAdj[i+1].y * projector_time) + (mScaleAdj[i].y * (1.0f - projector_time))
							);
						break;
					}
				}
			}
		}
	}
	//---------------------------------------------------------------------
	void ImpactProjectorModule::_updateProjectorColour(void)
	{
		if (mCurrentLifeTime > 0.0f && mColourChangeTime > 0.0f)
		{
			Real			projector_time	= fmod( mCurrentLifeTime / mColourChangeTime, 1.0f );

			if (projector_time <= mColourTimeAdj[0])
			{
				mProjectorColour = mColourAdj[0];
			} 
			else if (projector_time >= mColourTimeAdj[MAX_STAGES - 1])
			{
				mProjectorColour = mColourAdj[MAX_STAGES - 1];
			}
			else
			{
				for (int i=0;i<MAX_STAGES-1;i++)
				{
					if (projector_time >= mColourTimeAdj[i] && projector_time < mColourTimeAdj[i + 1])
					{
						projector_time -= mColourTimeAdj[i];
						projector_time /= (mColourTimeAdj[i+1]-mColourTimeAdj[i]);

						mProjectorColour.r = ((mColourAdj[i+1].r * projector_time) + (mColourAdj[i].r * (1.0f - projector_time)));
						mProjectorColour.g = ((mColourAdj[i+1].g * projector_time) + (mColourAdj[i].g * (1.0f - projector_time)));
						mProjectorColour.b = ((mColourAdj[i+1].b * projector_time) + (mColourAdj[i].b * (1.0f - projector_time)));
						mProjectorColour.a = ((mColourAdj[i+1].a * projector_time) + (mColourAdj[i].a * (1.0f - projector_time)));
						break;
					}
				}
			}
		}
	}
	//---------------------------------------------------------------------
	void ImpactProjectorModule::_setTextureUnitScale(float uscale, float vscale)
	{
		mTextureUnitUScale = uscale;
		mTextureUnitVScale = vscale;
	}
	//---------------------------------------------------------------------
	void ImpactProjectorModule::setMaterialName(const String &name)
	{
		mMaterialName = name;

		if (mProjector)
		{
			mProjector->setPatchMaterial(mMaterialName);
		}
	}
	//---------------------------------------------------------------------
	Ogre::Radian ImpactProjectorModule::_getFovFromProjectionSize(void)
	{
		/**
		mProjectionSize来计算出所需的fov
		/|
		/  |
		/    | mProjectionSize / 2
		/      |
		/a       | 
		/----------- D


		a为fov/2，D为near distance，由图可知，tan( fov / 2 ) * D = mProjectionSize / 2，
		D为100.0f（默认数值），所以fov = atan( mProjectionSize / ( 2 * D ) ) * 2
		*/

		Real nearClip = mProjector->getNearClipDistance();

		if (nearClip > 0.0f)
		{
			return Ogre::Math::ATan( mProjectionSize / (nearClip * 2) ) * 2.0f;
		}
		else
		{
			OGRE_EXCEPT(Ogre::Exception::ERR_INVALIDPARAMS,
				"the near clip distance of projector must be larger than zero.",
				"ProjectorElement::_getFovFromProjectionSize");
			return Ogre::Radian(0);
		}
	}
	//---------------------------------------------------------------------
	void ImpactProjectorModule::setProjectionSize(float size)
	{
		mProjectionSize = size;

		if (mProjector)
		{
			mProjector->setFOVy( _getFovFromProjectionSize() );
		}
	}
	//-----------------------------------------------------------------------
	void ImpactProjectorModule::setScaleAdjust(size_t index, ProjectorScaleValue& scale)
	{
		mScaleAdj[index] = scale;
	}
	//-----------------------------------------------------------------------
	ProjectorScaleValue ImpactProjectorModule::getScaleAdjust(size_t index) const
	{
		return mScaleAdj[index];
	}
	//-----------------------------------------------------------------------
	void ImpactProjectorModule::setScaleTimeAdjust(size_t index, Real time)
	{
		mScaleTimeAdj[index] = time;
	}
	//-----------------------------------------------------------------------
	Real ImpactProjectorModule::getScaleTimeAdjust(size_t index) const
	{
		return mScaleTimeAdj[index];
	}
	//-----------------------------------------------------------------------
	void ImpactProjectorModule::setColourAdjust(size_t index, Ogre::ColourValue colour)
	{
		mColourAdj[index] = colour;
	}
	//-----------------------------------------------------------------------
	Ogre::ColourValue ImpactProjectorModule::getColourAdjust(size_t index) const
	{
		return mColourAdj[index];
	}
	//-----------------------------------------------------------------------
	void ImpactProjectorModule::setColourTimeAdjust(size_t index, Real time)
	{
		mColourTimeAdj[index] = time;
	}
	//-----------------------------------------------------------------------
	Real ImpactProjectorModule::getColourTimeAdjust(size_t index) const
	{
		return mColourTimeAdj[index];
	}	
	//-----------------------------------------------------------------------
	void ImpactProjectorModule::setScaleChangeTime(Real time)
	{
		mScaleChangeTime = time;
	}
	//-----------------------------------------------------------------------
	void ImpactProjectorModule::setColourChangeTime(Real time)
	{
		mColourChangeTime = time;
	}
	//-----------------------------------------------------------------------
	void ImpactProjectorModule::setShowFrustum(bool show)
	{
		mShowFrustum = show;

		if (mProjector)
			mProjector->setShowFrustum(mShowFrustum);
	}
	//-----------------------------------------------------------------------
	void ImpactProjectorModule::setVisibleFlag(uint32 flags)
	{
	}

	void ImpactProjectorModule::setVisible(bool visible)
	{
		ImpactModule::setVisible(visible);

		if(mProjector)
		{
			mProjector->setVisible(visible);
		}
	}

	//-----------------------------------------------------------------------
	void ImpactProjectorModule::setNearClipDistance(Real dis)
	{
		mNearClipDistance = dis;

		if (mProjector)
			mProjector->setNearClipDistance(dis);
	}
	//-----------------------------------------------------------------------
	void ImpactProjectorModule::setFarClipDistance(Real dis)
	{
		mFarClipDistance = dis;

		if (mProjector)
			mProjector->setFarClipDistance(dis);
	}
	///*
	char * ImpactProjectorModule::readFromBuffer(char * pCurrent)
	{
		pCurrent = ImpactModule::readFromBuffer(pCurrent);

		int length = sizeof(float) * 5 + sizeof(float) * MAX_STAGES * 2 + 
			sizeof(ProjectorScaleValue) * MAX_STAGES + sizeof(Ogre::ColourValue) * MAX_STAGES + sizeof(int);
		memcpy(&mProjectionSize,pCurrent,length);
		pCurrent += length;

		String strMaterialName;
		Ogre::StringUtil::loadStringFromMemory(strMaterialName,pCurrent);

		setMaterialName(strMaterialName);

		return pCurrent;
	}

	void ImpactProjectorModule::saveToFile(std::ofstream & of)
	{
		ImpactModule::saveToFile(of);
		of.write((const char *)(&mProjectionSize),sizeof(float) * 5 + sizeof(float) * MAX_STAGES * 2 + 
			sizeof(ProjectorScaleValue) * MAX_STAGES + sizeof(Ogre::ColourValue) * MAX_STAGES + sizeof(int));
		Ogre::StringUtil::saveStringToStream(mMaterialName,of);
	}
	//*/
	bool ImpactProjectorModule::loadFromStream(Ogre::Serializer* pSerializer,Ogre::DataStreamPtr& stream)
	{
		if(pSerializer && stream->eof() == false)
		{
			unsigned short id = pSerializer->readChunk(stream);
			if(id != ImpactSerializer::EFF_PROJECTOR_ELEMENT)
			{
				WARNING_LOG("Load ProjectorElement From Stream Failed. ChunkId Error");
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
			String materialName = pSerializer->readStringBin(stream);
			setMaterialName(materialName);
			pSerializer->readData(stream,&mProjectionSize,1,sizeof(float));
			for (int i=0; i<MAX_STAGES; ++i)
			{
				pSerializer->readData(stream,&(mScaleAdj[i]),1,sizeof(ProjectorScaleValue));
				pSerializer->readData(stream,&(mScaleTimeAdj[i]),1,sizeof(float));
				pSerializer->readData(stream,&(mColourAdj[i]),1,sizeof(Ogre::ColourValue));
				pSerializer->readData(stream,&(mColourTimeAdj[i]),1,sizeof(float));
			}
			pSerializer->readData(stream,&mScaleChangeTime,1,sizeof(float));			
			pSerializer->readData(stream,&mColourChangeTime,1,sizeof(float));
			pSerializer->readData(stream,&mShowFrustum,1,sizeof(bool));
			pSerializer->readData(stream,&mNearClipDistance,1,sizeof(float));
			pSerializer->readData(stream,&mFarClipDistance,1,sizeof(float));
			return true;	
		}
		return false;
	}
	bool ImpactProjectorModule::saveToBinaryFile(Ogre::Serializer* pSerializer)
	{
		
		return false;
	}
	std::size_t	ImpactProjectorModule::calcSerializedSize()
	{
		size_t tmpSize = Ogre::Serializer::STREAM_OVERHEAD_SIZE;
		//基类成员
		tmpSize += sizeof(mStartTime);
		tmpSize += sizeof(mLifeTime);
		tmpSize += sizeof(mRelPos);
		tmpSize += sizeof(mRelOrientation);
		//自身成员
		tmpSize += mMaterialName.length() + 1;	
		tmpSize += sizeof(mProjectionSize);
		for (int i=0; i<MAX_STAGES; ++i)
		{
			tmpSize += sizeof(mScaleAdj[i]);
			tmpSize += sizeof(mScaleTimeAdj[i]);
			tmpSize += sizeof(mColourAdj[i]);
			tmpSize += sizeof(mColourTimeAdj[i]);
		}
		tmpSize += sizeof(mScaleChangeTime);
		tmpSize += sizeof(mColourChangeTime);
		tmpSize += sizeof(mShowFrustum);
		tmpSize += sizeof(mNearClipDistance);
		tmpSize += sizeof(mFarClipDistance);
		return tmpSize;
	}

	///////////////////////////////////////////
	String ImpactProjectorModule::CmdMaterialName::doGet(const void* target) const
	{
		return static_cast<const ImpactProjectorModule*>(target)->getMaterialName();
	}
	void ImpactProjectorModule::CmdMaterialName::doSet(void* target, const String& val)
	{
		static_cast<ImpactProjectorModule *>(target)->setMaterialName(val);
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void ImpactProjectorModule::CmdMaterialName::doCopy(void* target, const void* source)
	{
		static_cast<ImpactProjectorModule *>(target)->setMaterialName(
			static_cast<const ImpactProjectorModule*>(source)->getMaterialName() );
	}
#endif
	//---------------------------------------------------------------------
	String ImpactProjectorModule::CmdProjectionSize::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString( 
			static_cast<const ImpactProjectorModule*>(target)->getProjectionSize() );
	}
	void ImpactProjectorModule::CmdProjectionSize::doSet(void* target, const String& val)
	{
		static_cast<ImpactProjectorModule *>(target)->setProjectionSize( Ogre::StringConverter::parseReal(val) );
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void ImpactProjectorModule::CmdProjectionSize::doCopy(void* target, const void* source)
	{
		static_cast<ImpactProjectorModule *>(target)->setProjectionSize(
			static_cast<const ImpactProjectorModule*>(source)->getProjectionSize() );
	}
#endif
	//-----------------------------------------------------------------------
	String ImpactProjectorModule::CmdScaleAdjust::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const ImpactProjectorModule*>(target)->getScaleAdjust(mIndex) );
	}
	void ImpactProjectorModule::CmdScaleAdjust::doSet(void* target, const String& val)
	{
		Ogre::Vector3 tmp;
		Ogre::StringConverter::parse(val, tmp);
		static_cast<ImpactProjectorModule*>(target)->setScaleAdjust(mIndex, tmp);
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void ImpactProjectorModule::CmdScaleAdjust::doCopy(void* target, const void* source)
	{
		static_cast<ImpactProjectorModule *>(target)->setScaleAdjust(mIndex,
			static_cast<const ImpactProjectorModule*>(source)->getScaleAdjust(mIndex) );
	}
#endif
	//-----------------------------------------------------------------------
	String ImpactProjectorModule::CmdScaleTimeAdjust::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const ImpactProjectorModule*>(target)->getScaleTimeAdjust(mIndex) );
	}
	void ImpactProjectorModule::CmdScaleTimeAdjust::doSet(void* target, const String& val)
	{
		static_cast<ImpactProjectorModule*>(target)->setScaleTimeAdjust(mIndex,
			Ogre::StringConverter::parseReal(val));
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void ImpactProjectorModule::CmdScaleTimeAdjust::doCopy(void* target, const void* source)
	{
		static_cast<ImpactProjectorModule *>(target)->setScaleTimeAdjust(mIndex,
			static_cast<const ImpactProjectorModule*>(source)->getScaleTimeAdjust(mIndex) );
	}
#endif
	//-----------------------------------------------------------------------
	String ImpactProjectorModule::CmdColourAdjust::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const ImpactProjectorModule*>(target)->getColourAdjust(mIndex) );
	}
	void ImpactProjectorModule::CmdColourAdjust::doSet(void* target, const String& val)
	{
		static_cast<ImpactProjectorModule*>(target)->setColourAdjust(mIndex,
			Ogre::StringConverter::parseColourValue(val));
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void ImpactProjectorModule::CmdColourAdjust::doCopy(void* target, const void* source)
	{
		static_cast<ImpactProjectorModule *>(target)->setColourAdjust(mIndex,
			static_cast<const ImpactProjectorModule*>(source)->getColourAdjust(mIndex) );
	}
#endif
	//-----------------------------------------------------------------------
	String ImpactProjectorModule::CmdColourTimeAdjust::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const ImpactProjectorModule*>(target)->getColourTimeAdjust(mIndex) );
	}
	void ImpactProjectorModule::CmdColourTimeAdjust::doSet(void* target, const String& val)
	{
		static_cast<ImpactProjectorModule*>(target)->setColourTimeAdjust(mIndex,
			Ogre::StringConverter::parseReal(val));
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void ImpactProjectorModule::CmdColourTimeAdjust::doCopy(void* target, const void* source)
	{
		static_cast<ImpactProjectorModule *>(target)->setColourTimeAdjust(mIndex,
			static_cast<const ImpactProjectorModule*>(source)->getColourTimeAdjust(mIndex) );
	}
#endif
	//-----------------------------------------------------------------------
	String ImpactProjectorModule::CmdScaleChangeTime::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const ImpactProjectorModule*>(target)->getScaleChangeTime() );
	}
	void ImpactProjectorModule::CmdScaleChangeTime::doSet(void* target, const String& val)
	{
		static_cast<ImpactProjectorModule*>(target)->setScaleChangeTime(
			Ogre::StringConverter::parseReal(val));
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void ImpactProjectorModule::CmdScaleChangeTime::doCopy(void* target, const void* source)
	{
		static_cast<ImpactProjectorModule *>(target)->setScaleChangeTime(
			static_cast<const ImpactProjectorModule*>(source)->getScaleChangeTime() );
	}
#endif
	//-----------------------------------------------------------------------
	String ImpactProjectorModule::CmdColourChangeTime::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const ImpactProjectorModule*>(target)->getColourChangeTime() );
	}
	void ImpactProjectorModule::CmdColourChangeTime::doSet(void* target, const String& val)
	{
		static_cast<ImpactProjectorModule*>(target)->setColourChangeTime(
			Ogre::StringConverter::parseReal(val));
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void ImpactProjectorModule::CmdColourChangeTime::doCopy(void* target, const void* source)
	{
		static_cast<ImpactProjectorModule *>(target)->setColourChangeTime(
			static_cast<const ImpactProjectorModule*>(source)->getColourChangeTime() );
	}
#endif
	//-----------------------------------------------------------------------
	String ImpactProjectorModule::CmdShowFrustum::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const ImpactProjectorModule*>(target)->getShowFrustum() );
	}
	void ImpactProjectorModule::CmdShowFrustum::doSet(void* target, const String& val)
	{
		static_cast<ImpactProjectorModule*>(target)->setShowFrustum(
			Ogre::StringConverter::parseBool(val));
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void ImpactProjectorModule::CmdShowFrustum::doCopy(void* target, const void* source)
	{
		static_cast<ImpactProjectorModule *>(target)->setShowFrustum(
			static_cast<const ImpactProjectorModule*>(source)->getShowFrustum() );
	}
#endif
	//-----------------------------------------------------------------------
	String ImpactProjectorModule::CmdNearClipDistance::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const ImpactProjectorModule*>(target)->getNearClipDistance() );
	}
	void ImpactProjectorModule::CmdNearClipDistance::doSet(void* target, const String& val)
	{
		static_cast<ImpactProjectorModule*>(target)->setNearClipDistance(
			Ogre::StringConverter::parseReal(val));
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void ImpactProjectorModule::CmdNearClipDistance::doCopy(void* target, const void* source)
	{
		static_cast<ImpactProjectorModule *>(target)->setNearClipDistance(
			static_cast<const ImpactProjectorModule*>(source)->getNearClipDistance() );
	}
#endif
	//-----------------------------------------------------------------------
	String ImpactProjectorModule::CmdFarClipDistance::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const ImpactProjectorModule*>(target)->getFarClipDistance() );
	}
	void ImpactProjectorModule::CmdFarClipDistance::doSet(void* target, const String& val)
	{
		static_cast<ImpactProjectorModule*>(target)->setFarClipDistance(
			Ogre::StringConverter::parseReal(val));
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void ImpactProjectorModule::CmdFarClipDistance::doCopy(void* target, const void* source)
	{
		static_cast<ImpactProjectorModule *>(target)->setFarClipDistance(
			static_cast<const ImpactProjectorModule*>(source)->getFarClipDistance() );
	}
#endif
}