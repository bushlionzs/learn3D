#include "OgreHeader.h"
#include "OgreMeshComponentParticleRenderer.h"
#include "OgreStringConverter.h"
#include "OgreMeshComponentParticleVisualData.h"
#include "OgreMaterialManager.h"
#include "OgreNode.h"
#include "OgreParticleAffector.h"
#include "OgreParticleSystem.h"
#include "OgreSerializer.h"
#include "platform_log.h"
#include "OgreString.h"

namespace Ogre	{

	MeshComponentParticleRenderer::CmdMeshName MeshComponentParticleRenderer::msMeshNameCmd;
	MeshComponentParticleRenderer::CmdOrientType MeshComponentParticleRenderer::msOrientationTypeCmd;

	String MeshComponentParticleRendererFactory::msRendererType =  "mesh";
	//-----------------------------------------------------------------------
	MeshComponentParticleRenderer::MeshComponentParticleRenderer() :
	mMaterialName(""),
		mMeshName(""),
		mWorldSpace(false),
		mParticleSystemNode(NULL),
		mMeshRotation(false),
		mMeshSizeChanged(false),
		mDefaultWidth(1.0f),
		mDefaultHeight(1.0f),
		mMeshOrientationType(MOT_ORIENTED_ORIGIN),
		mNextPoolIndex(0)
	{		
		if (createParamDictionary("MeshComponentParticleRenderer"))
		{
			ParamDictionary* dict = getParamDictionary();
			dict->addParameter(ParameterDef("mesh_name", 
				"Mesh name",
				PT_STRING),
				&msMeshNameCmd);	

			dict->addParameter(ParameterDef("orientation_type", 
				"the orientation type of mesh particle",
				PT_STRING),
				&msOrientationTypeCmd);
		}

		_freeMeshComponentParticleVisualDatas();
	}
	//-----------------------------------------------------------------------
	MeshComponentParticleRenderer::~MeshComponentParticleRenderer()
	{
		_freeMeshComponentParticleVisualDatas();
	}
	//-----------------------------------------------------------------------
	const String& MeshComponentParticleRenderer::getType(void) const
	{
		//return meshRendererTypeName;
		return MeshComponentParticleRendererFactory::msRendererType;
	}
	//-----------------------------------------------------------------------
	void MeshComponentParticleRenderer::_updateRenderQueue(RenderQueue* queue, 
		std::list<Particle*>& currentParticles, bool cullIndividually)
	{		
		// not implement
	}
	//-----------------------------------------------------------------------
	void MeshComponentParticleRenderer::_notifyParticleMoved(std::list<Particle*>& currentParticles)
	{   
		// 如果送进来的粒子总数为0(有可能是调用了ParticleSystem::clear()),就马上隐藏所有的mesh particle
		if (currentParticles.size() == 0)
		{
			removeAllMeshParticle();
			return;
		}

		for (std::list<Particle*>::iterator i = currentParticles.begin();	
			i != currentParticles.end(); ++i)
		{
			Particle* p = *i;
			MeshComponentParticleVisualData *visualData = static_cast<MeshComponentParticleVisualData *>(p->getVisualData());

			if ( false == visualData->isInit() )
				visualData->createVisualData(mMeshName, mMaterialName, mParticleSystemNode);

			if (mWorldSpace)
				visualData->setPosition(mParticleSystemNode->_getDerivedOrientation().UnitInverse() *
				(p->mPosition - mParticleSystemNode->_getDerivedPosition()) / mParticleSystemNode->_getDerivedScale());
			else
				visualData->setPosition(p->mPosition);

			if (mMeshSizeChanged)
				visualData->setScale(p->mWidth, p->mHeight);
			else
				visualData->setScale(mDefaultWidth, mDefaultHeight);


			visualData->setColour(p->mColour);

			if (mMeshOrientationType == MOT_ORIENTED_SELF)
				visualData->setDirection(p->mDirection, mParticleSystemNode->_getDerivedOrientation());

			visualData->setOrientation(mMeshRotation, mParticleSystemNode->_getDerivedOrientation());

			if (visualData->mAnimationUpdated)
				visualData->updateAnimation();
			else
				visualData->resetAnimation();

			visualData->mAnimationUpdated = false;

			if (false == visualData->getVisible())
				visualData->setVisible(true);

		}        
	}
	//-----------------------------------------------------------------------
	void MeshComponentParticleRenderer::_notifyParticleExpired(Particle* particle)
	{
		MeshComponentParticleVisualData* data = static_cast<MeshComponentParticleVisualData*>(particle->getVisualData());
		if (data->isInit())
		{
			data->setVisible(false);
			data->resetAnimation();
		}
	}
	//-----------------------------------------------------------------------
	void MeshComponentParticleRenderer::_setMaterial(MaterialPtr& mat)
	{
		setMaterialName(mat->getName());
	}
	//-----------------------------------------------------------------------

	void MeshComponentParticleRenderer::_notifyCurrentCamera( Camera* cam )
	{

	}

	//-----------------------------------------------------------------------
	void MeshComponentParticleRenderer::_notifyParticleRotated(void)
	{
		mMeshRotation = true;
	}
	//-----------------------------------------------------------------------
	void MeshComponentParticleRenderer::_notifyDefaultDimensions(Real width, Real height)
	{
		mDefaultWidth = width;
		mDefaultHeight = height;
	}
	//-----------------------------------------------------------------------
	void MeshComponentParticleRenderer::_notifyParticleResized(void)
	{
		mMeshSizeChanged = true;
	}
	//-----------------------------------------------------------------------
	void MeshComponentParticleRenderer::_notifyParticleQuota(size_t equota)
	{
		size_t currentSize = mMeshComponentParticleVisualDataPool.size();

		if (currentSize >= equota)
			return;

		// 删除原来的
		_freeMeshComponentParticleVisualDatas();

		mMeshComponentParticleVisualDataPool.resize(equota);

		for (size_t i=0; i<mMeshComponentParticleVisualDataPool.size(); ++i)
		{
			mMeshComponentParticleVisualDataPool[i] = new MeshComponentParticleVisualData;
			mMeshComponentParticleVisualDataPool[i]->setRenderQueueGroup(mRenderQueue_ID);
		}

		mNextPoolIndex = 0;
	}
	//-----------------------------------------------------------------------
	void MeshComponentParticleRenderer::_notifyAttached(Node* parent, bool isTagPoint)
	{
		mParticleSystemNode = parent;
	}
	//-----------------------------------------------------------------------
	void MeshComponentParticleRenderer::setRenderQueueGroup(uint8 queueID)
	{
		mRenderQueue_ID = queueID;
		for (size_t i=0; i<mMeshComponentParticleVisualDataPool.size(); ++i)
		{
			mMeshComponentParticleVisualDataPool[i]->setRenderQueueGroup(queueID);
		}
	}
	//-----------------------------------------------------------------------
	void MeshComponentParticleRenderer::setKeepParticlesInLocalSpace(bool keepLocal)
	{
		mWorldSpace = !keepLocal;
	}
	//-----------------------------------------------------------------------
	Ogre::SortMode MeshComponentParticleRenderer::_getSortMode(void) const
	{
		return Ogre::SM_DISTANCE;
	}
	//-----------------------------------------------------------------------
	ParticleVisualData* MeshComponentParticleRenderer::_createVisualData(void)
	{
		if (mMeshComponentParticleVisualDataPool.size() <= mNextPoolIndex)
			_notifyParticleQuota(mNextPoolIndex+1);
		//end

		MeshComponentParticleVisualData* visualData = mMeshComponentParticleVisualDataPool[mNextPoolIndex];

		assert (mNextPoolIndex < mMeshComponentParticleVisualDataPool.size());
		visualData->setPoolIndex( mNextPoolIndex );

		// 数组下标递增
		++mNextPoolIndex;

		return visualData;
	}
	//-----------------------------------------------------------------------
	void MeshComponentParticleRenderer::_destroyVisualData(ParticleVisualData* vis)
	{
		if (vis)
		{
			size_t index = static_cast<MeshComponentParticleVisualData*>(vis)->getPoolIndex();

			delete mMeshComponentParticleVisualDataPool[index];
			mMeshComponentParticleVisualDataPool[index] = NULL;            
		}
		// 这里并不需要把mMeshParticleVisualDataPool中的对应项erase，因为MeshParticleVisualData
		// 记录的是mMeshParticleVisualDataPool的下标，如果erase，会使这个下标实效
	}
	//-----------------------------------------------------------------------
	void MeshComponentParticleRenderer::removeAllMeshParticle(void)
	{
		for ( MeshComponentParticleVisualDataPool::iterator i = mMeshComponentParticleVisualDataPool.begin();
			i != mMeshComponentParticleVisualDataPool.end(); ++i )
		{
			MeshComponentParticleVisualData* data = *i;
			if (data && data->isInit())
			{
				data->setVisible(false);
				data->resetAnimation();
			}
		}
	}
	//---------------------------------------------------------------------
	void MeshComponentParticleRenderer::setMeshName(const String &name)
	{
		mMeshName = name;

		for ( MeshComponentParticleVisualDataPool::iterator i = mMeshComponentParticleVisualDataPool.begin();
			i != mMeshComponentParticleVisualDataPool.end(); ++i )
		{
			if (*i)
			{
				if ( (*i)->isInit() )
					(*i)->modifyMesh(name);
			}
		}
	}
	//---------------------------------------------------------------------
	void MeshComponentParticleRenderer::_freeMeshComponentParticleVisualDatas(void)
	{
		for ( MeshComponentParticleVisualDataPool::iterator i = mMeshComponentParticleVisualDataPool.begin();
			i != mMeshComponentParticleVisualDataPool.end(); ++i )
		{
			if (*i)
			{
				delete *i;
				*i = NULL;
			}
		}
		mMeshComponentParticleVisualDataPool.clear();		
	}
	//-----------------------------------------------------------------------
	void MeshComponentParticleRenderer::setMaterialName( const String& name )
	{
		mMaterialName = name;

		if ( "" != mMaterialName )
		{
			mpMaterial = MaterialManager::getSingleton().getByName(name);

			if (!mpMaterial)
				OGRE_EXCEPT( Exception::ERR_ITEM_NOT_FOUND, "Could not find material " + name,
				"BillboardSet::setMaterialName" );

			//todo
			//mpMaterial->load();
		}

		for ( MeshComponentParticleVisualDataPool::iterator i = mMeshComponentParticleVisualDataPool.begin();
			i != mMeshComponentParticleVisualDataPool.end(); ++i )
		{
			if (*i)
			{
				if ( (*i)->isInit() )
					(*i)->modifyMaterial(name);
			}
		}
	}
	//-----------------------------------------------------------------------
	void MeshComponentParticleRenderer::setMeshOrientationType(MeshOrientationType mot)
	{
		mMeshOrientationType = mot;

		if (mMeshOrientationType == MOT_ORIENTED_ORIGIN)
		{
			for ( MeshComponentParticleVisualDataPool::iterator i = mMeshComponentParticleVisualDataPool.begin();
				i != mMeshComponentParticleVisualDataPool.end(); ++i )
			{
				if (*i)
				{
					if ( (*i)->isInit() )
						(*i)->setOrientation(Quaternion::IDENTITY);
				}
			}
		}
	}
	//-----------------------------------------------------------------------
	MeshOrientationType MeshComponentParticleRenderer::getMeshOrientationType(void) const
	{
		return mMeshOrientationType;
	}
	//-----------------------------------------------------------------------
	///*
	char * MeshComponentParticleRenderer::readFromBuffer(char * pCurrent)
	{

		String strMeshName;
		StringUtil::loadStringFromMemory(strMeshName,pCurrent);

		setMeshName(strMeshName);

		MeshOrientationType mot;
		mot = *((MeshOrientationType *)pCurrent);
		pCurrent += sizeof(MeshOrientationType);
		setMeshOrientationType(mot);

		return pCurrent;
	}
	void MeshComponentParticleRenderer::saveToFile(std::ofstream & of)
	{
		StringUtil::saveStringToStream(mMeshName,of);
		of.write((const char *)(&mMeshOrientationType),sizeof(MeshOrientationType));
	}
	bool MeshComponentParticleRenderer::loadFromStream(Ogre::Serializer* pSerializer,Ogre::DataStreamPtr& stream)
	{
		if(pSerializer && stream->eof() == false)
		{
			unsigned short chunkId = pSerializer->readChunk(stream);
			if(chunkId != Ogre::ParticleSystem::PSFF_MESH_PARTICLE_RENDER)
			{
				WARNING_LOG("Load MeshComponentParticleRenderer From Stream Failed. ChunkId Error");
				// 因为不读取，所以直接跳过相应数据段长
				pSerializer->skipChunk(stream);
				return false;
			}
			//属性
			String meshName = pSerializer->readStringBin(stream);
			setMeshName(meshName);
			String materialName = pSerializer->readStringBin(stream);
			setMaterialName(materialName);
			pSerializer->readData(stream,&mWorldSpace,1,sizeof(mWorldSpace));
			pSerializer->readData(stream,&mMeshRotation,1,sizeof(mMeshRotation));
			pSerializer->readData(stream,&mMeshSizeChanged,1,sizeof(mMeshSizeChanged));
			pSerializer->readData(stream,&mMeshOrientationType,1,sizeof(mMeshOrientationType));
			return true;
		}
		return false;
	}
	bool MeshComponentParticleRenderer::saveToBinaryFile(Ogre::Serializer* pSerializer)
	{
		
		return false;
	}
	std::size_t	MeshComponentParticleRenderer::calcSerializedSize()
	{
		size_t tmpSize = Ogre::Serializer::STREAM_OVERHEAD_SIZE;
		//属性
		tmpSize += mMeshName.length() + 1;	
		tmpSize += mMaterialName.length() + 1;	
		tmpSize += sizeof(mWorldSpace);
		tmpSize += sizeof(mMeshRotation);
		tmpSize += sizeof(mMeshSizeChanged);
		tmpSize += sizeof(mMeshOrientationType);
		return tmpSize;
	}	
	//////////////////////////////////////////////////////////////////////////
	String MeshComponentParticleRenderer::CmdMeshName::doGet(const void* target) const
	{
		return static_cast<const MeshComponentParticleRenderer*>(target)->getMeshName();
	}
	void MeshComponentParticleRenderer::CmdMeshName::doSet(void* target, const String& val)
	{
		static_cast<MeshComponentParticleRenderer *>(target)->setMeshName(val);
	}
	//-----------------------------------------------------------------------
	String MeshComponentParticleRenderer::CmdOrientType::doGet(const void* target) const
	{
		MeshOrientationType t = static_cast<const MeshComponentParticleRenderer*>(target)->getMeshOrientationType();
		switch(t)
		{
		case MOT_ORIENTED_ORIGIN:
			return "oriented_origin";

		case MOT_ORIENTED_SELF:
			return "oriented_self";

		}
		// Compiler nicety
		return "oriented_origin";
	}
	void MeshComponentParticleRenderer::CmdOrientType::doSet(void* target, const String& val)
	{
		MeshOrientationType t;
		if (val == "oriented_origin")
		{
			t = MOT_ORIENTED_ORIGIN;
		}
		else if (val == "oriented_self")
		{
			t = MOT_ORIENTED_SELF;
		}		
		else
		{
			OGRE_EXCEPT(Exception::ERR_INVALIDPARAMS, 
				"Invalid mesh orientation type '" + val + "'", 
				"MeshComponentParticleRenderer::CmdOrientType::doSet");
		}

		static_cast<MeshComponentParticleRenderer*>(target)->setMeshOrientationType(t);
	}

}