#include "OgreHeader.h"
#include "OgreTexcoordBillboardParticleRenderer.h"
#include "OgreParticle.h"
#include "OgreStringConverter.h"
#include "OgreSerializer.h"
#include "OgreParticleSystem.h"
#include "platform_log.h"
#include "OgreBillboard.h"

namespace Ogre {

	String TexCoordBillboardParticleRendererFactory::msRendererType = "texcoord_billboard";

	struct BillboardForTexcoordBillboardRenderer : public Billboard
	{
	public:
		void _setDimensions(bool o, Real w, Real h)
		{
			if (mOwnDimensions = o)
			{
				mWidth = w;
				mHeight = h;
			}
		}
	};

	//-----------------------------------------------------------------------
	TexCoordBillboardParticleRenderer::CmdTexcoordStacks TexCoordBillboardParticleRenderer::msTexcoordStacksCmd;
	TexCoordBillboardParticleRenderer::CmdTexcoordSlices TexCoordBillboardParticleRenderer::msTexcoordSlicesCmd;
	TexCoordBillboardParticleRenderer::CmdTexcoordRepeatTimes TexCoordBillboardParticleRenderer::msTexcoordRepeatTimesCmd;

	//-----------------------------------------------------------------------
	TexCoordBillboardParticleRenderer::TexCoordBillboardParticleRenderer()
	{
		if (createParamDictionary("TexCoordBillboardParticleRenderer"))
		{
			ParamDictionary* dict = getParamDictionary();
			dict->addParameter(ParameterDef("billboard_type", 
				"The type of billboard to use.",
				PT_STRING),
				&msBillboardTypeCmd);

			dict->addParameter(ParameterDef("billboard_origin", 
				"This setting controls the fine tuning of where a billboard appears in relation to it's position. "
				"Possible value are: 'top_left', 'top_center', 'top_right', 'center_left', 'center', 'center_right', "
				"'bottom_left', 'bottom_center' and 'bottom_right'. Default value is 'center'.",
				PT_STRING),
				&msBillboardOriginCmd);

			dict->addParameter(ParameterDef("billboard_rotation_type", 
				"This setting controls the billboard rotation type. "
				"'vertex' means rotate the billboard's vertices around their facing direction."
				"'texcoord' means rotate the billboard's texture coordinates. Default value is 'texcoord'.",
				PT_STRING),
				&msBillboardRotationTypeCmd);

			dict->addParameter(ParameterDef("common_direction", 
				"Only useful when billboard_type is oriented_common or perpendicular_common. ",
				PT_VECTOR3),
				&msCommonDirectionCmd);

			dict->addParameter(ParameterDef("common_up_vector",
				"Only useful when billboard_type is perpendicular_self or perpendicular_common.",
				PT_VECTOR3),
				&msCommonUpVectorCmd);

			dict->addParameter(ParameterDef("point_rendering",
				"Set whether or not particles will use point rendering "
				"Possible values are 'true' or 'false'.",
				PT_BOOL),
				&msPointRenderingCmd);
			dict->addParameter(ParameterDef("accurate_facing",
				"Set whether or not particles will be oriented to the camera "
				"Cannot be combined with point rendering.",
				PT_BOOL),
				&msAccurateFacingCmd);

			dict->addParameter(ParameterDef("speed_relatived_size_factor",
				"Sets the factor of the particle size relative to speed.",
				PT_REAL),
				&msSpeedRelativedSizeFactorCmd);

			dict->addParameter(ParameterDef("stacks", 
				"the stacks of texture coordinates.",
				PT_UNSIGNED_LONG),
				&msTexcoordStacksCmd);

			dict->addParameter(ParameterDef("slices",
				"the slices of texture coordinates.",
				PT_UNSIGNED_LONG),
				&msTexcoordSlicesCmd);

			dict->addParameter(ParameterDef("repeat_times", 
				"the repeat times of the colour interpolate.",
				PT_REAL), &msTexcoordRepeatTimesCmd);
		}

		mTexcoordStacks = 1;
		mTexcoordSlices = 1;

		mTexcoordRepeatTimes = 1.0f;
	}
	//-----------------------------------------------------------------------
	const String& TexCoordBillboardParticleRenderer::getType(void) const
	{
		//return rendererTypeName;
		return TexCoordBillboardParticleRendererFactory::msRendererType;
	}	
	//-----------------------------------------------------------------------
	void TexCoordBillboardParticleRenderer::_updateRenderQueue(RenderQueue* queue, 
		std::list<Particle*>& currentParticles, bool cullIndividually)
	{	
		BillboardSet* billboardset = getBillboardSet();
		billboardset->setCullIndividually(cullIndividually);

		ulong numTexCoords = mTexcoordSlices * mTexcoordStacks;
		Real life_time = 0.0f;
		Real particle_time = 0.0f;
		Real repeatedParticleTime = 0.0f;
		uint16 texCoords = 0;

		billboardset->beginBillboards();
		BillboardForTexcoordBillboardRenderer bb;

		for (std::list<Particle*>::iterator i = currentParticles.begin();
			i != currentParticles.end(); ++i)
		{
			Particle* p = *i;
			bb.mPosition = p->mPosition;

			switch (billboardset->getBillboardType())
			{
			case BBT_ORIENTED_SELF:
				if (mSpeedRelativedSizeFactor > 0)
				{
					bb.mDirection = p->mDirection;
					bb.mDirection *= mSpeedRelativedSizeFactor;
					break;
				}
			case BBT_PERPENDICULAR_SELF:
				bb.mDirection = p->mDirection;
				bb.mDirection.normalise();
				break;
			}

			life_time		= p->mTotalTimeToLive;
			particle_time	= 1.0f - (p->mTimeToLive / life_time);

			repeatedParticleTime = fmod( particle_time * mTexcoordRepeatTimes, 1.0f );
			texCoords = (uint16)(repeatedParticleTime * numTexCoords);

			if (texCoords == numTexCoords)
				--texCoords;

			bb.mColour = p->mColour;
			bb.mRotation = p->mRotation;
			bb.setTexcoordIndex(texCoords);
			bb._setDimensions(true, p->mWidth, p->mHeight); 
			billboardset->injectBillboard(bb);
		}

		billboardset->endBillboards();

		// Update the queue
		billboardset->_updateRenderQueue(queue);
	}
	//-----------------------------------------------------------------------
	void TexCoordBillboardParticleRenderer::setTexcoordStacks(ulong stacks)
	{
		if (stacks < 1)
			mTexcoordStacks = 1;
		else
			mTexcoordStacks = stacks;

		getBillboardSet()->setTextureStacksAndSlices((uchar)mTexcoordStacks, (uchar)mTexcoordSlices);
	}

	ulong TexCoordBillboardParticleRenderer::getTexcoordStacks( void ) const
	{
		return mTexcoordStacks;
	}

	//-----------------------------------------------------------------------
	void TexCoordBillboardParticleRenderer::setTexcoordSlices(ulong slices)
	{
		if (slices < 1)
			mTexcoordSlices = 1;
		else
			mTexcoordSlices = slices;

		getBillboardSet()->setTextureStacksAndSlices((uchar)mTexcoordStacks, (uchar)mTexcoordSlices);
	}

	ulong TexCoordBillboardParticleRenderer::getTexcoordSlices( void ) const
	{
		return mTexcoordSlices;
	}

	void TexCoordBillboardParticleRenderer::setTexcoordRepeatTimes( Real times )
	{
		mTexcoordRepeatTimes = times;
	}

	Ogre::Real TexCoordBillboardParticleRenderer::getTexcoordRepeatTimes( void ) const
	{
		return mTexcoordRepeatTimes;
	}
	//-----------------------------------------------------------------------
	//
	char * TexCoordBillboardParticleRenderer::readFromBuffer(char * pCurrent)
	{
		//写入BillboardParticleRenderer类的属性
		//pCurrent = BillboardParticleRenderer::readFromBuffer(pCurrent);

		//todo123
		int length = sizeof(unsigned long) * 2 + sizeof(Ogre::Real);
		memcpy(&mTexcoordStacks,pCurrent,length);
		pCurrent += length;

		return pCurrent;
	}

	void TexCoordBillboardParticleRenderer::saveToFile(std::ofstream & of)
	{
	}
	bool TexCoordBillboardParticleRenderer::loadFromStream(Ogre::Serializer* pSerializer,Ogre::DataStreamPtr& stream)
	{
		if(pSerializer && stream->eof() == false)
		{
			unsigned short chunkId = pSerializer->readChunk(stream);
			if(chunkId != Ogre::ParticleSystem::PSFF_TEXCOORD_BILLBOARD_PARTICLE_RENDER)
			{
				WARNING_LOG("Load TexcoordBillboardParticleRenderer From Stream Failed. ChunkId Error");
				// 因为不读取，所以直接跳过相应数据段长
				pSerializer->skipChunk(stream);
				return false;
			}
			//基类
			BillboardParticleRenderer::loadFromStream(pSerializer,stream);
			//属性
			ulong stacks = 0;
			ulong slices = 0;
			Real repeatTimes = 0;
			pSerializer->readData(stream,&stacks,1,sizeof(stacks));
			pSerializer->readData(stream,&slices,1,sizeof(slices));
			pSerializer->readData(stream,&repeatTimes,1,sizeof(repeatTimes));
			setTexcoordStacks(stacks);
			setTexcoordSlices(slices);
			setTexcoordRepeatTimes(repeatTimes);
			return true;
		}
		return false;
	}
	bool TexCoordBillboardParticleRenderer::saveToBinaryFile(Ogre::Serializer* pSerializer)
	{
		
		return false;
	}
	std::size_t	TexCoordBillboardParticleRenderer::calcSerializedSize()
	{
		return 0;
	}

	//-----------------------------------------------------------------------
	//-----------------------------------------------------------------------	
	//-----------------------------------------------------------------------
	String TexCoordBillboardParticleRenderer::CmdTexcoordStacks::doGet(const void* target) const
	{
		return StringConverter::toString(
			static_cast<const TexCoordBillboardParticleRenderer*>(target)->getTexcoordStacks() );
	}
	void TexCoordBillboardParticleRenderer::CmdTexcoordStacks::doSet(void* target, const String& val)
	{
		static_cast<TexCoordBillboardParticleRenderer*>(target)->setTexcoordStacks(
			StringConverter::parseUnsignedInt(val));
	}
	//-----------------------------------------------------------------------
	String TexCoordBillboardParticleRenderer::CmdTexcoordSlices::doGet(const void* target) const
	{
		return StringConverter::toString(
			static_cast<const TexCoordBillboardParticleRenderer*>(target)->getTexcoordSlices() );
	}
	void TexCoordBillboardParticleRenderer::CmdTexcoordSlices::doSet(void* target, const String& val)
	{
		static_cast<TexCoordBillboardParticleRenderer*>(target)->setTexcoordSlices(
			StringConverter::parseUnsignedInt(val));
	}
	//-----------------------------------------------------------------------
	String TexCoordBillboardParticleRenderer::CmdTexcoordRepeatTimes::doGet(const void* target) const
	{
		return StringConverter::toString(
			static_cast<const TexCoordBillboardParticleRenderer*>(target)->getTexcoordRepeatTimes() );
	}
	void TexCoordBillboardParticleRenderer::CmdTexcoordRepeatTimes::doSet(void* target, const String& val)
	{
		static_cast<TexCoordBillboardParticleRenderer*>(target)->setTexcoordRepeatTimes(
			StringConverter::parseReal(val));
	}
}

