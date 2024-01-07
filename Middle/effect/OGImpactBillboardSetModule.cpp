#include "OgreHeader.h"
#include "OGImpactBillboardSetModule.h"


// ogre header
#include <OgreSceneManager.h>
#include <OgreBillboard.h>
#include <OgreBillboardSet.h>
#include <OgreStringConverter.h>
#include <OgreMath.h>
#include <platform_log.h>
#include "OGImpactSerializer.h"
#include "engine_manager.h"
#include "OgreSceneNode.h"

namespace Orphigine	
{

	ImpactBillboardSetModule::CmdBillboardColour ImpactBillboardSetModule::msBillboardColourCmd;
	ImpactBillboardSetModule::CmdBillboardScale ImpactBillboardSetModule::msBillboardScaleCmd[MAX_STAGES];
	ImpactBillboardSetModule::CmdScaleIntervalTime ImpactBillboardSetModule::msScaleIntervalTimeCmd;
	ImpactBillboardSetModule::CmdBillboardAlpha ImpactBillboardSetModule::msBillboardAlphaCmd;
	ImpactBillboardSetModule::CmdBillboardCount ImpactBillboardSetModule::msBillboardCountCmd;
	ImpactBillboardSetModule::CmdBillboardMaterial ImpactBillboardSetModule::msBillboardMaterialCmd;
	ImpactBillboardSetModule::CmdBillboardInterval ImpactBillboardSetModule::msBillboardIntervalCmd;
	ImpactBillboardSetModule::CmdBillboardHeight ImpactBillboardSetModule::msBillboardHeightCmd;
	ImpactBillboardSetModule::CmdBillboardWidth ImpactBillboardSetModule::msBillboardWidthCmd;
	ImpactBillboardSetModule::CmdStacks ImpactBillboardSetModule::msStacksCmd;
	ImpactBillboardSetModule::CmdSlices ImpactBillboardSetModule::msSlicesCmd;
	ImpactBillboardSetModule::CmdTexIntervalTime ImpactBillboardSetModule::msTexIntervalTimeCmd;

	//////////////////////////////////////////////////////////////////////////
	ImpactBillboardSetModule::ImpactBillboardSetModule(const String &type) :
	ImpactModule(type),
		mBillboardSet(NULL),
		mBillboardColour(Ogre::ColourValue::White),
		mScaleIntervalTime(0.1f),
		mSizeChanged(false),
		mBillboardCount(5),
		mBillboardMaterial("BaseWhiteNoLighting"),
		mBillboardInterval(10.0f),
		mBillboardWidth(100.0f),
		mBillboardHeight(100.0f),
		mAlphaValue(1.0f),
		mColourChanged(false),
		mStacks(1),
		mSlices(1),
		mTexIntervalTime(0.1f),
		mCurrentTexIntervalTime(0.0f)
	{
		for (int i=0; i<MAX_STAGES; ++i)
		{
			mBillboardScale[i] = Ogre::Vector3(1.0f, 1.0f, 1.0f);
		}

		if ( initDefaults(mElementType) )
		{
			Ogre::ParamDictionary* dict = getParamDictionary();

			// Custom params      

			dict->addParameter(Ogre::ParameterDef("BillboardColour", 
				"BillboardColour",
				Ogre::PT_COLOURVALUE), &msBillboardColourCmd);

			dict->addParameter(Ogre::ParameterDef("BillboardAlpha", 
				"Billboard Alpha Value of first point and second point.",
				Ogre::PT_REAL),&msBillboardAlphaCmd);

			dict->addParameter(Ogre::ParameterDef("BillboardCount", 
				"the life time of the vertex.",
				Ogre::PT_INT),&msBillboardCountCmd);

			dict->addParameter(Ogre::ParameterDef("Material", 
				"alpha factor of head point.",
				Ogre::PT_STRING),&msBillboardMaterialCmd);

			dict->addParameter(Ogre::ParameterDef("BillboardInterval", 
				"alpha factor of tail point.",
				Ogre::PT_REAL),&msBillboardIntervalCmd);

			dict->addParameter(Ogre::ParameterDef("BillboardHeight", 
				"alpha factor of tail point.",
				Ogre::PT_REAL),&msBillboardHeightCmd);

			dict->addParameter(Ogre::ParameterDef("BillboardWidth", 
				"alpha factor of tail point.",
				Ogre::PT_REAL),&msBillboardWidthCmd); 

			for (int i=0;i<MAX_STAGES;i++)
			{
				msBillboardScaleCmd[i].mIndex	= i;

				std::stringstream stage;
				stage << i;
				String	colour_title	= String("BillboardScale") + stage.str();
				String	colour_descr	= String("Stage ") + stage.str() +
					String(" BillboardScale of first point and second point.");

				dict->addParameter(Ogre::ParameterDef(colour_title, colour_descr,
					Ogre::PT_VECTOR3), &msBillboardScaleCmd[i]);
			}

			dict->addParameter(Ogre::ParameterDef("ScaleIntervalTime", 
				"the interval time of changing scale.",
				Ogre::PT_REAL),&msScaleIntervalTimeCmd);   

			dict->addParameter(Ogre::ParameterDef("stacks", 
				"the stacks of texture coordinates.",
				Ogre::PT_UNSIGNED_LONG),
				&msStacksCmd);

			dict->addParameter(Ogre::ParameterDef("slices",
				"the slices of texture coordinates.",
				Ogre::PT_UNSIGNED_LONG),
				&msSlicesCmd);

			dict->addParameter(Ogre::ParameterDef("TexIntervalTime", 
				"the interval time of changing texture index.",
				Ogre::PT_REAL),&msTexIntervalTimeCmd);   

		}    
	}
	//---------------------------------------------------------------------
	ImpactBillboardSetModule::~ImpactBillboardSetModule()
	{
		destroyRenderInstance();
	}	
	//---------------------------------------------------------------------
	bool ImpactBillboardSetModule::createRenderInstance(void)
	{
		return _createBillboardSet();
	}
	//---------------------------------------------------------------------
	void ImpactBillboardSetModule::destroyRenderInstance(void)
	{
		_destroyBillboardSet();

		ImpactModule::destroyRenderInstance();
	}
	bool ImpactBillboardSetModule::loadFromStream(Ogre::Serializer* pSerializer,Ogre::DataStreamPtr& stream)
	{
		if(pSerializer && stream->eof() == false)
		{
			unsigned short id = pSerializer->readChunk(stream);
			if(id != ImpactSerializer::EFF_BILLBOARDSET_ELEMENT)
			{
				WARNING_LOG("Load BillboardSetElement From Stream Failed. ChunkId Error");
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
			pSerializer->readData(stream,&mBillboardColour,1,sizeof(Ogre::ColourValue));
			pSerializer->readData(stream,&mBillboardCount,1,sizeof(int));
			String billboardMaterialName = pSerializer->readStringBin(stream);
			setBillboardMaterial(billboardMaterialName);
			pSerializer->readData(stream,&mBillboardInterval,1,sizeof(Ogre::Real));
			pSerializer->readData(stream,&mBillboardWidth,1,sizeof(Ogre::Real));
			pSerializer->readData(stream,&mBillboardHeight,1,sizeof(Ogre::Real));
			for (int i=0; i<MAX_STAGES; ++i)
			{
				pSerializer->readData(stream,&(mBillboardScale[i]),1,sizeof(ScaleValue));
			}
			pSerializer->readData(stream,&mScaleIntervalTime,1,sizeof(Ogre::Real));
			pSerializer->readData(stream,&mSizeChanged,1,sizeof(bool));	
			pSerializer->readData(stream,&mAlphaValue,1,sizeof(Ogre::Real));
			pSerializer->readData(stream,&mColourChanged,1,sizeof(bool));
			pSerializer->readData(stream,&mStacks,1,sizeof(ulong));
			pSerializer->readData(stream,&mSlices,1,sizeof(ulong));
			pSerializer->readData(stream,&mTexIntervalTime,1,sizeof(Ogre::Real));
			return true;			
		}
		return false;
	}
	bool ImpactBillboardSetModule::saveToBinaryFile(Ogre::Serializer* pSerializer)
	{
		
		return false;
	}
	std::size_t	ImpactBillboardSetModule::calcSerializedSize()
	{
		size_t tmpSize = Ogre::Serializer::STREAM_OVERHEAD_SIZE;
		//基类成员
		tmpSize += sizeof(mStartTime);
		tmpSize += sizeof(mLifeTime);
		tmpSize += sizeof(mRelPos);
		tmpSize += sizeof(mRelOrientation);
		//自身成员
		tmpSize += sizeof(mBillboardColour);
		tmpSize += sizeof(mBillboardCount);
		tmpSize += mBillboardMaterial.length() + 1;	
		tmpSize += sizeof(mBillboardInterval);
		tmpSize += sizeof(mBillboardWidth);
		tmpSize += sizeof(mBillboardHeight);
		for (int i=0; i<MAX_STAGES; ++i)
		{
			tmpSize += sizeof(mBillboardScale[i]);
		}
		tmpSize += sizeof(mScaleIntervalTime);
		tmpSize += sizeof(mSizeChanged);
		tmpSize += sizeof(mAlphaValue);
		tmpSize += sizeof(mColourChanged);
		tmpSize += sizeof(mStacks);
		tmpSize += sizeof(mSlices);
		tmpSize += sizeof(mTexIntervalTime);
		return tmpSize;
	}

	//---------------------------------------------------------------------
	bool ImpactBillboardSetModule::_createBillboardSet(void)
	{
		Ogre::SceneNode* parent = mBasicNode;

		if (parent)
		{
			auto sceneMgr = EngineManager::getSingleton().getSceneManager();
			mBillboardSet = sceneMgr->createBillboardSet( parent->getName() );
			mBillboardSet->setMaterialName(mBillboardMaterial, BLANKSTRING);

			if ( (mStacks > 1) || (mSlices > 1) )
				mBillboardSet->setTextureStacksAndSlices(mStacks, mSlices);

			mBillboardSet->setCastShadows(false);

			mBillboardSet->setVisible(mVisible);

			parent->attachObject(mBillboardSet);

			for ( int i=0; i<mBillboardCount; ++i )
			{
				Ogre::Billboard *billboard = mBillboardSet->createBillboard(0, i*mBillboardInterval, 0, mBillboardColour * mAlphaValue);
				assert (billboard);
				billboard->setDimensions(mBillboardWidth, mBillboardHeight);
			}

			_resetBillboardStartTexIndex();
			_resetBillboardStartScaleTime();

			return true;
		}

		return false;
	}
	//---------------------------------------------------------------------
	void ImpactBillboardSetModule::_destroyBillboardSet(void)
	{		
		if (mBillboardSet)
		{
			Ogre::SceneNode* parent = mBillboardSet->getParentSceneNode();
			assert(parent);
			Ogre::SceneManager* creator = parent->getCreator();
			assert(creator);

			parent->detachObject(mBillboardSet->getName());

			creator->destroyBillboardSet(mBillboardSet);
		}
	}
	//---------------------------------------------------------------------
	void ImpactBillboardSetModule::_resetBillboardStartTexIndex(void)
	{
		assert (mBillboardSet);

		for ( int i=0; i<mBillboardCount; ++i )
		{
			uint16 texIndex = Ogre::Math::RangeRandom(0, mStacks * mSlices - 1);

			mBillboardSet->getBillboard(i)->setTexcoordIndex(texIndex);
		}
	}
	//---------------------------------------------------------------------
	void ImpactBillboardSetModule::updateRenderInstance( Real time, TransformInfo &info )
	{
		if (mBillboardSet)
		{
			bool updateTexIndex = false;

			if (mSlices > 1 || mStacks > 1)
			{
				mCurrentTexIntervalTime += time;

				if (mCurrentTexIntervalTime >= mTexIntervalTime)
				{
					updateTexIndex = true;
					mCurrentTexIntervalTime = 0.0f;
				}            
			}

			for ( int i = 0; i < mBillboardSet->getNumBillboards(); ++i )
			{
				Ogre::Billboard* billboard = mBillboardSet->getBillboard(i);

				if (updateTexIndex)
				{
					uint16 texIndex = billboard->getTexcoordIndex();
					++texIndex;

					if (texIndex == mStacks * mSlices)
						texIndex = 0;

					billboard->setTexcoordIndex(texIndex);
				}

				if (mColourChanged)
					billboard->setColour(mBillboardColour * mAlphaValue);

				if (mSizeChanged)
				{
					_CurrentScaleInfo& info = mCurrentScaleInfos[i];
					info.mCurrentScaleIntervalTime += time;

					float colourPersent = fmod( info.mCurrentScaleIntervalTime, mScaleIntervalTime );

					if (info.mCurrentScaleIntervalTime > mScaleIntervalTime)
					{
						info.mCurrentScaleIntervalTime  = colourPersent;

						++(info.mCurrentIndex);

						if (info.mCurrentIndex == MAX_STAGES)
							info.mCurrentIndex = 0;
					}

					Ogre::Vector3 resultColour;

					Real rate = colourPersent / mScaleIntervalTime;

					int incIndex = info.mCurrentIndex + 1;
					if (incIndex == MAX_STAGES)
						incIndex = 0;

					resultColour = mBillboardScale[info.mCurrentIndex] * (1-rate) + mBillboardScale[incIndex] * rate;

					billboard->setDimensions(mBillboardWidth * resultColour.x,
						mBillboardHeight * resultColour.y);
				}
			}

			if (mColourChanged)
				mColourChanged = false;
		}
	}
	//---------------------------------------------------------------------
	void ImpactBillboardSetModule::setBillboardColour(const Ogre::ColourValue &colour)
	{
		if (mBillboardColour != colour)
		{
			mBillboardColour = colour;
			mColourChanged = true;
		}
	}
	//---------------------------------------------------------------------
	void ImpactBillboardSetModule::setBillboardScale(size_t index, const ImpactBillboardSetModule::ScaleValue &scale)
	{
		if (mBillboardScale[index] != scale)
		{
			mBillboardScale[index] = scale;
			mSizeChanged = true;
		}		
	}
	//---------------------------------------------------------------------
	void ImpactBillboardSetModule::setBillboardCount(int count)
	{
		mBillboardCount = count;

		if (mBillboardSet)
		{
			mBillboardSet->clear();

			for ( int i=0; i<mBillboardCount; ++i )
			{
				Ogre::Billboard *billboard = mBillboardSet->createBillboard(0, i*mBillboardInterval, 0, mBillboardColour * mAlphaValue);
				assert (billboard);
				billboard->setDimensions(mBillboardWidth, mBillboardHeight);
			}

			_resetBillboardStartTexIndex();
			_resetBillboardStartScaleTime();
		}
	}
	//---------------------------------------------------------------------
	void ImpactBillboardSetModule::setBillboardMaterial(const String &material)
	{
		mBillboardMaterial = material;

		if (mBillboardSet)
		{
			mBillboardSet->setMaterialName(mBillboardMaterial, BLANKSTRING);
		}
	}
	//---------------------------------------------------------------------
	void ImpactBillboardSetModule::setBillboardInterval(Real interval)
	{
		mBillboardInterval = interval;

		if (mBillboardSet)
		{
			for ( int i = 0; i < mBillboardSet->getNumBillboards(); ++i )
			{
				mBillboardSet->getBillboard(i)->setPosition(0, i*mBillboardInterval, 0);
			}

			_resetBillboardStartScaleTime();
		}
	}
	//---------------------------------------------------------------------
	void ImpactBillboardSetModule::setBillboardWidth(Real width)
	{
		mBillboardWidth = width;

		if (mBillboardSet)
		{
			for ( int i = 0; i < mBillboardSet->getNumBillboards(); ++i )
			{
				mBillboardSet->getBillboard(i)->setDimensions(mBillboardWidth, mBillboardHeight);
			}
		}
	}
	//---------------------------------------------------------------------
	void ImpactBillboardSetModule::setBillboardHeight(Real height)
	{
		mBillboardHeight = height;

		if (mBillboardSet)
		{
			for ( int i = 0; i < mBillboardSet->getNumBillboards(); ++i )
			{
				mBillboardSet->getBillboard(i)->setDimensions(mBillboardWidth, mBillboardHeight);
			}
		}
	}
	//---------------------------------------------------------------------
	void ImpactBillboardSetModule::setStacks(ulong stacks)
	{
		if (stacks < 1)
			mStacks = 1;
		else
			mStacks = stacks;

		if (mBillboardSet)
		{
			mBillboardSet->setTextureStacksAndSlices((uchar)mStacks, (uchar)mSlices);
			_resetBillboardStartTexIndex();
		}
	}
	//-----------------------------------------------------------------------
	void ImpactBillboardSetModule::setSlices(ulong slices)
	{
		if (slices < 1)
			mSlices = 1;
		else
			mSlices = slices;

		if (mBillboardSet)
		{
			mBillboardSet->setTextureStacksAndSlices((uchar)mStacks, (uchar)mSlices);
			_resetBillboardStartTexIndex();
		}
	}
	//-----------------------------------------------------------------------
	void ImpactBillboardSetModule::_resetBillboardStartScaleTime(void)
	{
		mCurrentScaleInfos.resize(mBillboardCount);

		for (int i=0; i<mBillboardCount; ++i)
		{
			mCurrentScaleInfos[i].mCurrentScaleIntervalTime = Ogre::Math::RangeRandom(0.0f, mScaleIntervalTime);
			mCurrentScaleInfos[i].mCurrentIndex = (int)(Ogre::Math::RangeRandom(0,MAX_STAGES));
		}
	}
	//-----------------------------------------------------------------------
	void ImpactBillboardSetModule::setVisibleFlag(uint32 flags)
	{
		if (mBillboardSet)
			mBillboardSet->setVisibilityFlags(flags);
	}
	//////////////////////////////////////////////////////////////////////////
	String ImpactBillboardSetModule::CmdBillboardColour::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const ImpactBillboardSetModule *>(target)->getBillboardColour() );
	}
	void ImpactBillboardSetModule::CmdBillboardColour::doSet(void* target, const String& val)
	{
		static_cast<ImpactBillboardSetModule *>(target)->setBillboardColour(
			Ogre::StringConverter::parseColourValue(val) );
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void ImpactBillboardSetModule::CmdBillboardColour::doCopy(void* target, const void* source)
	{
		static_cast<ImpactBillboardSetModule *>(target)->setBillboardColour(
			static_cast<const ImpactBillboardSetModule *>(source)->getBillboardColour() );
	}
#endif
	//-----------------------------------------------------------------------
	String ImpactBillboardSetModule::CmdBillboardScale::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const ImpactBillboardSetModule *>(target)->getBillboardScale(mIndex) );
	}
	void ImpactBillboardSetModule::CmdBillboardScale::doSet(void* target, const String& val)
	{
		static_cast<ImpactBillboardSetModule *>(target)->setBillboardScale(mIndex,
			Ogre::StringConverter::parseVector3(val) );
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void ImpactBillboardSetModule::CmdBillboardScale::doCopy(void* target, const void* source)
	{
		static_cast<ImpactBillboardSetModule *>(target)->setBillboardScale(mIndex,
			static_cast<const ImpactBillboardSetModule *>(source)->getBillboardScale(mIndex) );
	}
#endif
	//-----------------------------------------------------------------------
	String ImpactBillboardSetModule::CmdScaleIntervalTime::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const ImpactBillboardSetModule *>(target)->getScaleIntervalTime() );
	}
	void ImpactBillboardSetModule::CmdScaleIntervalTime::doSet(void* target, const String& val)
	{
		static_cast<ImpactBillboardSetModule *>(target)->setScaleIntervalTime(
			Ogre::StringConverter::parseReal(val) );
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void ImpactBillboardSetModule::CmdScaleIntervalTime::doCopy(void* target, const void* source)
	{
		static_cast<ImpactBillboardSetModule *>(target)->setScaleIntervalTime(
			static_cast<const ImpactBillboardSetModule *>(source)->getScaleIntervalTime() );
	}
#endif
	//-----------------------------------------------------------------------
	String ImpactBillboardSetModule::CmdBillboardAlpha::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const ImpactBillboardSetModule *>(target)->getBillboardAlpha() );
	}
	void ImpactBillboardSetModule::CmdBillboardAlpha::doSet(void* target, const String& val)
	{
		static_cast<ImpactBillboardSetModule *>(target)->setBillboardAlpha(
			Ogre::StringConverter::parseReal(val) );
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void ImpactBillboardSetModule::CmdBillboardAlpha::doCopy(void* target, const void* source)
	{
		static_cast<ImpactBillboardSetModule *>(target)->setBillboardAlpha(
			static_cast<const ImpactBillboardSetModule *>(source)->getBillboardAlpha() );
	}
#endif
	//-----------------------------------------------------------------------
	String ImpactBillboardSetModule::CmdBillboardCount::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const ImpactBillboardSetModule *>(target)->getBillboardCount() );
	}
	void ImpactBillboardSetModule::CmdBillboardCount::doSet(void* target, const String& val)
	{
		static_cast<ImpactBillboardSetModule *>(target)->setBillboardCount( 
			Ogre::StringConverter::parseInt(val) );
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void ImpactBillboardSetModule::CmdBillboardCount::doCopy(void* target, const void* source)
	{
		static_cast<ImpactBillboardSetModule *>(target)->setBillboardCount(
			static_cast<const ImpactBillboardSetModule *>(source)->getBillboardCount() );
	}
#endif
	//-----------------------------------------------------------------------
	String ImpactBillboardSetModule::CmdBillboardMaterial::doGet(const void* target) const
	{
		return static_cast<const ImpactBillboardSetModule *>(target)->getBillboardMaterial();
	}
	void ImpactBillboardSetModule::CmdBillboardMaterial::doSet(void* target, const String& val)
	{
		static_cast<ImpactBillboardSetModule *>(target)->setBillboardMaterial(val);
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void ImpactBillboardSetModule::CmdBillboardMaterial::doCopy(void* target, const void* source)
	{
		static_cast<ImpactBillboardSetModule *>(target)->setBillboardMaterial(
			static_cast<const ImpactBillboardSetModule *>(source)->getBillboardMaterial() );
	}
#endif
	//-----------------------------------------------------------------------
	String ImpactBillboardSetModule::CmdBillboardInterval::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const ImpactBillboardSetModule *>(target)->getBillboardInterval() );
	}
	void ImpactBillboardSetModule::CmdBillboardInterval::doSet(void* target, const String& val)
	{
		static_cast<ImpactBillboardSetModule *>(target)->setBillboardInterval(
			Ogre::StringConverter::parseReal(val) );
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void ImpactBillboardSetModule::CmdBillboardInterval::doCopy(void* target, const void* source)
	{
		static_cast<ImpactBillboardSetModule *>(target)->setBillboardInterval(
			static_cast<const ImpactBillboardSetModule *>(source)->getBillboardInterval() );
	}
#endif
	//-----------------------------------------------------------------------
	String ImpactBillboardSetModule::CmdBillboardHeight::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const ImpactBillboardSetModule *>(target)->getBillboardHeight() );
	}
	void ImpactBillboardSetModule::CmdBillboardHeight::doSet(void* target, const String& val)
	{
		static_cast<ImpactBillboardSetModule *>(target)->setBillboardHeight(
			Ogre::StringConverter::parseReal(val) );
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void ImpactBillboardSetModule::CmdBillboardHeight::doCopy(void* target, const void* source)
	{
		static_cast<ImpactBillboardSetModule *>(target)->setBillboardHeight(
			static_cast<const ImpactBillboardSetModule *>(source)->getBillboardHeight() );
	}
#endif
	//-----------------------------------------------------------------------
	String ImpactBillboardSetModule::CmdBillboardWidth::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const ImpactBillboardSetModule *>(target)->getBillboardWidth() );
	}
	void ImpactBillboardSetModule::CmdBillboardWidth::doSet(void* target, const String& val)
	{
		static_cast<ImpactBillboardSetModule *>(target)->setBillboardWidth(
			Ogre::StringConverter::parseReal(val) );
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void ImpactBillboardSetModule::CmdBillboardWidth::doCopy(void* target, const void* source)
	{
		static_cast<ImpactBillboardSetModule *>(target)->setBillboardWidth(
			static_cast<const ImpactBillboardSetModule *>(source)->getBillboardWidth() );
	}
#endif
	//-----------------------------------------------------------------------
	String ImpactBillboardSetModule::CmdStacks::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const ImpactBillboardSetModule*>(target)->getStacks() );
	}
	void ImpactBillboardSetModule::CmdStacks::doSet(void* target, const String& val)
	{
		int64_t ret;
		ret = Ogre::StringConverter::parse(val, ret) ? ret : 0;
		static_cast<ImpactBillboardSetModule*>(target)->setStacks(ret);
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void ImpactBillboardSetModule::CmdStacks::doCopy(void* target, const void* source)
	{
		static_cast<ImpactBillboardSetModule *>(target)->setStacks(
			static_cast<const ImpactBillboardSetModule *>(source)->getStacks() );
	}
#endif
	//-----------------------------------------------------------------------
	String ImpactBillboardSetModule::CmdSlices::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const ImpactBillboardSetModule*>(target)->getSlices() );
	}
	void ImpactBillboardSetModule::CmdSlices::doSet(void* target, const String& val)
	{
		int64_t ret;
		ret = Ogre::StringConverter::parse(val, ret) ? ret : 0;
		static_cast<ImpactBillboardSetModule*>(target)->setSlices(ret);
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void ImpactBillboardSetModule::CmdSlices::doCopy(void* target, const void* source)
	{
		static_cast<ImpactBillboardSetModule *>(target)->setSlices(
			static_cast<const ImpactBillboardSetModule *>(source)->getSlices() );
	}
#endif
	//-----------------------------------------------------------------------
	String ImpactBillboardSetModule::CmdTexIntervalTime::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const ImpactBillboardSetModule *>(target)->getTexIntervalTime() );
	}
	void ImpactBillboardSetModule::CmdTexIntervalTime::doSet(void* target, const String& val)
	{
		static_cast<ImpactBillboardSetModule *>(target)->setTexIntervalTime(
			Ogre::StringConverter::parseReal(val) );
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void ImpactBillboardSetModule::CmdTexIntervalTime::doCopy(void* target, const void* source)
	{
		static_cast<ImpactBillboardSetModule *>(target)->setTexIntervalTime(
			static_cast<const ImpactBillboardSetModule *>(source)->getTexIntervalTime() );
	}
#endif
}