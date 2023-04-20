#include "OgreHeader.h"
#include "OGImpactRibandModule.h"
#include "OgreRibbonTrail.h"
#include "ogrescenemanager.h"
#include "ogreparsecommandhelper.h"
#include <platform_log.h>
#include "OGImpactSerializer.h"
#include "OgreSceneNode.h"
#include "engine_manager.h"

namespace Orphigine
{
	namespace
	{
		typedef MemeberValueCopyParamCommand< ImpactRibbonModule, Real, &ImpactRibbonModule::mWidthChange >	sRibbonWidthChangeCommand;
		typedef MemeberValueCopyParamCommand< ImpactRibbonModule, Ogre::ColourValue, &ImpactRibbonModule::mColourChange >	sRibbonColourChangeCommand;

		typedef MemeberValueCopyParamCommand< ImpactRibbonModule, Ogre::ColourValue, &ImpactRibbonModule::mColourStart >	sRibbonColourStartValueCommand;
		typedef MemeberValueCopyParamCommand< ImpactRibbonModule, Real, &ImpactRibbonModule::mWidthStart >	sRibbonWidthStartCommand;


		typedef MemeberValueCopyParamCommand< ImpactRibbonModule, Real, &ImpactRibbonModule::mTrailLength >	sRibbonTrailLengthNumberCommand;
		typedef MemeberValueCopyParamCommand< ImpactRibbonModule, int, &ImpactRibbonModule::mTrailSepNumber >	sRibbonTrailSepNumberCommand;

		typedef MemeberValueCopyParamCommand< ImpactRibbonModule, Real, &ImpactRibbonModule::mWidthMin >	sRibbonTrailWidthMinCommand;

		class __MaterialCommand : public Ogre::ParamCommand
		{
		public:
			virtual Ogre::String doGet(const void* target) const 
			{
				const ImpactRibbonModule* pObj = static_cast<const ImpactRibbonModule*>(target);
				return pObj->getMaterialName();
			}

			virtual void doSet(void* target, const Ogre::String& val) 
			{
				ImpactRibbonModule* pObj = static_cast<ImpactRibbonModule*>(target);
				pObj->setMaterialName( val );
			}

#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source)
			{
				ImpactRibbonModule* pTarget = static_cast<ImpactRibbonModule*>(target);
				const ImpactRibbonModule* pSource = static_cast<const ImpactRibbonModule*>(source);
				pTarget->setMaterialName( pSource->getMaterialName());
			}
#endif
		};

	}

	ImpactRibbonModule::ImpactRibbonModule(const String &type)
		: ImpactModule(type), m_pRibbonTrail(NULL), mWidthChange(0), m_pRibbonSceneNode(NULL),mColourChange(Ogre::ColourValue::ZERO)
		,mTrailLength(100.0f), mTrailSepNumber(20), mColourStart(Ogre::ColourValue::Red), mWidthStart(100), mWidthMin(10)
	{
		mMaterialName = "";
		if ( initDefaults(mElementType) )
		{
			Ogre::ParamDictionary* dict = getParamDictionary();

			static sRibbonWidthChangeCommand	s_ribbonWidthChangeCommand;
			// Custom params      
			dict->addParameter(Ogre::ParameterDef("ribbonwidthchange", 
				"width change of ribbon.",
				Ogre::PT_REAL),&s_ribbonWidthChangeCommand);

			static sRibbonColourChangeCommand	s_ribbonColourChangeCommand;
			dict->addParameter(Ogre::ParameterDef("colourchange", 
				"colour change of ribbon",
				Ogre::PT_COLOURVALUE),&s_ribbonColourChangeCommand);

			static sRibbonColourStartValueCommand	s_ribbonColourStartCommand;
			dict->addParameter(Ogre::ParameterDef("colourstart", 
				"colour start of ribbon",
				Ogre::PT_COLOURVALUE),&s_ribbonColourStartCommand);

			static sRibbonWidthStartCommand	s_ribbonWidthStartCommand;
			dict->addParameter(Ogre::ParameterDef("widthstart", 
				"start width of ribbon",
				Ogre::PT_REAL),&s_ribbonWidthStartCommand);

			static sRibbonTrailSepNumberCommand	s_ribbonTrailSepCommand;
			dict->addParameter(Ogre::ParameterDef("ribbontrailsep", 
				"ribbon trail seperator number",
				Ogre::PT_INT),&s_ribbonTrailSepCommand);

			static sRibbonTrailLengthNumberCommand	s_ribbonTrailLengthCommand;
			dict->addParameter(Ogre::ParameterDef("ribbontraillength", 
				"ribbon trail length",
				Ogre::PT_REAL),&s_ribbonTrailLengthCommand);

			static sRibbonTrailWidthMinCommand	s_ribbonMinWidthCommand;
			dict->addParameter(Ogre::ParameterDef("ribbontrailminwidth", 
				"ribbon trail min width",
				Ogre::PT_REAL),&s_ribbonMinWidthCommand);



			static __MaterialCommand	s_materialCommand;
			dict->addParameter(Ogre::ParameterDef("materialmame", 
				"ribbon trail material",
				Ogre::PT_STRING),&s_materialCommand);

		}
	}

	ImpactRibbonModule::~ImpactRibbonModule(void)
	{
	}

	bool ImpactRibbonModule::createRenderInstance(void)
	{
		Ogre::SceneNode* pAttachNode = mBasicNode;

		return _createRibbonTrail();
	}
	//---------------------------------------------------------------------
	void ImpactRibbonModule::destroyRenderInstance(void)
	{
		_destroyRibbonTrail();

		ImpactModule::destroyRenderInstance();
	}
	//---------------------------------------------------------------------
	void ImpactRibbonModule::updateRenderInstance( Real time, TransformInfo &info )
	{
		if ( mBasicNode )
		{
			_updateRibbonTrail();
		}
	}
	bool ImpactRibbonModule::loadFromStream(Ogre::Serializer* pSerializer,Ogre::DataStreamPtr& stream)
	{
		if(pSerializer && stream->eof() == false)
		{
			unsigned short id = pSerializer->readChunk(stream);
			if(id != ImpactSerializer::EFF_RIBBONEFFECT_ELEMENT)
			{
				WARNING_LOG("Load RibbonEffectElement From Stream Failed. ChunkId Error");
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
			pSerializer->readData(stream,&mWidthStart,1,sizeof(Ogre::Real));
			pSerializer->readData(stream,&mWidthChange,1,sizeof(Ogre::Real));			
			pSerializer->readData(stream,&mColourChange,1,sizeof(Ogre::ColourValue));
			pSerializer->readData(stream,&mColourStart,1,sizeof(Ogre::ColourValue));
			pSerializer->readData(stream,&mTrailLength,1,sizeof(Ogre::Real));
			pSerializer->readData(stream,&mWidthMin,1,sizeof(Ogre::Real));
			pSerializer->readData(stream,&mTrailSepNumber,1,sizeof(int));
			String materialName = pSerializer->readStringBin(stream);
			setMaterialName(materialName);
			return true;	
		}
		return false;
	}
	bool ImpactRibbonModule::saveToBinaryFile(Ogre::Serializer* pSerializer)
	{
		
		return false;
	}
	std::size_t	ImpactRibbonModule::calcSerializedSize()
	{
		size_t tmpSize = Ogre::Serializer::STREAM_OVERHEAD_SIZE;
		//基类成员
		tmpSize += sizeof(mStartTime);
		tmpSize += sizeof(mLifeTime);
		tmpSize += sizeof(mRelPos);
		tmpSize += sizeof(mRelOrientation);
		//自身成员
		tmpSize += sizeof(mWidthStart);
		tmpSize += sizeof(mWidthChange);
		tmpSize += sizeof(mColourChange);
		tmpSize += sizeof(mColourStart);
		tmpSize += sizeof(mTrailLength);
		tmpSize += sizeof(mWidthMin);
		tmpSize += sizeof(mTrailSepNumber);
		tmpSize += mMaterialName.length() + 1;	
		return tmpSize;
	}
	bool ImpactRibbonModule::_createRibbonTrail()
	{
		if( m_pRibbonTrail )
			return true;
		auto sceneMgr = EngineManager::getSingletonPtr()->getSceneManager();
		m_pRibbonTrail = static_cast< Ogre::RibbonTrail *> (sceneMgr->createRibbonTrail( mBasicNode->getName() ) );

		//mBasicNode->attachObject( m_pRibbonTrail );

		m_pRibbonTrail->setNumberOfChains(1);
		m_pRibbonTrail->setMaxChainElements(mTrailSepNumber);
		m_pRibbonTrail->setInitialColour( 0, mColourStart );
		m_pRibbonTrail->setTrailLength(mTrailLength);
		//m_pRibbonTrail->setMinWidth( 0, mWidthMin ); todo123
		m_pRibbonTrail->setColourChange( 0, mColourChange);
		m_pRibbonTrail->setInitialWidth( 0, mWidthStart );
		m_pRibbonTrail->setWidthChange( 0, mWidthChange );


		if( !mMaterialName.empty() )
			m_pRibbonTrail->setMaterialName(mMaterialName, BLANKSTRING);
		m_pRibbonTrail->addNode( mBasicNode );
		SceneNode* baseNode = EngineManager::getSingletonPtr()->getBaseSceneNode();
		m_pRibbonSceneNode = static_cast<Ogre::SceneNode *> (baseNode->createChild( mBasicNode->_getDerivedPosition(), mBasicNode->_getDerivedOrientation() ) );
		m_pRibbonSceneNode->attachObject( m_pRibbonTrail );

		return true;
	}

	bool ImpactRibbonModule::_destroyRibbonTrail()
	{
		if( m_pRibbonSceneNode )
			m_pRibbonSceneNode->detachAllObjects();
		if( m_pRibbonTrail )
		{
			EngineManager::getSingletonPtr()->getSceneManager()->destroyRibbonTrail( m_pRibbonTrail->getName() );
			m_pRibbonTrail = NULL;
		}

		m_pRibbonSceneNode->getCreator()->destroySceneNode(m_pRibbonSceneNode);
		return true;
	}

	bool ImpactRibbonModule::_updateRibbonTrail()
	{
		//m_pRibbonTrail->_timeUpdate();
		_destroyRibbonTrail();
		_createRibbonTrail();
		return true;
	}


	void ImpactRibbonModule::setVisibleFlag(uint32 flags) 
	{
	}

	void	ImpactRibbonModule::setMaterialName( const String &m )
	{
		mMaterialName = m;
		if( m_pRibbonTrail )
			m_pRibbonTrail->setMaterialName(mMaterialName, BLANKSTRING);
	}

}

