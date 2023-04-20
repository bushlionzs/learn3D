#include "OgreHeader.h"
#include "OGBulletSystemBeamElement.h"
#include "OgreEffectBillboardChain.h"
// ogre header
#include <OgreSceneManager.h>
#include <OgreStringConverter.h>
#include "OgreSceneNode.h"
#include "engine_manager.h"

namespace Orphigine	{

	BulletSystemBeamElement::CmdNoiseXMin BulletSystemBeamElement::msNoiseXMinCmd;
	BulletSystemBeamElement::CmdNoiseXMax BulletSystemBeamElement::msNoiseXMaxCmd;
	BulletSystemBeamElement::CmdNoiseYMin BulletSystemBeamElement::msNoiseYMinCmd;
	BulletSystemBeamElement::CmdNoiseYMax BulletSystemBeamElement::msNoiseYMaxCmd;
	BulletSystemBeamElement::CmdNoiseZMin BulletSystemBeamElement::msNoiseZMinCmd;
	BulletSystemBeamElement::CmdNoiseZMax BulletSystemBeamElement::msNoiseZMaxCmd;
	BulletSystemBeamElement::CmdNumElements BulletSystemBeamElement::msNumElementsCmd;
	BulletSystemBeamElement::CmdWidthStart BulletSystemBeamElement::msWidthStartCmd;
	BulletSystemBeamElement::CmdWidthEnd BulletSystemBeamElement::msWidthEndCmd;
	BulletSystemBeamElement::CmdColour BulletSystemBeamElement::msColourCmd;
	BulletSystemBeamElement::CmdColourRangeStart BulletSystemBeamElement::msColourRangeStartCmd;
	BulletSystemBeamElement::CmdColourRangeEnd BulletSystemBeamElement::msColourRangeEndCmd;
	BulletSystemBeamElement::CmdMaterial BulletSystemBeamElement::msMaterialCmd;
	BulletSystemBeamElement::CmdFrequency BulletSystemBeamElement::msFrequencyCmd;

	//////////////////////////////////////////////////////////////////////////
	BulletSystemBeamElement::BulletSystemBeamElement() 
		:	
		BulletSystemElement("BulletSystemBeamElement"),
		mNumBillboardElements(10),
		mNoiseXMin(0.0f),
		mNoiseXMax(0.0f),
		mNoiseYMin(0.0f),
		mNoiseYMax(0.0f),
		mNoiseZMin(0.0f), 
		mNoiseZMax(0.0f),
		mWidthStart(10.0f),
		mWidthEnd(10.0f),
		mBillboardChain(NULL),
		mMaterialName("BaseWhiteNoLighting"),
		mFrequency(20.0f),
		m_sourcePosition(Ogre::Vector3::ZERO),
		m_destPosition(Ogre::Vector3::ZERO), // 初始位置
		mFrequencyTime(0.0f),
		mCurrentFrequencyTime(0.0f)
	{
		if ( _initParameters(m_typeName) )
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

			dict->addParameter(Ogre::ParameterDef("EndWidth", 
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
		}

		mColourRangeStart = mColourRangeEnd = Ogre::ColourValue::White;
	}
	//---------------------------------------------------------------------
	BulletSystemBeamElement::~BulletSystemBeamElement()
	{
		destroyRenderInstance();
	}	
	//---------------------------------------------------------------------
	bool BulletSystemBeamElement::createRenderInstance(void)
	{
		return _createBillboardChains();
	}
	//---------------------------------------------------------------------
	void BulletSystemBeamElement::destroyRenderInstance(void)
	{
		_destroyBillboardChains();

		//EffectElement::destroyRenderInstance();
	}
	//---------------------------------------------------------------------
	void BulletSystemBeamElement::updateRenderInstance( Real time, const Ogre::Vector3& sourcePosition,
		const Ogre::Vector3& destPosition)
	{
		//m_sourcePosition = sourcePosition;
		m_sceneNode->setPosition(sourcePosition);
		m_destPosition = destPosition;

		if ( m_sceneNode )
		{
			_updateBillboardChains(time);
		}
	}
	//---------------------------------------------------------------------
	bool BulletSystemBeamElement::_createBillboardChains(void)
	{
		Ogre::SceneNode* parent = m_sceneNode;

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
	void BulletSystemBeamElement::_destroyBillboardChains(void)
	{		
		if (mBillboardChain)
		{
			m_sceneNode->detachObject(mBillboardChain);

			delete mBillboardChain;
			mBillboardChain = NULL;
		}		
	}
	//---------------------------------------------------------------------
	void BulletSystemBeamElement::_updateBillboardChains( Real time )
	{
		mCurrentFrequencyTime += time;

		if (mCurrentFrequencyTime > mFrequencyTime || mFrequency == 0.0f)
		{
			// 如果目标位置为初始位置，就不进行更新，防止第一帧出现的位置不正确
			if (m_destPosition == Ogre::Vector3::ZERO)
			{
				return;
			}

			Ogre::Vector3 originPos = m_sceneNode->_getDerivedPosition()/* + m_sourcePosition*/;

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
							m_destPosition - originPos,
							mWidthEnd,
							1.0f,
							colour)
							);
					}
					else
					{
						float interpolateValue = (float)j / (float)mNumBillboardElements;
						Ogre::Vector3 pos = (m_destPosition - originPos) * interpolateValue;
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

	int BulletSystemBeamElement::getNumBillboardElements( void ) const
	{
		return mNumBillboardElements;
	}

	void BulletSystemBeamElement::setNumBillboardElements( int num )
	{
		mNumBillboardElements = num;

		if (mBillboardChain)
		{
			mBillboardChain->setNbChainElements(mNumBillboardElements);
		}
	}
	//-----------------------------------------------------------------------
	void BulletSystemBeamElement::setColour(const Ogre::ColourValue& colour)
	{
		mColourRangeStart = mColourRangeEnd = colour;
	}
	//-----------------------------------------------------------------------
	void BulletSystemBeamElement::setColour(const Ogre::ColourValue& colourStart, const Ogre::ColourValue& colourEnd)
	{
		mColourRangeStart = colourStart;
		mColourRangeEnd = colourEnd;
	}
	//-----------------------------------------------------------------------
	const Ogre::ColourValue& BulletSystemBeamElement::getColour(void) const
	{
		return mColourRangeStart;
	}
	//-----------------------------------------------------------------------
	const Ogre::ColourValue& BulletSystemBeamElement::getColourRangeStart(void) const
	{
		return mColourRangeStart;
	}
	//-----------------------------------------------------------------------
	const Ogre::ColourValue& BulletSystemBeamElement::getColourRangeEnd(void) const
	{
		return mColourRangeEnd;
	}
	//-----------------------------------------------------------------------
	void BulletSystemBeamElement::setColourRangeStart(const Ogre::ColourValue& val)
	{
		mColourRangeStart = val;
	}
	//-----------------------------------------------------------------------
	void BulletSystemBeamElement::setColourRangeEnd(const Ogre::ColourValue& val )
	{
		mColourRangeEnd = val;
	}
	//-----------------------------------------------------------------------
	void BulletSystemBeamElement::genColour(Ogre::ColourValue& destColour)
	{
		if (mColourRangeStart != mColourRangeEnd)
		{
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
	const String& BulletSystemBeamElement::getMaterialName( void ) const
	{
		return mMaterialName;
	}

	void BulletSystemBeamElement::setMaterialName(const String &matName)
	{
		mMaterialName = matName;

		if (mBillboardChain)
			mBillboardChain->setMaterial(mMaterialName);
	}
	//-----------------------------------------------------------------------
	float BulletSystemBeamElement::getFrequency( void ) const
	{
		return mFrequency;
	}

	void BulletSystemBeamElement::setFrequency(float frequency)
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
	void BulletSystemBeamElement::sleep(void)
	{
		if (mBillboardChain)
		{
			mBillboardChain->isInitData(false);
		}

		//EffectElement::sleep();		
	}
	//-----------------------------------------------------------------------
	void BulletSystemBeamElement::setVisibleFlag(uint32 flags)
	{
		if (mBillboardChain)
			mBillboardChain->setVisibilityFlags(flags);
	}

	void BulletSystemBeamElement::copyAttributesTo( BulletSystemBeamElement& target ) const
	{
		target.mNoiseXMin = mNoiseXMin;
		target.mNoiseXMax = mNoiseXMax;
		target.mNoiseYMin = mNoiseYMin;
		target.mNoiseYMax = mNoiseYMax;
		target.mNoiseZMin = mNoiseZMin;
		target.mNoiseZMax = mNoiseZMax;
		target.mNumBillboardElements = mNumBillboardElements;
		target.mWidthStart = mWidthStart;
		target.mWidthEnd = mWidthEnd;
		target.mColourRangeStart = mColourRangeStart;
		target.mColourRangeEnd = mColourRangeEnd;
		target.mMaterialName = mMaterialName;
		target.mFrequency = mFrequency;
	}

	void BulletSystemBeamElement::createElementSceneNode( Ogre::SceneNode* node )
	{
		assert(NULL != node && "BulletSystemBeamElement::createElementSceneNode");

		
		m_sceneNode = EngineManager::getSingleton().getBaseSceneNode()->createChildSceneNode(BLANKSTRING);

	}

	//////////////////////////////////////////////////////////////////////////
	String BulletSystemBeamElement::CmdNoiseXMin::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const BulletSystemBeamElement *>(target)->mNoiseXMin );
	}
	void BulletSystemBeamElement::CmdNoiseXMin::doSet(void* target, const String& val)
	{
		static_cast<BulletSystemBeamElement *>(target)->mNoiseXMin = 
			Ogre::StringConverter::parseReal(val);
	}

	//-----------------------------------------------------------------------
	String BulletSystemBeamElement::CmdNoiseXMax::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const BulletSystemBeamElement *>(target)->mNoiseXMax );
	}
	void BulletSystemBeamElement::CmdNoiseXMax::doSet(void* target, const String& val)
	{
		static_cast<BulletSystemBeamElement *>(target)->mNoiseXMax = 
			Ogre::StringConverter::parseReal(val);
	}

	//-----------------------------------------------------------------------
	String BulletSystemBeamElement::CmdNoiseYMin::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const BulletSystemBeamElement *>(target)->mNoiseYMin );
	}
	void BulletSystemBeamElement::CmdNoiseYMin::doSet(void* target, const String& val)
	{
		static_cast<BulletSystemBeamElement *>(target)->mNoiseYMin = 
			Ogre::StringConverter::parseReal(val);
	}

	//-----------------------------------------------------------------------
	String BulletSystemBeamElement::CmdNoiseYMax::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const BulletSystemBeamElement *>(target)->mNoiseYMax );
	}
	void BulletSystemBeamElement::CmdNoiseYMax::doSet(void* target, const String& val)
	{
		static_cast<BulletSystemBeamElement *>(target)->mNoiseYMax = 
			Ogre::StringConverter::parseReal(val);
	}

	//-----------------------------------------------------------------------
	String BulletSystemBeamElement::CmdNoiseZMin::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const BulletSystemBeamElement *>(target)->mNoiseZMin );
	}
	void BulletSystemBeamElement::CmdNoiseZMin::doSet(void* target, const String& val)
	{
		static_cast<BulletSystemBeamElement *>(target)->mNoiseZMin = 
			Ogre::StringConverter::parseReal(val);
	}

	//-----------------------------------------------------------------------
	String BulletSystemBeamElement::CmdNoiseZMax::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const BulletSystemBeamElement *>(target)->mNoiseZMax );
	}
	void BulletSystemBeamElement::CmdNoiseZMax::doSet(void* target, const String& val)
	{
		static_cast<BulletSystemBeamElement *>(target)->mNoiseZMax = 
			Ogre::StringConverter::parseReal(val);
	}

	//-----------------------------------------------------------------------
	String BulletSystemBeamElement::CmdNumElements::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const BulletSystemBeamElement *>(target)->getNumBillboardElements() );
	}
	void BulletSystemBeamElement::CmdNumElements::doSet(void* target, const String& val)
	{
		static_cast<BulletSystemBeamElement *>(target)->setNumBillboardElements( Ogre::StringConverter::parseInt(val) );
	}

	//-----------------------------------------------------------------------
	String BulletSystemBeamElement::CmdWidthStart::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const BulletSystemBeamElement *>(target)->mWidthStart );
	}
	void BulletSystemBeamElement::CmdWidthStart::doSet(void* target, const String& val)
	{
		static_cast<BulletSystemBeamElement *>(target)->mWidthStart = Ogre::StringConverter::parseReal(val);
	}


	String BulletSystemBeamElement::CmdWidthEnd::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const BulletSystemBeamElement *>(target)->mWidthEnd );
	}
	void BulletSystemBeamElement::CmdWidthEnd::doSet(void* target, const String& val)
	{
		static_cast<BulletSystemBeamElement *>(target)->mWidthEnd = Ogre::StringConverter::parseReal(val);
	}

	//-----------------------------------------------------------------------
	String BulletSystemBeamElement::CmdColour::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const BulletSystemBeamElement*>(target)->getColour() );
	}
	void BulletSystemBeamElement::CmdColour::doSet(void* target, const String& val)
	{
		static_cast<BulletSystemBeamElement*>(target)->setColour(Ogre::StringConverter::parseColourValue(val));
	}

	//-----------------------------------------------------------------------
	String BulletSystemBeamElement::CmdColourRangeStart::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const BulletSystemBeamElement*>(target)->getColourRangeStart() );
	}
	void BulletSystemBeamElement::CmdColourRangeStart::doSet(void* target, const String& val)
	{
		static_cast<BulletSystemBeamElement*>(target)->setColourRangeStart(Ogre::StringConverter::parseColourValue(val));
	}

	//-----------------------------------------------------------------------
	String BulletSystemBeamElement::CmdColourRangeEnd::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const BulletSystemBeamElement*>(target)->getColourRangeEnd() );
	}
	void BulletSystemBeamElement::CmdColourRangeEnd::doSet(void* target, const String& val)
	{
		static_cast<BulletSystemBeamElement*>(target)->setColourRangeEnd(Ogre::StringConverter::parseColourValue(val));
	}

	//-----------------------------------------------------------------------
	String BulletSystemBeamElement::CmdMaterial::doGet(const void* target) const
	{
		return static_cast<const BulletSystemBeamElement *>(target)->getMaterialName();
	}
	void BulletSystemBeamElement::CmdMaterial::doSet(void* target, const String& val)
	{
		static_cast<BulletSystemBeamElement *>(target)->setMaterialName(val);
	}

	//-----------------------------------------------------------------------
	String BulletSystemBeamElement::CmdFrequency::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const BulletSystemBeamElement *>(target)->getFrequency() );
	}
	void BulletSystemBeamElement::CmdFrequency::doSet(void* target, const String& val)
	{
		static_cast<BulletSystemBeamElement *>(target)->setFrequency( Ogre::StringConverter::parseReal(val) );
	}

}