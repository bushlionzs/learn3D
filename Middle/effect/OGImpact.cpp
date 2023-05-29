#include "OgreHeader.h"
#include "OGImpact.h"
#include "OGImpactModule.h"
#include "OGImpactManager.h"
#include "OGImpactParticleModule.h"
#include "OGFlags.h"
#include "OGImpactSerializer.h"
#include "OGImpactModuleFactory.h"

// ogre header
#include <OgreSceneNode.h>
#include <OgreSceneManager.h>
#include <OgreStringConverter.h>
#include <OgreParticleSystemManager.h>
#include <OgreParticleSystem.h>
#include <platform_log.h>
#include "OgreString.h"
#include "engine_manager.h"

namespace Orphigine	
{

	///////////////////////////////////////////////////////////////////////
	ImpactBasic::ImpactBasic() :
	mBasicNode(NULL),
	mVisible(true)	
	{
	}
	//---------------------------------------------------------------------
	ImpactBasic::~ImpactBasic()
	{
		deleteSceneNode();
	}    

	//---------------------------------------------------------------------
	void ImpactBasic::deleteSceneNode(void)
	{
		if (mBasicNode)
		{
			mBasicNode->getCreator()->destroySceneNode(mBasicNode);
			mBasicNode = NULL;
		}		
	}

	void ImpactBasic::dumpSceneNode(Ogre::SceneNode *node, bool create) const
	{
		
	}	

	void ImpactBasic::getAllMovableObjects(Ogre::RenderQueue *queue)
	{
		
	}
	void ImpactBasic::setVisible(bool visible)
	{		
		// mBasicNode->setVisible(visible);
		if (visible != mVisible)
		{
			mVisible = visible;

			if (mBasicNode)
				mBasicNode->setVisible(mVisible);
		}
	}

	//-----------------------------------------------------------------------
	Real Impact::msDefaultIterativeInterval = 0;

	Impact::CmdLifeTime Impact::msLifeTimeCmd;
	std::map< String,ImpactModuleFactory* > Impact::mElementFactoryMap;

	//---------------------------------------------------------------------
	Impact::Impact(const String &templateName)	: 
	ImpactBasic(),
		mTemplateName(templateName),
		mLifeTime(0.0f),
		mCurrentLifeTime(0.0f),
		mAliveEffect(true),
		mIterativeInterval(msDefaultIterativeInterval),
		mIterateRemainTime(0.0f),
		mNeedSetVisibleFlags(false),
		mVisibleFlags(OVF_DEFAULT),
		mRemoveParentNode(false),
		mDelayRemove(false),
		mPutIntoFreePool(true),
		mPriority(3),
		mEnable(true),
		mVersion(100)
	{	
		initDefaults();
		mElementList.clear();//一个effect可以包含多个element
	}
	//---------------------------------------------------------------------
	Impact::~Impact()
	{		
		destroyAllElements();
	}
	bool Impact::registerElementFactory(ImpactModuleFactory* pFactory)
	{
		if(pFactory)
		{
			std::pair<ElementFactoryMap::iterator, bool> inserted;
			inserted = mElementFactoryMap.insert( ElementFactoryMap::value_type(pFactory->getName(),pFactory));
			assert (inserted.second);
			return true;
		}
		return false;
	}
	bool Impact::unregisterElementFactory(ImpactModuleFactory* pFactory)
	{
		if(pFactory)
		{
			std::map< String,ImpactModuleFactory* >::iterator itElementFactory = mElementFactoryMap.find(pFactory->getName());
			if(itElementFactory!=mElementFactoryMap.end())
			{
				mElementFactoryMap.erase(itElementFactory);
			}
			return true;
		}
		return false;		
	}
	//---------------------------------------------------------------------
	bool Impact::registerEffectElementFactory()
	{
		registerElementFactory(ImpactParticleModuleFactory::getFactory() );
		registerElementFactory(ImpactMeshModuleFactory::getFactory() );
		registerElementFactory(ImpactBillboardSetModuleFactory::getFactory() );
		registerElementFactory(ImpactProjectorModuleFactory::getFactory() );
		registerElementFactory(ImpactBeamModuleFactory::getFactory() ); 
		registerElementFactory(ImpactPointLightModuleFactory::getFactory() );
		registerElementFactory(ImpactRibandModuleFactory::getFactory() );
		return true;
	}
	bool Impact::unregisterEffectElementFactory()
	{
		unregisterElementFactory(ImpactParticleModuleFactory::getFactory());
		unregisterElementFactory(ImpactMeshModuleFactory::getFactory());
		unregisterElementFactory(ImpactBillboardSetModuleFactory::getFactory());
		unregisterElementFactory(ImpactProjectorModuleFactory::getFactory());
		unregisterElementFactory(ImpactBeamModuleFactory::getFactory()); 
		unregisterElementFactory(ImpactPointLightModuleFactory::getFactory());
		unregisterElementFactory(ImpactRibandModuleFactory::getFactory());
		return true;
	}
	ImpactModule* Impact::createElement(const String &elementType)
	{
		ElementFactoryMap::const_iterator itElementFactory = mElementFactoryMap.find(elementType);
		if ( itElementFactory == mElementFactoryMap.end() )
		{
			// exception
			OGRE_EXCEPT(Ogre::Exception::ERR_ITEM_NOT_FOUND, 
				"the effect element type '" + elementType + "' didn't exist!",
				"Effect::createElement");
		}
		ImpactModuleFactory* pFactory = itElementFactory->second;
		if(pFactory)
		{
			ImpactModule* pElement = pFactory->createElement();
			return pElement;
		}
		return NULL;
	}	
	Impact::ElementFactoryIterator Impact::getElementFactoryIterator()
	{	
		return ElementFactoryIterator(
			mElementFactoryMap.begin(), mElementFactoryMap.end());
	}	
	//---------------------------------------------------------------------
	void Impact::dump(std::ofstream &of) const
	{
		of << "effect " << std::endl;

		for ( ElementList::const_iterator i = mElementList.begin();
			i != mElementList.end();	++i	)
		{
			//	(*i)->dump(of);			
		}
		of << "end of effect " << std::endl;
	}
	//---------------------------------------------------------------------
	void Impact::updateEffect(Real value)
	{
		if ( mAliveEffect )
		{
			if (mIterativeInterval > 0)
			{
				mIterateRemainTime += value;

				while (mIterateRemainTime >= mIterativeInterval)
				{
					_updateSelf(mIterativeInterval);	

					_updateElements(mIterativeInterval);

					mIterateRemainTime -= mIterativeInterval;
				}				
			}
			else
			{
				_updateSelf(value);

				_updateElements(value);
			}

			if (mNeedSetVisibleFlags)
			{
				// 对所有的元素进行visible设置
				if (mElementList.size() > 0)
				{			
					ElementList::iterator i = mElementList.begin();

					while ( i != mElementList.end() )
					{
						ImpactModule *element = *i;
						assert (element);

						if ( element->isActive() && ( false == element->isDestroy() ) )
						{				
							element->setVisibleFlag(mVisibleFlags);
						}				

						++i;
					}
				}

				mNeedSetVisibleFlags = false;
			}
		}		
	}
	//---------------------------------------------------------------------
	void Impact::_updateSelf(Real time)
	{
		if ( mLifeTime > 0.0f )
		{
			//　calculate the life time
			Real currentTime = mCurrentLifeTime + time;

			// if the life time is zero ,the elements of the effect will not be deleted.
			if ( currentTime > mLifeTime )
			{
				// destroy
				removeAllElements();

				mAliveEffect = false;
				return;
			}
			else
				mCurrentLifeTime = currentTime;
		}
	}
	//---------------------------------------------------------------------
	void Impact::_updateElements(Real time)
	{
		if (mElementList.size() > 0)
		{			
			ElementList::iterator i = mElementList.begin();

			while ( i != mElementList.end() )
			{
				ImpactModule *element = *i;
				assert (element);

				if (element->isActive())
				{
					// the lifetime of the element is reached. 
					if (element->isDestroy())
					{
						//	i =	removeElement(i);
						removeElement(*i);
					}
					else
					{
						element->update(time, mTransformInfo);
					}
				}				

				++i;
			}
		}
	}
	//---------------------------------------------------------------------
	Impact& Impact::operator=(const Impact& rhs)
	{
		destroyAllElements();

		// copy elements
		for ( ElementList::const_iterator i = rhs.mElementList.begin();
			i != rhs.mElementList.end(); ++i )
		{
			ImpactModule *temElement = (*i);
			assert (temElement);

			ImpactModule *element = createElement(temElement->getType());
			temElement->copyParametersTo(element);

			addElement(element);
		}

		// copy effect parameter
		rhs.copyParametersTo(this);

		return *this;
	}
	//---------------------------------------------------------------------
	void Impact::reborn(void)
	{
		mCurrentLifeTime = 0.0f;
		mAliveEffect = true;

		mDelayRemove = false;
		mRemoveParentNode = false;

		mNeedSetVisibleFlags = false;
		mVisibleFlags = OVF_DEFAULT;

		mPriority = 3;
		mEnable = true;

		//       mTransformInfo.mPosition = Ogre::Vector3::ZERO;
		//       mTransformInfo.mRotation = Ogre::Quaternion::IDENTITY;

		if (mElementList.size() > 0)
		{			
			ElementList::iterator i = mElementList.begin();

			while ( i != mElementList.end() )
			{
				ImpactModule *element = *i;
				assert (element);

				element->active();

				// 设置visible属性为默认值true
				element->setVisible(true);

				// 设置visible flag为默认值
				element->setVisibleFlag(OVF_DEFAULT);

				//               element->setTransformInfo(mTransformInfo);

				++i;
			}
		}
	}
	//---------------------------------------------------------------------
	void Impact::addElement( ImpactModule *element )
	{
		assert (element);

		mElementList.push_back(element);
		element->setParent(this);
	}
	//---------------------------------------------------------------------
	Impact::ElementIterator Impact::destroyElement( ElementIterator i )
	{
		delete (*i);
		(*i) = NULL;
		return mElementList.erase(i);
	}
	//---------------------------------------------------------------------
	void Impact::destroyElement( ImpactModule *element )
	{
		assert (element);
		for ( ElementList::iterator i = mElementList.begin();
			i != mElementList.end();	++i	)
		{
			if ((*i) == element)
			{
				delete (*i);
				(*i) = NULL;
				mElementList.erase(i);
				break;
			}
		}		
	}
	//---------------------------------------------------------------------
	void Impact::destroyElement( unsigned short index )
	{
		assert(index < mElementList.size() && "element index out of bounds!");
		ElementList::iterator i = mElementList.begin() + index;
		destroyElement(i);
	}
	//---------------------------------------------------------------------
	void Impact::removeElement( ImpactModule *element )
	{
		assert (element);
		element->sleep();
	}
	//---------------------------------------------------------------------
	void Impact::removeAllElements(void)
	{
		for ( ElementList::iterator i = mElementList.begin();
			i != mElementList.end();	++i	)
		{
			if ((*i))
			{
				removeElement(*i);
			}
		}
	}
	//---------------------------------------------------------------------
	void Impact::removeParentSceneNode(void)
	{
		mBasicNode->getParent()->removeChild(mBasicNode);
	}
	//---------------------------------------------------------------------
	void Impact::destroyAllElements(void)
	{
		for ( ElementList::iterator i = mElementList.begin();
			i != mElementList.end();	++i	)
		{			
			if (*i)
			{
				delete *i;
				*i = NULL;
			}
		}
		mElementList.clear();
	}
	static uint32_t impact_index = 0;
	//---------------------------------------------------------------------
	Ogre::SceneNode* Impact::createSceneNode(void)
	{
		// if the scene node isn't null, the effect is exist(it is recreated from free list), so
		// we don't need to create the scene node.
		if ( mBasicNode )
			return mBasicNode;

		Ogre::SceneNode* baseNode = EngineManager::getSingletonPtr()->getBaseSceneNode();
		assert (baseNode);

		

		String name = Ogre::StringUtil::format("Impact:%d", impact_index++);
		mBasicNode = baseNode->createChildSceneNode(name);

		assert (mBasicNode);

		//dumpSceneNode(mBasicNode);

		// create the scene node of the element
		for ( ElementList::iterator i = mElementList.begin();
			i != mElementList.end();	++i	)
		{
			if ((*i))
			{
				(*i)->createSceneNode(mBasicNode);
			}
		}

		return mBasicNode;
	}
	//---------------------------------------------------------------------
	void Impact::createSceneNode( Ogre::SceneNode *parentNode )
	{
		assert (parentNode);


		if (mBasicNode)
		{
			//assert (mBasicNode->getParent() == NULL);
			// 如果已经挂在别的节点上了，就先解挂
			// 如果这个effect是从freelist中得到的，而且他上次创建的是用
			// createSceneNode（不带参数，例如LogicModel中的addEffect），
			// 当removeEffect时，并不会接触它与父节点的关系，所以这时他
			// 是有parent的，这时就先要接触它与父节点的关系
			if (mBasicNode->getParent())
			{
				mBasicNode->getParent()->removeChild(mBasicNode);
			}
			parentNode->addChild(mBasicNode);
		}
		else
		{
			String name = Ogre::StringUtil::format("Impact:%d", impact_index++);
			mBasicNode = parentNode->createChildSceneNode(name);

			int kk = 0;
			// create the scene node of the element
			for ( ElementList::iterator i = mElementList.begin();
				i != mElementList.end();	++i	, ++kk)
			{
				if ((*i))
				{
					(*i)->createSceneNode(mBasicNode);
				}
				
			}
		}

		assert (mBasicNode);
	}
	//---------------------------------------------------------------------
	ImpactModule * Impact::getElement( unsigned short index ) const
	{
		assert(index < mElementList.size() && "element index out of bounds!");
		return mElementList[index];
	}
	//---------------------------------------------------------------------
	void Impact::addElement( const String &type )
	{
		ImpactModule *element = createElement(type);
		assert (element);
		element->createSceneNode(mBasicNode);
		addElement(element);
	}
	//---------------------------------------------------------------------
	bool Impact::initDefaults(void)
	{		
		if (createParamDictionary("Effect"))
		{
			Ogre::ParamDictionary* dict = getParamDictionary();//effect的一个基本参数是lifeTime

			dict->addParameter(Ogre::ParameterDef("LifeTime", 
				"the life time of this effect.",
				Ogre::PT_REAL),&msLifeTimeCmd);		

			return true;

		}
		return false;
	}
	//---------------------------------------------------------------------
	bool Impact::existVisualElements(void)
	{
		for (unsigned short i=0; i<getNumElements(); ++i)
		{
			ImpactModule *element = getElement(i);

			if (element->existVisualElements())
				return true;
		}

		return false;
	}
	//---------------------------------------------------------------------
	void Impact::setExtraTransformInfos( const TransformInfos &infos )
	{
		for (unsigned short i=0; i<getNumElements(); ++i)
		{
			getElement(i)->updateExtraTransformInfos(infos);
		}
	}
	//---------------------------------------------------------------------
	void Impact::shutdown(void)
	{
		for (unsigned short i=0; i<getNumElements(); ++i)
		{
			ImpactModule *element = getElement(i);

			element->shutdown();
		}
	}
	//---------------------------------------------------------------------
	void Impact::setTransformInfo( const TransformInfo &info )
	{	
		mTransformInfo = info;

		// 马上对element进行transform信息的设置，避免延迟
		if (mElementList.size() > 0)
		{			
			ElementList::iterator i = mElementList.begin();

			while ( i != mElementList.end() )
			{
				ImpactModule *element = *i;
				assert (element);

				if ( element->isActive() && ( false == element->isDestroy() ) )
				{				
					element->setTransformInfo(mTransformInfo);
				}				

				++i;
			}
		}
	}

	void Impact::enableEffect(bool enable)
	{
		//if (mEnable == enable)
		//	return;
		this->mEnable = enable;

		_setVisible(mVisible && mEnable);
	}
	//---------------------------------------------------------------------
	void Impact::_setVisible(bool visible)
	{
		//EffectBasic::setVisible(visible);
		if (mBasicNode)
			mBasicNode->setVisible(visible);

		// 对所有的元素进行visible设置
		if (mElementList.size() > 0)
		{			
			ElementList::iterator i = mElementList.begin();

			while ( i != mElementList.end() )
			{
				ImpactModule *element = *i;
				assert (element);

				if ( element->isActive() && ( false == element->isDestroy() ) )
				{				
					element->setVisible(visible);
				}				

				++i;
			}
		}
	}

	//---------------------------------------------------------------------
	void Impact::setVisible(bool visible)
	{ 
		//if (mVisible == visible)
		//	return;
		mVisible = visible;

		_setVisible(mVisible && mEnable);
		//end
	}
	//end
	//---------------------------------------------------------------------
	void Impact::setColour( const Ogre::ColourValue& colour )
	{
		// 对所有的元素进行visible设置
		if (mElementList.size() > 0)
		{			
			ElementList::iterator i = mElementList.begin();

			while ( i != mElementList.end() )
			{
				ImpactModule *element = *i;
				assert (element);

				if ( element->isActive() && ( false == element->isDestroy() ) )
				{				
					element->setColour(colour);
				}				

				++i;
			}
		}
	}
	//---------------------------------------------------------------------
	void Impact::setVisibleFlag(uint32 flags)
	{
		mVisibleFlags = flags;
		mNeedSetVisibleFlags = true;
		//// 对所有的元素进行visible设置
		//if (mElementList.size() > 0)
		//{			
		//    ElementList::iterator i = mElementList.begin();

		//    while ( i != mElementList.end() )
		//    {
		//        EffectElement *element = *i;
		//        assert (element);

		//        if ( element->isActive() && ( false == element->isDestroy() ) )
		//        {				
		//            element->setVisibleFlag(flags);
		//        }				

		//        ++i;
		//    }
		//}
	}

	TransformInfo& Impact::getTransformInfo()
	{
		return mTransformInfo;
	}


	bool Impact::hasProjector()
	{
		ElementList::iterator it = mElementList.begin();
		for ( ; it != mElementList.end(); it++ )
		{
			if ( (*it)->getType() == "Particle" && static_cast<ImpactParticleModule *>(*it)->getIsProjector() )
			{
				return true;
			}
		}
		return false;
	}
	bool Impact::loadFromStream(Ogre::Serializer* pSerializer,Ogre::DataStreamPtr& stream)
	{
		if(pSerializer && stream->eof() == false)
		{
			unsigned short chunkId = pSerializer->readChunk(stream);
			if(chunkId != ImpactSerializer::EFF_EFFECT)
			{
				WARNING_LOG("Load Effect From Stream Failed. ChunkId Error");
				// 因为不读取，所以直接跳过相应数据段长
				pSerializer->skipChunk(stream);
				return false;
			}
			mParticleSystemTemplateNameMap.clear();

			//属性
			loadAttribute(pSerializer,stream);			

			//element
			loadElement(pSerializer,stream);

			//ParticleSystem
			loadParticleSystem(pSerializer,stream);			

			return true;
		}
		return false;
	}
	bool Impact::saveToBinaryFile(Ogre::Serializer* pSerializer)
	{
		return false;
	}
	std::size_t	Impact::calcSerializedSize()
	{
		return 0;
	}
	bool Impact::loadAttribute(Ogre::Serializer* pSerializer,Ogre::DataStreamPtr& stream)
	{
		pSerializer->readData(stream,&mVisible,1,sizeof(mVisible));
		String effectName = pSerializer->readStringBin(stream);
		setTemplateName(effectName); 
		//属性--属性型解析

		//属性--二进制解析
		pSerializer->readData(stream,&mLifeTime,1,sizeof(mLifeTime));

		return true;
	}
	bool Impact::saveAttribute(Ogre::Serializer* pSerializer)
	{
		
		return true;
	}
	std::size_t	Impact::calcAttributeSize()
	{
		size_t tmpSize = 0 ;
		tmpSize += sizeof(mVisible);
		tmpSize += mTemplateName.length() + 1;	
		//属性--属性型解析
		/*
		const Ogre::ParameterList& param = getParameters();
		size_t paramSize = param.size();
		tmpSize += sizeof(paramSize);
		for( size_t paramIndex = 0 ; paramIndex != paramSize ; ++paramIndex)
		{
		String name = param[paramIndex].name;
		String value = getParameter(name);
		tmpSize += name.length() + 1;	
		tmpSize += value.length() + 1;	
		}
		*/
		//属性--二进制解析
		tmpSize += sizeof(mLifeTime);
		return tmpSize;
	}
	bool Impact::loadElement(Ogre::Serializer* pSerializer,Ogre::DataStreamPtr& stream)
	{
		int32_t elementNum = 0;
		pSerializer->readData(stream,&elementNum,1,sizeof(elementNum));
		for (int32_t elementIndex = 0 ; elementIndex != elementNum ; ++elementIndex )
		{
			//类型
			String type = pSerializer->readStringBin(stream);
			ImpactModule *pElement =createElement(type);
			assert(pElement);
			addElement(pElement);
			//element属性--属性型解析
			/*
			size_t elemParamSize = 0;
			pSerializer->readData(stream,&elemParamSize,1,sizeof(elemParamSize));
			for(size_t elemParamIndex = 0 ; elemParamIndex != elemParamSize ; ++elemParamIndex)
			{
			String name = pSerializer->readStringBin(stream);
			String value = pSerializer->readStringBin(stream);
			pElement->setParameter(name,value);
			}
			*/
			//element属性--二进制解析
			pElement->loadFromStream(pSerializer,stream);
			if(type == "Particle")
			{
				Ogre::ParticleSystem* pParticleSystem = NULL;
				mParticleSystemTemplateNameMap.insert(std::make_pair(((ImpactParticleModule*)pElement)->getParticleSystemName(),pParticleSystem));
				//particleSystemNameMap.insert(((ImpactParticleModule*)pElement)->getParticleSystemName());
			}
		}
		return true;
	}	
	bool Impact::saveElement(Ogre::Serializer* pSerializer)
	{
		

		return true;
	}
	std::size_t	Impact::calcElementSize()
	{
		size_t tmpSize = 0 ;
		size_t elementNum = mElementList.size();
		tmpSize += sizeof(elementNum);
		for ( size_t elementIndex = 0 ; elementIndex != elementNum ; ++elementIndex )
		{
			ImpactModule *pElement = mElementList[elementIndex];
			//类型
			tmpSize += pElement->getType().length() + 1;	
			//element属性--属性型解析
			/*
			const Ogre::ParameterList& elemParam = pElement->getParameters();
			size_t elemParamSize = elemParam.size();
			tmpSize += sizeof(elemParamSize);
			for( size_t elemParamIndex = 0 ; elemParamIndex != elemParamSize ; ++elemParamIndex)
			{
			String name = elemParam[elemParamIndex].name;
			String value = pElement->getParameter(name);
			tmpSize += name.length() + 1;	
			tmpSize += value.length() + 1;	
			}
			*/
			//element属性--二进制解析
			tmpSize += pElement->calcSerializedSize();
			//ParticleSystemName
			if(pElement->getType() == "Particle")
			{
				mParticleSystemTemplateNameMap.insert(std::make_pair(((ImpactParticleModule*)pElement)->getParticleSystemName(),((ImpactParticleModule*)pElement)->getParticleSystem()));
			}
		}		
		return tmpSize;
	}
	bool Impact::loadParticleSystem(Ogre::Serializer* pSerializer,Ogre::DataStreamPtr& stream)
	{
		std::map<String,Ogre::ParticleSystem*>::iterator itPSName = mParticleSystemTemplateNameMap.begin();
		while(itPSName!=mParticleSystemTemplateNameMap.end())
		{
			String psName = itPSName->first;
			itPSName->second =  new Ogre::ParticleSystem(itPSName->first, BLANKSTRING);
			assert(itPSName->second);
			itPSName->second->_notifyOrigin(stream->getName());
			itPSName->second->loadFromStream(pSerializer, stream, mVersion);
			++itPSName;
		}
		return true;
	}
	bool Impact::saveParticleSystem(Ogre::Serializer* pSerializer)
	{
		
		return true;
	}		
	std::size_t	Impact::calcParticleSystemSize()
	{
		size_t tmpSize = 0 ;
				

		return tmpSize;
	}
	//////////////////////////////////////////////////////////////////////////
	//-----------------------------------------------------------------------
	String Impact::CmdLifeTime::doGet(const void* target) const
	{
		return Ogre::StringConverter::toString(
			static_cast<const Impact *>(target)->getLifeTime() );
	}
	//---------------------------------------------------------------------
	void Impact::CmdLifeTime::doSet(void* target, const String& val)
	{
		static_cast<Impact *>(target)->setLifeTime(Ogre::StringConverter::parseReal(val));
	}
#if OGRE_STRING_INTERFACE_COPY
	//-----------------------------------------------------------------------
	void Impact::CmdLifeTime::doCopy(void* target, const void* source)
	{
		static_cast<Impact *>(target)->setLifeTime(
			static_cast<const Impact *>(source)->getLifeTime() );
	}
#endif
}