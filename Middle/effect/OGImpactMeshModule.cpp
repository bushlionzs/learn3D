#include "OgreHeader.h"
#include "OGImpactMeshModule.h"
#include "OGImpact.h"

#include <OgreSceneNode.h>
#include <OgreStringConverter.h>
#include <OgreEntity.h>
#include <OgreSceneManager.h>
#include <OgreMeshManager.h>
#include <OgreSubEntity.h>
#include <OgreSubMesh.h>
#include <OgreParticleAffector.h>
#include <platform_log.h>
#include "OGImpactSerializer.h"
#include "engine_manager.h"
#include "OgreString.h"

namespace Orphigine	{

	ImpactMeshModule::CmdMeshName ImpactMeshModule::msMeshNameCmd;
	ImpactMeshModule::CmdMaterialName ImpactMeshModule::msMaterialNameCmd;

	ImpactMeshModule::ImpactMeshModule(const String &type) :
	ImpactModule(type),
		mEntity(NULL),
		mMeshName(""), mMaterialName("none")
	{
		if ( initDefaults(mElementType) )
		{
			Ogre::ParamDictionary* dict = getParamDictionary();

			// Custom params      
			dict->addParameter(Ogre::ParameterDef("MeshName", 
				"the name of mesh.",
				Ogre::PT_STRING),&msMeshNameCmd);  

			dict->addParameter(Ogre::ParameterDef("Material", 
				"the name of material.",
				Ogre::PT_STRING),&msMaterialNameCmd);  
		}
	}
	//---------------------------------------------------------------------
	ImpactMeshModule::~ImpactMeshModule()
	{
		destroyRenderInstance();
	}
	//---------------------------------------------------------------------
	bool ImpactMeshModule::createRenderInstance(void)
	{
		return _createMesh();
	}
	//---------------------------------------------------------------------
	void ImpactMeshModule::destroyRenderInstance(void)
	{	
		_destroyMesh();  

		ImpactModule::destroyRenderInstance();
	}
	//---------------------------------------------------------------------
	void ImpactMeshModule::destroyMe(void)
	{
		ImpactModule::destroyMe();
	}
	//---------------------------------------------------------------------
	bool ImpactMeshModule::_createMesh(void)
	{
		assert ( NULL == mEntity );
		//assert ( false == mMeshName.empty() );

		if ( false == mMeshName.empty() )
		{
			if (mBasicNode)
			{
				assert (mEffectParent);

				auto sceneMgr = EngineManager::getSingleton().getSceneManager();
				mEntity = sceneMgr->createEntity(mBasicNode->getName(), mMeshName );
				assert (mEntity);
				mEntity->setMaterialName(mMaterialName);
				mEntity->setCastShadows(false);

				mEntity->setVisible(mVisible);

				mBasicNode->attachObject(mEntity);
				mBasicNode->setPosition(mRelPos);
				mBasicNode->setOrientation(mRelOrientation);

				return true;
			}
		}		

		return false;
	}
	//---------------------------------------------------------------------
	void ImpactMeshModule::_destroyMesh(void)
	{
		if (mEntity)
		{
			assert(mBasicNode);
			Ogre::SceneManager* creator = mBasicNode->getCreator();
			assert(creator);       

			String meshName = mEntity->getMesh()->getName();

			mBasicNode->detachObject(mEntity->getName());
#if ((OGRE_VERSION_MAJOR << 16) | (OGRE_VERSION_MINOR << 8) | OGRE_VERSION_PATCH) >= 0x010100
			creator->destroyMovableObject(mEntity);
#else
			creator->removeEntity(mEntity->getName());
#endif
			mEntity = NULL;

		}
	}
	//---------------------------------------------------------------------
	void ImpactMeshModule::setMeshName(const String &name)
	{
		mMeshName = name;

		_destroyMesh();

		mIsRenderInstanceCreated = false;
	}
	//---------------------------------------------------------------------
	void ImpactMeshModule::setMaterialName(const String &name)
	{
		mMaterialName = name;

		if (mEntity)
		{
			// if this is "none",we will use the origin material of the mesh
			if (mMaterialName == "none")
			{

				if ( false == mMeshName.empty() )
				{
					Ogre::MeshPtr currentMesh = Ogre::MeshManager::getSingleton().getByName(mMeshName);

					for ( unsigned short i=0; i<currentMesh->getSubMeshCount(); ++i )
					{
						mEntity->getSubEntity(i)->setMaterialName( currentMesh->getSubMesh(i)->getMaterialName() );
					}
				}
			}		
			else
				mEntity->setMaterialName(mMaterialName);
		}		
	}
	//-----------------------------------------------------------------------
	void ImpactMeshModule::setVisibleFlag(uint32 flags)
	{
		if (mEntity)
			mEntity->setVisibilityFlags(flags);
	}
	//-----------------------------------------------------------------------
	///*
	char * ImpactMeshModule::readFromBuffer(char * pCurrent)
	{
		pCurrent = ImpactModule::readFromBuffer(pCurrent);

		String strTemp;
		Ogre::StringUtil::loadStringFromMemory(strTemp,pCurrent);
		setMeshName(strTemp);

		Ogre::StringUtil::loadStringFromMemory(strTemp,pCurrent);
		setMaterialName(strTemp);

		return pCurrent;
	}
	//-----------------------------------------------------------------------
	void ImpactMeshModule::saveToFile(std::ofstream & of)
	{
	}
	//*/
	bool ImpactMeshModule::loadFromStream(Ogre::Serializer* pSerializer,Ogre::DataStreamPtr& stream)
	{
		if(pSerializer && stream->eof() == false)
		{
			unsigned short id = pSerializer->readChunk(stream);
			if(id != ImpactSerializer::EFF_MESH_ELEMENT)
			{
				WARNING_LOG("Load MeshElement From Stream Failed. ChunkId Error");
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
			String meshName = pSerializer->readStringBin(stream);
			setMeshName(meshName);
			String materialName = pSerializer->readStringBin(stream);
			setMaterialName(materialName);
			return true;			
		}
		return false;
	}
	bool ImpactMeshModule::saveToBinaryFile(Ogre::Serializer* pSerializer)
	{
		
		return false;
	}
	std::size_t	ImpactMeshModule::calcSerializedSize()
	{
		size_t tmpSize = Ogre::Serializer::STREAM_OVERHEAD_SIZE;
		//基类成员
		tmpSize += sizeof(mStartTime);
		tmpSize += sizeof(mLifeTime);
		tmpSize += sizeof(mRelPos);
		tmpSize += sizeof(mRelOrientation);
		//自身成员
		tmpSize += mMeshName.length() + 1;	
		tmpSize += mMaterialName.length() + 1;	
		return tmpSize;
	}

	///////////////////////////////////////////
	String ImpactMeshModule::CmdMeshName::doGet(const void* target) const
	{
		return static_cast<const ImpactMeshModule*>(target)->getMeshName();
	}
	void ImpactMeshModule::CmdMeshName::doSet(void* target, const String& val)
	{
		static_cast<ImpactMeshModule *>(target)->setMeshName(val);
	}    
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void ImpactMeshModule::CmdMeshName::doCopy(void* target, const void* source)
	{
		static_cast<ImpactMeshModule *>(target)->setMeshName(
			static_cast<const ImpactMeshModule*>(source)->getMeshName() );
	}
#endif

	String ImpactMeshModule::CmdMaterialName::doGet(const void* target) const
	{
		return static_cast<const ImpactMeshModule*>(target)->getMaterialName();
	}
	void ImpactMeshModule::CmdMaterialName::doSet(void* target, const String& val)
	{
		static_cast<ImpactMeshModule *>(target)->setMaterialName(val);
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void ImpactMeshModule::CmdMaterialName::doCopy(void* target, const void* source)
	{
		static_cast<ImpactMeshModule *>(target)->setMaterialName(
			static_cast<const ImpactMeshModule*>(source)->getMaterialName() );
	}
#endif
}