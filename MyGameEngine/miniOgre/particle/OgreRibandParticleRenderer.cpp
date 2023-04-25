#include "OgreHeader.h"
#include "OgreRibandParticleRenderer.h"
#include "OgreRibandSet.h"

#include <OgreNode.h>
#include <OgreStringConverter.h>
#include "OgreParticleSystem.h"
#include "OgreSerializer.h"
#include "platform_log.h"
#include "OgreMaterial.h"
#include "OgreCamera.h"

namespace Ogre
{

	String RibbonRendererFactory::msRendererType = "ribbon";

	RibandParticleRenderer::CmdHeadAlpha RibandParticleRenderer::msHeadAlphaCmd;
	RibandParticleRenderer::CmdTailAlpha RibandParticleRenderer::msTailAlphaCmd;
	RibandParticleRenderer::CmdHeadWidthScale RibandParticleRenderer::msHeadWidthScaleCmd;
	RibandParticleRenderer::CmdTailWidthScale RibandParticleRenderer::msTailWidthScaleCmd;
	RibandParticleRenderer::CmdElementCount RibandParticleRenderer::msElementCountCmd;

	RibandParticleRenderer::RibandParticleRenderer()
		: mRibbonSet(NULL)
		, mIsWorldSpace(false)
		, mNextRibbonIndex(0)
	{
		if (createParamDictionary("RibandParticleRenderer"))
		{
			ParamDictionary* dict = getParamDictionary();
			dict->addParameter(ParameterDef("head_alpha", 
				"the alpha value of the head of ribbon.",
				PT_REAL),
				&msHeadAlphaCmd);

			dict->addParameter(ParameterDef("tail_alpha", 
				"the alpha value of the tail of ribbon.",
				PT_REAL),
				&msTailAlphaCmd);

			dict->addParameter(ParameterDef("head_width_scale", 
				"the width scale value of the head of ribbon.",
				PT_REAL),
				&msHeadWidthScaleCmd);

			dict->addParameter(ParameterDef("tail_width_scale", 
				"the width scale value of the tail of ribbon.",
				PT_REAL),
				&msTailWidthScaleCmd);

			dict->addParameter(ParameterDef("element_count",
				"the element count of the ribbon.",
				PT_UNSIGNED_INT),
				&msElementCountCmd);
		}

		mRibbonSet = new RibandSet("", 15);
	}
	//-----------------------------------------------------------------------
	RibandParticleRenderer::~RibandParticleRenderer()
	{
		delete mRibbonSet;
	}
	//-----------------------------------------------------------------------
	void RibandParticleRenderer::setHeadAlpha(Real alpha)
	{
		mRibbonSet->setHeadAlpha(alpha);
	}
	//-----------------------------------------------------------------------
	Real RibandParticleRenderer::getHeadAlpha(void) const
	{
		return mRibbonSet->getHeadAlpha();
	}
	//-----------------------------------------------------------------------
	void RibandParticleRenderer::setTailAlpha(Real alpha)
	{
		mRibbonSet->setTailAlpha(alpha);
	}
	//-----------------------------------------------------------------------
	Real RibandParticleRenderer::getTailAlpha(void) const
	{
		return mRibbonSet->getTailAlpha();
	}
	//-----------------------------------------------------------------------
	void RibandParticleRenderer::setHeadWidthScale(Real width)
	{
		mRibbonSet->setHeadWidthScale(width);
	}
	//-----------------------------------------------------------------------
	Real RibandParticleRenderer::getHeadWidthScale(void) const
	{
		return mRibbonSet->getHeadWidthScale();
	}
	//-----------------------------------------------------------------------
	void RibandParticleRenderer::setTailWidthScale(Real width)
	{
		mRibbonSet->setTailWidthScale(width);
	}
	//-----------------------------------------------------------------------
	Real RibandParticleRenderer::getTailWidthScale(void) const
	{
		return mRibbonSet->getTailWidthScale();
	}
	//-----------------------------------------------------------------------
	void RibandParticleRenderer::setElementCount(size_t count)
	{
		mRibbonSet->setMaxChainElements(count);
	}
	//-----------------------------------------------------------------------
	size_t RibandParticleRenderer::getElementCount(void) const
	{
		return mRibbonSet->getMaxChainElements();
	}
	//-----------------------------------------------------------------------
	const String& RibandParticleRenderer::getType(void) const
	{
		return /*RibbonRendererType*/RibbonRendererFactory::msRendererType;
	}
	//-----------------------------------------------------------------------
	void RibandParticleRenderer::_updateRenderQueue(RenderQueue* queue, 
		std::list<Particle*>& currentParticles, bool cullIndividually)
	{
		mRibbonSet->_updateRenderQueue(queue);
	}
	//-----------------------------------------------------------------------
	void RibandParticleRenderer::_setMaterial(MaterialPtr& mat)
	{
		mRibbonSet->setMaterialName(mat->getName(), BLANKSTRING);
	}
	//-----------------------------------------------------------------------
	void RibandParticleRenderer::_notifyCurrentCamera(Camera* cam)
	{
		mRibbonSet->_notifyCurrentCamera(cam);
	}
	//-----------------------------------------------------------------------
	void RibandParticleRenderer::_notifyParticleMoved(std::list<Particle*>& currentParticles)
	{
		for (std::list<Particle*>::iterator i = currentParticles.begin();
			i != currentParticles.end(); ++i)
		{
			Particle* p = *i;

			RibbonParticleData* particleData = static_cast<RibbonParticleData*>(p->getVisualData());

			mRibbonSet->updateRiband( particleData->getRibbonIndex(), p->mPosition, mIsWorldSpace, p->mColour, p->mWidth );
		}
	}
	//-----------------------------------------------------------------------
	void RibandParticleRenderer::_notifyParticleRotated(void)
	{
	}
	//-----------------------------------------------------------------------
	void RibandParticleRenderer::_notifyParticleResized(void)
	{
		mRibbonSet->_notifyResized();
	}
	//-----------------------------------------------------------------------
	void RibandParticleRenderer::_notifyParticleQuota(size_t quota)
	{
		mRibbonSet->setNumberOfChains(quota);
	}
	//-----------------------------------------------------------------------
	void RibandParticleRenderer::_notifyAttached(Node* parent, bool isTagPoint)
	{
		mRibbonSet->_notifyAttached(parent, isTagPoint);
	}
	//-----------------------------------------------------------------------
	void RibandParticleRenderer::_notifyDefaultDimensions(Real width, Real height)
	{
		mRibbonSet->setDefaultSize(width, height);
	}
	//-----------------------------------------------------------------------
	void RibandParticleRenderer::setRenderQueueGroup(uint8 queueID)
	{
		
	}
	//-----------------------------------------------------------------------
	void RibandParticleRenderer::setKeepParticlesInLocalSpace(bool keepLocal)
	{
		mIsWorldSpace = !keepLocal;
	}
	//-----------------------------------------------------------------------
	Ogre::SortMode RibandParticleRenderer::_getSortMode(void) const
	{
		return Ogre::SM_DISTANCE;
	}
	//-----------------------------------------------------------------------
	ParticleVisualData* RibandParticleRenderer::_createVisualData(void)
	{
		assert (mNextRibbonIndex < mRibbonSet->getNumberOfChains());

		return new RibbonParticleData(mNextRibbonIndex++);
	}
	//-----------------------------------------------------------------------
	void RibandParticleRenderer::_destroyVisualData(ParticleVisualData* vis)
	{
		delete vis;
	}
	//-----------------------------------------------------------------------
	void RibandParticleRenderer::_notifyParticleExpired(Particle* particle)
	{
		RibbonParticleData* particleData = static_cast<RibbonParticleData*>(particle->getVisualData());

		mRibbonSet->resetRiband(particleData->getRibbonIndex());
	}
	//-----------------------------------------------------------------------
	///*
	char * RibandParticleRenderer::readFromBuffer(char * pCurrent)
	{
		if(mRibbonSet)
		{
			Real Temp[4];
			size_t elementCount;
			Temp[0]= *((Real*)pCurrent);
			pCurrent += sizeof(Real);
			Temp[1]= *((Real*)pCurrent);
			pCurrent += sizeof(Real);
			Temp[2]= *((Real*)pCurrent);
			pCurrent += sizeof(Real);
			Temp[3]= *((Real*)pCurrent);
			pCurrent += sizeof(Real);
			elementCount= *((size_t*)pCurrent);
			pCurrent += sizeof(size_t);

			mRibbonSet->setHeadAlpha(Temp[0]);    
			mRibbonSet->setTailAlpha(Temp[1]);    
			mRibbonSet->setHeadWidthScale(Temp[2]);    
			mRibbonSet->setTailWidthScale(Temp[3]);    
			mRibbonSet->setMaxChainElements(elementCount);
		}		
		return pCurrent;		
	}

	void RibandParticleRenderer::saveToFile(std::ofstream & of)
	{
		if(mRibbonSet)
		{
			Real Temp[4];
			Temp[0]=mRibbonSet->getHeadAlpha();
			Temp[1]=mRibbonSet->getTailAlpha();
			Temp[2]=mRibbonSet->getHeadWidthScale();
			Temp[3]=mRibbonSet->getTailWidthScale();
			size_t elementCount=mRibbonSet->getMaxChainElements();
			of.write((const char *)Temp,4*sizeof(Real));
			of.write((const char *)(&elementCount),sizeof(size_t));
		}
	}
	bool RibandParticleRenderer::loadFromStream(Ogre::Serializer* pSerializer,Ogre::DataStreamPtr& stream)
	{
		if(pSerializer && stream->eof() == false)
		{
			unsigned short chunkId = pSerializer->readChunk(stream);
			if(chunkId != Ogre::ParticleSystem::PSFF_RIBBON_RENDER)
			{
				WARNING_LOG("Load RibandParticleRenderer From Stream Failed. ChunkId Error");
				// 因为不读取，所以直接跳过相应数据段长
				pSerializer->skipChunk(stream);
				return false;
			}
			//属性
			assert(mRibbonSet);
			pSerializer->readData(stream,&mIsWorldSpace,1,sizeof(mIsWorldSpace));
			Real Temp[4];
			pSerializer->readData(stream,Temp,1,sizeof(Temp));
			size_t elementCount = 0;
			pSerializer->readData(stream,&elementCount,1,sizeof(elementCount));
			mRibbonSet->setHeadAlpha(Temp[0]);    
			mRibbonSet->setTailAlpha(Temp[1]);    
			mRibbonSet->setHeadWidthScale(Temp[2]);    
			mRibbonSet->setTailWidthScale(Temp[3]);    
			mRibbonSet->setMaxChainElements(elementCount);			
			return true;
		}
		return false;
	}
	bool RibandParticleRenderer::saveToBinaryFile(Ogre::Serializer* pSerializer)
	{
		
		return false;
	}
	std::size_t	RibandParticleRenderer::calcSerializedSize()
	{
		size_t tmpSize = Ogre::Serializer::STREAM_OVERHEAD_SIZE;
		//属性
		tmpSize += sizeof(mIsWorldSpace);
		tmpSize += 4*sizeof(Real);
		tmpSize += sizeof(size_t);
		return tmpSize;
	}
	//*/
	//-----------------------------------------------------------------------
	String RibandParticleRenderer::CmdHeadAlpha::doGet(const void* target) const
	{
		return StringConverter::toString(
			static_cast<const RibandParticleRenderer*>(target)->getHeadAlpha() );
	}
	void RibandParticleRenderer::CmdHeadAlpha::doSet(void* target, const String& val)
	{
		static_cast<RibandParticleRenderer*>(target)->setHeadAlpha(
			StringConverter::parseReal(val));
	}
	//-----------------------------------------------------------------------
	String RibandParticleRenderer::CmdTailAlpha::doGet(const void* target) const
	{
		return StringConverter::toString(
			static_cast<const RibandParticleRenderer*>(target)->getTailAlpha() );
	}
	void RibandParticleRenderer::CmdTailAlpha::doSet(void* target, const String& val)
	{
		static_cast<RibandParticleRenderer*>(target)->setTailAlpha(
			StringConverter::parseReal(val));
	}
	//-----------------------------------------------------------------------
	String RibandParticleRenderer::CmdHeadWidthScale::doGet(const void* target) const
	{
		return StringConverter::toString(
			static_cast<const RibandParticleRenderer*>(target)->getHeadWidthScale() );
	}
	void RibandParticleRenderer::CmdHeadWidthScale::doSet(void* target, const String& val)
	{
		static_cast<RibandParticleRenderer*>(target)->setHeadWidthScale(
			StringConverter::parseReal(val));
	}
	//-----------------------------------------------------------------------
	String RibandParticleRenderer::CmdTailWidthScale::doGet(const void* target) const
	{
		return StringConverter::toString(
			static_cast<const RibandParticleRenderer*>(target)->getTailWidthScale() );
	}
	void RibandParticleRenderer::CmdTailWidthScale::doSet(void* target, const String& val)
	{
		static_cast<RibandParticleRenderer*>(target)->setTailWidthScale(
			StringConverter::parseReal(val));
	}
	//-----------------------------------------------------------------------
	String RibandParticleRenderer::CmdElementCount::doGet(const void* target) const
	{
		return StringConverter::toString(
			static_cast<const RibandParticleRenderer*>(target)->getElementCount() );
	}
	void RibandParticleRenderer::CmdElementCount::doSet(void* target, const String& val)
	{
		static_cast<RibandParticleRenderer*>(target)->setElementCount(
			StringConverter::parseUnsignedInt(val));
	}
}