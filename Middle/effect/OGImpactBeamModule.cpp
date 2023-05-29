#include "OgreHeader.h"
#include "OGImpactBeamModule.h"
#include "OgreEffectBillboardChain.h"
#include "OgreSceneNode.h"
// ogre header
#include <OgreSceneManager.h>
#include <OgreStringConverter.h>
#include <OgreParticleAffector.h>
#include <platform_log.h>
#include "OGImpactSerializer.h"
#include "OgreString.h"

namespace Orphigine	{

	ImpactBeamModule::CmdNoiseXMin ImpactBeamModule::msNoiseXMinCmd;
	ImpactBeamModule::CmdNoiseXMax ImpactBeamModule::msNoiseXMaxCmd;
	ImpactBeamModule::CmdNoiseYMin ImpactBeamModule::msNoiseYMinCmd;
	ImpactBeamModule::CmdNoiseYMax ImpactBeamModule::msNoiseYMaxCmd;
	ImpactBeamModule::CmdNoiseZMin ImpactBeamModule::msNoiseZMinCmd;
	ImpactBeamModule::CmdNoiseZMax ImpactBeamModule::msNoiseZMaxCmd;
	ImpactBeamModule::CmdNumElements ImpactBeamModule::msNumElementsCmd;
	ImpactBeamModule::CmdWidthStart ImpactBeamModule::msWidthStartCmd;
	ImpactBeamModule::CmdWidthEnd ImpactBeamModule::msWidthEndCmd;
	ImpactBeamModule::CmdColour ImpactBeamModule::msColourCmd;
	ImpactBeamModule::CmdColourRangeStart ImpactBeamModule::msColourRangeStartCmd;
	ImpactBeamModule::CmdColourRangeEnd ImpactBeamModule::msColourRangeEndCmd;
	ImpactBeamModule::CmdMaterial ImpactBeamModule::msMaterialCmd;
	ImpactBeamModule::CmdFrequency ImpactBeamModule::msFrequencyCmd;
	ImpactBeamModule::CmdDestPos ImpactBeamModule::msDestPosCmd;

	//////////////////////////////////////////////////////////////////////////
	ImpactBeamModule::ImpactBeamModule(const String &type) :
	ImpactModule(type),
		mNumBillboardElements(10),
		mNoiseXMin(0.0f),
		mNoiseXMax(0.0f),
		mNoiseYMin(0.0f),
		mNoiseYMax(0.0f),
		mNoiseZMin(0.0f),
		mNoiseZMax(0.0f),
		mDestPos(Ogre::Vector3::UNIT_Y), // 初始位置
		mWidthStart(10.0f),
		mWidthEnd(10.0f),
		mBillboardChain(NULL),
		mMaterialName("BaseWhiteNoLighting"),
		mFrequency(20.0f),
		mFrequencyTime(0.0f),
		mCurrentFrequencyTime(0.0f)
	{
		if ( initDefaults(mElementType) )
		{
			Ogre::ParamDictionary* dict = getParamDictionary();

			// Custom params      
			dict->addParameter(Ogre::ParameterDef("NoiseXMin", 
				"min noise of x axis.",
				Ogre::PT_REAL),&msNoiseXMinCmd);

			dict->addParameter(Ogre::ParameterDef("NoiseXMax", 
				"max noise of x axis.",
				Ogre::PT_REAL),&msNoiseXMaxCmd);

			dict->addParameter(Ogre::ParameterDef("NoiseYMin", 
				"min noise of y axis.",
				Ogre::PT_REAL),&msNoiseYMinCmd);

			dict->addParameter(Ogre::ParameterDef("NoiseYMax", 
				"max noise of y axis.",
				Ogre::PT_REAL),&msNoiseYMaxCmd);

			dict->addParameter(Ogre::ParameterDef("NoiseZMin", 
				"min noise of z axis.",
				Ogre::PT_REAL),&msNoiseZMinCmd);

			dict->addParameter(Ogre::ParameterDef("NoiseZMax", 
				"max noise of z axis.",
				Ogre::PT_REAL),&msNoiseZMaxCmd);

			dict->addParameter(Ogre::ParameterDef("NumElements", 
				"the num of billboard chain elements.",
				Ogre::PT_INT),&msNumElementsCmd);

			dict->addParameter(Ogre::ParameterDef("StartWidth", 
				"start width of billboard.",
				Ogre::PT_REAL),&msWidthStartCmd);

			dict->addParameter(Ogre::ParameterDef("StartWidth", 
				"end width of billboard.",
				Ogre::PT_REAL),&msWidthEndCmd);

			dict->addParameter(Ogre::ParameterDef("Colour", 
				"The colour of emitted particles.", Ogre::PT_COLOURVALUE),
				&msColourCmd);

			dict->addParameter(Ogre::ParameterDef("ColourRangeStart", 
				"The start of a range of colours to be assigned to emitted particles.", Ogre::PT_COLOURVALUE),
				&msColourRangeStartCmd);

			dict->addParameter(Ogre::ParameterDef("ColourRangeEnd", 
				"The end of a range of colours to be assigned to emitted particles.", Ogre::PT_COLOURVALUE),
				&msColourRangeEndCmd);

			dict->addParameter(Ogre::ParameterDef("Material", 
				"name of beam material.",
				Ogre::PT_STRING),&msMaterialCmd);

			dict->addParameter(Ogre::ParameterDef("Frequency", 
				"frequency of billboard.",
				Ogre::PT_REAL),&msFrequencyCmd);

			dict->addParameter( Ogre::ParameterDef("DestPos",
				"dest pos of billboard",
				Ogre::PT_REAL), &msDestPosCmd );
		}

		mColourRangeStart = mColourRangeEnd = Ogre::ColourValue::White;
	}
	//---------------------------------------------------------------------
	ImpactBeamModule::~ImpactBeamModule()
	{
		destroyRenderInstance();
	}	
	//---------------------------------------------------------------------
	bool ImpactBeamModule::createRenderInstance(void)
	{
		return _createBillboardChains();
	}
	//---------------------------------------------------------------------
	void ImpactBeamModule::destroyRenderInstance(void)
	{
		_destroyBillboardChains();

		ImpactModule::destroyRenderInstance();
	}
	//---------------------------------------------------------------------
	void ImpactBeamModule::updateRenderInstance( Real time, TransformInfo &info )
	{
		if ( mBasicNode )
		{
			_updateBillboardChains(time);
		}
	}
	//---------------------------------------------------------------------
	bool ImpactBeamModule::_createBillboardChains(void)
	{
		Ogre::SceneNode* parent = mBasicNode;

		if (parent)
		{			
			mBillboardChain = new Ogre::EffectBillboardChain(mNumBillboardElements);
			mBillboardChain->setNbChainElements(mNumBillboardElements);
			mBillboardChain->setMaterial(mMaterialName);

			mBillboardChain->updateBoundingBox();

			mBillboardChain->setCastShadows(false);

			// Add it to the scene
			parent->attachObject(mBillboardChain);

			return true;
		}

		return false;
	}
	//---------------------------------------------------------------------
	void ImpactBeamModule::_destroyBillboardChains(void)
	{		
		if (mBillboardChain)
		{
			mBasicNode->detachObject(mBillboardChain);

			delete mBillboardChain;
			mBillboardChain = NULL;
		}		
	}
	//---------------------------------------------------------------------
	void ImpactBeamModule::_updateBillboardChains( Real time )
	{
		mCurrentFrequencyTime += time;

		if (mCurrentFrequencyTime > mFrequencyTime || mFrequency == 0.0f)
		{
			// 如果目标位置为初始位置，就不进行更新，防止第一帧出现的位置不正确
			if (mDestPos == Ogre::Vector3::UNIT_Y)
			{
				return;
			}

			Ogre::Vector3 originPos = mBasicNode->_getDerivedPosition();

			// 如果初始点还没初始化（在LogicModel::addEffect中会把这个特效的位置设成一个很低的地方），也return
			if ( originPos.y < -9000 )
			{
				return;
			}

			if (mBillboardChain)
			{
				Ogre::ColourValue colour;
				genColour(colour);

				for (int j = 0; j < mNumBillboardElements; ++j)
				{
					if (j == 0)
					{
						mBillboardChain->setChainElement(j, 
							Ogre::EffectBillboardChainElement(
							Ogre::Vector3::ZERO,
							mWidthStart,
							0.0f,
							colour)
							);
					}
					else if ( j == (mNumBillboardElements-1) )
					{
						mBillboardChain->setChainElement(j, 
							Ogre::EffectBillboardChainElement(
							mDestPos - originPos,
							mWidthEnd,
							1.0f,
							colour)
							);
					}
					else
					{
						float interpolateValue = (float)j / (float)mNumBillboardElements;
						Ogre::Vector3 pos = (mDestPos - originPos) * interpolateValue;
						pos.x += Ogre::Math::RangeRandom(mNoiseXMin, mNoiseXMax);
						pos.y += Ogre::Math::RangeRandom(mNoiseYMin, mNoiseYMax);
						pos.z += Ogre::Math::RangeRandom(mNoiseZMin, mNoiseZMax);

						float width = (mWidthEnd - mWidthStart) * interpolateValue + mWidthStart;

						mBillboardChain->setChainElement(j, 
							Ogre::EffectBillboardChainElement(
							pos,
							width,
							interpolateValue,
							colour)
							);
					}					
				}

				mBillboardChain->updateBoundingBox();

				// 数据已准备好，可以进行渲染了
				mBillboardChain->isInitData(true);
			}

			mCurrentFrequencyTime = 0.0f;
		}		
	}
	//---------------------------------------------------------------------
	void ImpactBeamModule::updateExtraTransformInfos( const TransformInfos &infos )
	{
		mDestPos = infos[0].mPosition;	

		//	_updateBillboardChains();
	}
	//---------------------------------------------------------------------
	void ImpactBeamModule::setNumBillboardElements( int num )
	{
		mNumBillboardElements = num;

		if (mBillboardChain)
		{
			mBillboardChain->setNbChainElements(mNumBillboardElements);
		}
	}
	//-----------------------------------------------------------------------
	void ImpactBeamModule::setColour(const Ogre::ColourValue& colour)
	{
		mColourRangeStart = mColourRangeEnd = colour;
	}
	//-----------------------------------------------------------------------
	void ImpactBeamModule::setColour(const Ogre::ColourValue& colourStart, const Ogre::ColourValue& colourEnd)
	{
		mColourRangeStart = colourStart;
		mColourRangeEnd = colourEnd;
	}
	//-----------------------------------------------------------------------
	const Ogre::ColourValue& ImpactBeamModule::getColour(void) const
	{
		return mColourRangeStart;
	}
	//-----------------------------------------------------------------------
	const Ogre::ColourValue& ImpactBeamModule::getColourRangeStart(void) const
	{
		return mColourRangeStart;
	}
	//-----------------------------------------------------------------------
	const Ogre::ColourValue& ImpactBeamModule::getColourRangeEnd(void) const
	{
		return mColourRangeEnd;
	}
	//-----------------------------------------------------------------------
	void ImpactBeamModule::setColourRangeStart(const Ogre::ColourValue& val)
	{
		mColourRangeStart = val;
	}
	//-----------------------------------------------------------------------
	void ImpactBeamModule::setColourRangeEnd(const Ogre::ColourValue& val )
	{
		mColourRangeEnd = val;
	}
	//-----------------------------------------------------------------------
	void ImpactBeamModule::genColour(Ogre::ColourValue& destColour)
	{
		if (mColourRangeStart != mColourRangeEnd)
		{
			// Randomise
			//Real t = Math::UnitRandom();
			destColour.r = mColourRangeStart.r + (Ogre::Math::UnitRandom() * (mColourRangeEnd.r - mColourRangeStart.r));
			destColour.g = mColourRangeStart.g + (Ogre::Math::UnitRandom() * (mColourRangeEnd.g - mColourRangeStart.g));
			destColour.b = mColourRangeStart.b + (Ogre::Math::UnitRandom() * (mColourRangeEnd.b - mColourRangeStart.b));
			destColour.a = mColourRangeStart.a + (Ogre::Math::UnitRandom() * (mColourRangeEnd.a - mColourRangeStart.a));
		}
		else
		{
			destColour = mColourRangeStart;
		}
	}
	//-----------------------------------------------------------------------
	void ImpactBeamModule::setMaterialName(const String &matName)
	{
		mMaterialName = matName;

		if (mBillboardChain)
			mBillboardChain->setMaterial(mMaterialName);
	}
	//-----------------------------------------------------------------------
	void ImpactBeamModule::setFrequency(float frequency)
	{
		mFrequency = frequency;

		if (mFrequency > 0.0f)
		{
			mFrequencyTime = 1.0 / mFrequency;
		}
		else
		{
			mFrequencyTime = 0.0f;
			mCurrentFrequencyTime = 0.0f;
		}
	}
	//-----------------------------------------------------------------------
	void ImpactBeamModule::sleep(void)
	{
		if (mBillboardChain)
		{
			mBillboardChain->isInitData(false);
		}

		ImpactModule::sleep();		
	}
	//-----------------------------------------------------------------------
	void ImpactBeamModule::setVisibleFlag(uint32 flags)
	{
		if (mBillboardChain)
			mBillboardChain->setVisibilityFlags(flags);
	}
	//-----------------------------------------------------------------------	
	///*
	char * ImpactBeamModule::readFromBuffer(char * pCurrent)
	{
		pCurrent = ImpactModule::readFromBuffer(pCurrent);

		int length = sizeof(float) * 9 + sizeof(int) + sizeof(Ogre::ColourValue) * 2 + sizeof(Ogre::Vector3);
		memcpy(&mNoiseXMin,pCurrent,length);
		pCurrent += length;


		String strMaterialName;
		Ogre::StringUtil::loadStringFromMemory(strMaterialName,pCurrent);

		setFrequency(mFrequency);
		setMaterialName(strMaterialName);

		return pCurrent;
	}
	//-----------------------------------------------------------------------
	void ImpactBeamModule::saveToFile(std::ofstream & of)
	{
		ImpactModule::saveToFile(of);
		of.write((const char *)(&mNoiseXMin),sizeof(float) * 9 + sizeof(int) + sizeof(Ogre::ColourValue) * 2 + sizeof(Ogre::Vector3));
		Ogre::StringUtil::saveStringToStream(mMaterialName,of);
	}
	//*/
	bool ImpactBeamModule::loadFromStream(Ogre::Serializer* pSerializer,Ogre::DataStreamPtr& stream)
	{
		if(pSerializer && stream->eof() == false)
		{
			unsigned short id = pSerializer->readChunk(stream);
			if(id != ImpactSerializer::EFF_BEAM_ELEMENT)
			{
				WARNING_LOG("Load BeamElement From Stream Failed. ChunkId Error");
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
			pSerializer->readData(stream,&mNoiseXMin,1,sizeof(float));
			pSerializer->readData(stream,&mNoiseXMax,1,sizeof(float));
			pSerializer->readData(stream,&mNoiseYMin,1,sizeof(float));
			pSerializer->readData(stream,&mNoiseYMax,1,sizeof(float));
			pSerializer->readData(stream,&mNoiseZMin,1,sizeof(float));
			pSerializer->readData(stream,&mNoiseZMax,1,sizeof(float));
			pSerializer->readData(stream,&mNumBillboardElements,1,sizeof(int));	

			pSerializer->readData(stream,&mWidthStart,1,sizeof(float));
			pSerializer->readData(stream,&mWidthEnd,1,sizeof(float));
			pSerializer->readData(stream,&mColourRangeStart,1,sizeof(Ogre::ColourValue));
			pSerializer->readData(stream,&mColourRangeEnd,1,sizeof(Ogre::ColourValue));
			float frequency = 0.0f;
			pSerializer->readData(stream,&frequency,1,sizeof(float));
			setFrequency(frequency);
			pSerializer->readData(stream,&mDestPos,1,sizeof(Ogre::Vector3));
			String materialName = pSerializer->readStringBin(stream);
			setMaterialName(materialName);
			return true;	
		}
		return false;
	}
	bool ImpactBeamModule::saveToBinaryFile(Ogre::Serializer* pSerializer)
	{
		
		return false;
	}
	std::size_t	ImpactBeamModule::calcSerializedSize()
	{
		size_t tmpSize = Ogre::Serializer::STREAM_OVERHEAD_SIZE;
		//基类成员
		tmpSize += sizeof(mStartTime);
		tmpSize += sizeof(mLifeTime);
		tmpSize += sizeof(mRelPos);
		tmpSize += sizeof(mRelOrientation);
		//自身成员
		tmpSize += sizeof(mNoiseXMin);
		tmpSize += sizeof(mNoiseXMax);
		tmpSize += sizeof(mNoiseYMin);
		tmpSize += sizeof(mNoiseYMax);
		tmpSize += sizeof(mNoiseZMin);
		tmpSize += sizeof(mNoiseZMax);
		tmpSize += sizeof(mNumBillboardElements);

		tmpSize += sizeof(mWidthStart);
		tmpSize += sizeof(mWidthEnd);
		tmpSize += sizeof(mColourRangeStart);
		tmpSize += sizeof(mColourRangeEnd);
		tmpSize += sizeof(mFrequency);
		tmpSize += sizeof(mDestPos);
		tmpSize += mMaterialName.length() + 1;			
		return tmpSize;
	}

	//////////////////////////////////////////////////////////////////////////
	String ImpactBeamModule::CmdNoiseXMin::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const ImpactBeamModule *>(target)->mNoiseXMin );
	}
	void ImpactBeamModule::CmdNoiseXMin::doSet(void* target, const String& val)
	{
		static_cast<ImpactBeamModule *>(target)->mNoiseXMin = 
			Ogre::StringConverter::parseReal(val);
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void ImpactBeamModule::CmdNoiseXMin::doCopy(void* target, const void* source)
	{
		static_cast<ImpactBeamModule *>(target)->mNoiseXMin = 
			static_cast<const ImpactBeamModule *>(source)->mNoiseXMin;
	}
#endif
	//-----------------------------------------------------------------------
	String ImpactBeamModule::CmdNoiseXMax::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const ImpactBeamModule *>(target)->mNoiseXMax );
	}
	void ImpactBeamModule::CmdNoiseXMax::doSet(void* target, const String& val)
	{
		static_cast<ImpactBeamModule *>(target)->mNoiseXMax = 
			Ogre::StringConverter::parseReal(val);
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void ImpactBeamModule::CmdNoiseXMax::doCopy(void* target, const void* source)
	{
		static_cast<ImpactBeamModule *>(target)->mNoiseXMax = 
			static_cast<const ImpactBeamModule *>(source)->mNoiseXMax;
	}
#endif
	//-----------------------------------------------------------------------
	String ImpactBeamModule::CmdNoiseYMin::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const ImpactBeamModule *>(target)->mNoiseYMin );
	}
	void ImpactBeamModule::CmdNoiseYMin::doSet(void* target, const String& val)
	{
		static_cast<ImpactBeamModule *>(target)->mNoiseYMin = 
			Ogre::StringConverter::parseReal(val);
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void ImpactBeamModule::CmdNoiseYMin::doCopy(void* target, const void* source)
	{
		static_cast<ImpactBeamModule *>(target)->mNoiseYMin = 
			static_cast<const ImpactBeamModule *>(source)->mNoiseYMin;
	}
#endif
	//-----------------------------------------------------------------------
	String ImpactBeamModule::CmdNoiseYMax::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const ImpactBeamModule *>(target)->mNoiseYMax );
	}
	void ImpactBeamModule::CmdNoiseYMax::doSet(void* target, const String& val)
	{
		static_cast<ImpactBeamModule *>(target)->mNoiseYMax = 
			Ogre::StringConverter::parseReal(val);
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void ImpactBeamModule::CmdNoiseYMax::doCopy(void* target, const void* source)
	{
		static_cast<ImpactBeamModule *>(target)->mNoiseYMax = 
			static_cast<const ImpactBeamModule *>(source)->mNoiseYMax;
	}
#endif
	//-----------------------------------------------------------------------
	String ImpactBeamModule::CmdNoiseZMin::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const ImpactBeamModule *>(target)->mNoiseZMin );
	}
	void ImpactBeamModule::CmdNoiseZMin::doSet(void* target, const String& val)
	{
		static_cast<ImpactBeamModule *>(target)->mNoiseZMin = 
			Ogre::StringConverter::parseReal(val);
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void ImpactBeamModule::CmdNoiseZMin::doCopy(void* target, const void* source)
	{
		static_cast<ImpactBeamModule *>(target)->mNoiseZMin = 
			static_cast<const ImpactBeamModule *>(source)->mNoiseZMin;
	}
#endif
	//-----------------------------------------------------------------------
	String ImpactBeamModule::CmdNoiseZMax::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const ImpactBeamModule *>(target)->mNoiseZMax );
	}
	void ImpactBeamModule::CmdNoiseZMax::doSet(void* target, const String& val)
	{
		static_cast<ImpactBeamModule *>(target)->mNoiseZMax = 
			Ogre::StringConverter::parseReal(val);
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void ImpactBeamModule::CmdNoiseZMax::doCopy(void* target, const void* source)
	{
		static_cast<ImpactBeamModule *>(target)->mNoiseZMax = 
			static_cast<const ImpactBeamModule *>(source)->mNoiseZMax;
	}
#endif
	//-----------------------------------------------------------------------
	String ImpactBeamModule::CmdNumElements::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const ImpactBeamModule *>(target)->getNumBillboardElements() );
	}
	void ImpactBeamModule::CmdNumElements::doSet(void* target, const String& val)
	{
		static_cast<ImpactBeamModule *>(target)->setNumBillboardElements( Ogre::StringConverter::parseInt(val) );
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void ImpactBeamModule::CmdNumElements::doCopy(void* target, const void* source)
	{
		static_cast<ImpactBeamModule *>(target)->setNumBillboardElements(
			static_cast<const ImpactBeamModule *>(source)->getNumBillboardElements() );
	}
#endif
	//-----------------------------------------------------------------------
	String ImpactBeamModule::CmdWidthStart::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const ImpactBeamModule *>(target)->mWidthStart );
	}
	void ImpactBeamModule::CmdWidthStart::doSet(void* target, const String& val)
	{
		static_cast<ImpactBeamModule *>(target)->mWidthStart = Ogre::StringConverter::parseReal(val);
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void ImpactBeamModule::CmdWidthStart::doCopy(void* target, const void* source)
	{
		static_cast<ImpactBeamModule *>(target)->mWidthStart = 
			static_cast<const ImpactBeamModule *>(source)->mWidthStart;
	}
#endif

	String ImpactBeamModule::CmdWidthEnd::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const ImpactBeamModule *>(target)->mWidthEnd );
	}
	void ImpactBeamModule::CmdWidthEnd::doSet(void* target, const String& val)
	{
		static_cast<ImpactBeamModule *>(target)->mWidthEnd = Ogre::StringConverter::parseReal(val);
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void ImpactBeamModule::CmdWidthEnd::doCopy(void* target, const void* source)
	{
		static_cast<ImpactBeamModule *>(target)->mWidthEnd = 
			static_cast<const ImpactBeamModule *>(source)->mWidthEnd;
	}
#endif

	//-----------------------------------------------------------------------
	String ImpactBeamModule::CmdColour::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const ImpactBeamModule*>(target)->getColour() );
	}
	void ImpactBeamModule::CmdColour::doSet(void* target, const String& val)
	{
		static_cast<ImpactBeamModule*>(target)->setColour(Ogre::StringConverter::parseColourValue(val));
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void ImpactBeamModule::CmdColour::doCopy(void* target, const void* source)
	{
		static_cast<ImpactBeamModule *>(target)->setColour(
			static_cast<const ImpactBeamModule *>(source)->getColour() );
	}
#endif
	//-----------------------------------------------------------------------
	String ImpactBeamModule::CmdColourRangeStart::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const ImpactBeamModule*>(target)->getColourRangeStart() );
	}
	void ImpactBeamModule::CmdColourRangeStart::doSet(void* target, const String& val)
	{
		static_cast<ImpactBeamModule*>(target)->setColourRangeStart(Ogre::StringConverter::parseColourValue(val));
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void ImpactBeamModule::CmdColourRangeStart::doCopy(void* target, const void* source)
	{
		static_cast<ImpactBeamModule *>(target)->setColourRangeStart(
			static_cast<const ImpactBeamModule *>(source)->getColourRangeStart() );
	}
#endif
	//-----------------------------------------------------------------------
	String ImpactBeamModule::CmdColourRangeEnd::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const ImpactBeamModule*>(target)->getColourRangeEnd() );
	}
	void ImpactBeamModule::CmdColourRangeEnd::doSet(void* target, const String& val)
	{
		static_cast<ImpactBeamModule*>(target)->setColourRangeEnd(Ogre::StringConverter::parseColourValue(val));
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void ImpactBeamModule::CmdColourRangeEnd::doCopy(void* target, const void* source)
	{
		static_cast<ImpactBeamModule *>(target)->setColourRangeEnd( 
			static_cast<const ImpactBeamModule *>(source)->getColourRangeEnd() );
	}
#endif
	//-----------------------------------------------------------------------
	String ImpactBeamModule::CmdMaterial::doGet(const void* target) const
	{
		return static_cast<const ImpactBeamModule *>(target)->getMaterialName();
	}
	void ImpactBeamModule::CmdMaterial::doSet(void* target, const String& val)
	{
		static_cast<ImpactBeamModule *>(target)->setMaterialName(val);
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void ImpactBeamModule::CmdMaterial::doCopy(void* target, const void* source)
	{
		static_cast<ImpactBeamModule *>(target)->setMaterialName( 
			static_cast<const ImpactBeamModule *>(source)->getMaterialName() );
	}
#endif
	//-----------------------------------------------------------------------
	String ImpactBeamModule::CmdFrequency::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const ImpactBeamModule *>(target)->getFrequency() );
	}
	void ImpactBeamModule::CmdFrequency::doSet(void* target, const String& val)
	{
		static_cast<ImpactBeamModule *>(target)->setFrequency( Ogre::StringConverter::parseReal(val) );
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void ImpactBeamModule::CmdFrequency::doCopy(void* target, const void* source)
	{
		static_cast<ImpactBeamModule *>(target)->setFrequency( 
			static_cast<const ImpactBeamModule *>(source)->getFrequency() );
	}
#endif

	String ImpactBeamModule::CmdDestPos::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const ImpactBeamModule *>(target)->mDestPos );
	}
	void ImpactBeamModule::CmdDestPos::doSet(void* target, const String& val)
	{
		static_cast<ImpactBeamModule *>(target)->mDestPos = ( Ogre::StringConverter::parseVector3(val) );
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void ImpactBeamModule::CmdDestPos::doCopy(void* target, const void* source)
	{
		static_cast<ImpactBeamModule *>(target)->mDestPos =
			static_cast<const ImpactBeamModule *>(source)->mDestPos ;
	}
#endif
}