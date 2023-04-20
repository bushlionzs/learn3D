#ifndef OGImpact_h__
#define OGImpact_h__


#include <OgreStringInterface.h>
#include <OgreIteratorWrapper.h>
#include "OgreDataStream.h"
#include <OgreQuaternion.h>
#include "OgreColourValue.h"

namespace Orphigine	
{
	class ImpactManager;
	class Engine;

	struct TransformInfo
	{
		TransformInfo(const Ogre::Vector3& pos = Ogre::Vector3::ZERO, const Ogre::Quaternion& rotation = Ogre::Quaternion::IDENTITY, const Ogre::Vector3& scale = Ogre::Vector3::UNIT_SCALE)
			: mPosition(pos)
			, mRotation(rotation)
			, mScale(scale)
		{
		}

		Ogre::Vector3 mPosition;  // 都是世界空间的
		Ogre::Quaternion mRotation;
		Ogre::Vector3 mScale;  // 客户端可能会对角色进行缩放（比如登录时的选人界面，那里显示的角色就是放大了的），这时对武器特效也要相应的缩放，否则特效的位置和大小就不适合角色了
	};

	typedef std::vector<TransformInfo> TransformInfos;

	class _OrphigineExport ImpactBasic
	{
	public:
		ImpactBasic();
		virtual ~ImpactBasic();		

		void setSceneNode( Ogre::SceneNode *node )
		{
			assert (node);
			mBasicNode = node;
		}

		/**	delete the scene node of this effect */
		void deleteSceneNode(void);	

		Ogre::SceneNode *getBasicNode(void)	{	return mBasicNode;	}

		/** dump the scene node info ,for debug */
		void dumpSceneNode(Ogre::SceneNode *node, bool create = true) const;

		/** 该特效是否仍可见（例如粒子系统还在往外发射）
		*/
		virtual bool existVisualElements(void)	{	return false;	}

		/// 设置位移信息或旋转信息
		virtual void setTransformInfo( const TransformInfo &info ) = 0;

		/// 设置特效的显示或隐藏
		virtual void setVisible(bool visible);
		bool getVisible() { return mVisible; }

		virtual void setColour( const Ogre::ColourValue& colour ) { }

		/// 设置visible flag
		virtual void setVisibleFlag(uint32 flags) = 0;

		void getAllMovableObjects(Ogre::RenderQueue *queue);

		virtual bool loadFromStream(Ogre::Serializer* pSerializer,Ogre::DataStreamPtr& stream)=0;
		virtual bool saveToBinaryFile(Ogre::Serializer* pSerializer)=0;
		virtual std::size_t	calcSerializedSize()=0;
	protected:
		Ogre::SceneNode *mBasicNode;
		bool mVisible;
	};


	class ImpactModule;	
	class ImpactModuleFactory;

	class _OrphigineExport Impact : public Ogre::StringInterface, public ImpactBasic
	{
		friend class ImpactManager;
	public:
		typedef std::vector<ImpactModule *> ElementList;
		typedef ElementList::iterator ElementIterator;
		typedef std::map<String, ImpactModuleFactory *> ElementFactoryMap;
		typedef Ogre::MapIterator<ElementFactoryMap> ElementFactoryIterator;

		typedef Ogre::MapIterator<std::map<String,Ogre::ParticleSystem*> > ParticleSystemIterator;

	public:

		class CmdLifeTime : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif
		};

		//////////////////////////////////////////////////////////////////////////
		Impact(const String &templateName);
		virtual ~Impact();

		//EffectElement相关的静态函数
		static bool registerElementFactory(ImpactModuleFactory* pFactory);
		static bool unregisterElementFactory(ImpactModuleFactory* pFactory);	
		//注册/反注册特效元素工厂--每增加一种新类型的特效元素，都得在这2个函数中添加相应的代码
		static bool registerEffectElementFactory();
		static bool unregisterEffectElementFactory();
		static ImpactModule* createElement(const String &elementType);
		static ElementFactoryIterator getElementFactoryIterator(void);

		//得到粒子借口 by changhao
		ParticleSystemIterator getParticleSystemIterator()
		{
			return ParticleSystemIterator(mParticleSystemTemplateNameMap.begin(), mParticleSystemTemplateNameMap.end());
		}

		Ogre::ParticleSystem* getParticleSystemByName(const Ogre::String& name)
		{
			std::map<String,Ogre::ParticleSystem*>::iterator iter = mParticleSystemTemplateNameMap.find(name);
			
			if (iter == mParticleSystemTemplateNameMap.end())
			{
				return NULL;
			}
			else
			{
				return iter->second;
			}
		}

		//当前element共7种:
		//BeamElement、BillboardSetElement、MeshElement、ParticleElement、PointLightElement、ProjectorElement、RibbonEffectElement
		virtual bool loadFromStream(Ogre::Serializer* pSerializer,Ogre::DataStreamPtr& stream);
		virtual bool loadAttribute(Ogre::Serializer* pSerializer,Ogre::DataStreamPtr& stream);
		virtual bool loadElement(Ogre::Serializer* pSerializer,Ogre::DataStreamPtr& stream);
		virtual bool loadParticleSystem(Ogre::Serializer* pSerializer,Ogre::DataStreamPtr& stream);
		virtual bool saveToBinaryFile(Ogre::Serializer* pSerializer);
		virtual bool saveAttribute(Ogre::Serializer* pSerializer);
		virtual bool saveElement(Ogre::Serializer* pSerializer);
		virtual bool saveParticleSystem(Ogre::Serializer* pSerializer);
		virtual std::size_t	calcSerializedSize();
		virtual std::size_t	calcAttributeSize();
		virtual std::size_t	calcElementSize();
		virtual std::size_t	calcParticleSystemSize();


		const String& getTemplateName(void) const	{	return mTemplateName;	}
		void setTemplateName( const String &name )	{	mTemplateName = name;	}

		void dump(std::ofstream &of) const;		

		/// update the effect and its elements, will be called by a controller.
		void updateEffect(Real value);

		/** Assignment operator for copying.
		@remarks
		This operator deep copies all info of the effect.
		*/
		Impact& operator=(const Impact& rhs);

		virtual void setTransformInfo( const TransformInfo &info );

		TransformInfo& getTransformInfo();

		void setExtraTransformInfos( const TransformInfos &infos );

		void reborn(void);

		/** add a child element */
		void addElement( ImpactModule *element );
		void addElement( const String &type );

		void removeAllElements(void);

		/// remove the element,not destroy,just sleep
		void removeElement( ImpactModule *element );

		/// 把effect主节点从它的父节点上卸下来，以便在之后可以挂上别的父节点
		void removeParentSceneNode(void);

		/// destroy the child element
		ElementIterator destroyElement( ElementIterator i );
		void destroyElement( ImpactModule *element );
		void destroyElement( unsigned short index );

		void destroyAllElements(void);

		/**	get the number of child elements */
		unsigned short getNumElements(void) const
		{
			return static_cast<unsigned short>( mElementList.size() );
		}

		ImpactModule *getElement( unsigned short index ) const;

		Ogre::SceneNode* createSceneNode(void);
		void createSceneNode( Ogre::SceneNode *parentNode );

		/**	set the life time of this element
		@param time second
		*/
		void setLifeTime(Real time)	{	mLifeTime = time;	}
		/**	get the born time of this element
		@param time second
		*/
		Real getLifeTime(void) const	{	return mLifeTime;	}

		bool isAlive(void)	{ return mAliveEffect;	}

		virtual bool existVisualElements(void);

		static void setDefaultIterativeInterval(Real time)
		{
			msDefaultIterativeInterval = time;
		}

		static Real getDefaultIterativeInterval(void)
		{
			return msDefaultIterativeInterval;
		}

		void setIterativeInterval(Real time)
		{
			mIterativeInterval = time;
		}

		Real getIterativeInterval(void)
		{
			return mIterativeInterval;
		}

		void shutdown(void);

		virtual void setVisible(bool visible);

		/** 设置特效上各种元素的颜色
		@remarks 会遍历所有的元素，改变各种元素的颜色
		*/
		virtual void setColour( const Ogre::ColourValue& colour );

		/// 设置visible flag
		virtual void setVisibleFlag(uint32 flags);

		void setRemoveParentNode(bool removeParentNode)
		{
			mRemoveParentNode = removeParentNode;
		}
		bool getRemoveParentNode(void)
		{
			return mRemoveParentNode;
		}

		void setDelayRemove(bool delayRemove)
		{
			mDelayRemove = delayRemove;
		}
		bool getDelayRemove(void)
		{
			return mDelayRemove;
		}

		void setPriority(int priority) { this->mPriority = priority;}
		int  getPriority() { return this->mPriority;}
		void enableEffect(bool enable);
		bool isEnable() { return mEnable;}
		void _setVisible(bool visible);
		//end
		void setVersion(int version) {mVersion = version;}
		int  getVersion() {return mVersion;}

		bool hasProjector();

		/// 特效是否在删除时回收
		bool mPutIntoFreePool;

	protected:

		bool initDefaults(void);

		void _updateSelf(Real time);

		void _updateElements(Real time);

	protected:

		String mTemplateName;

		TransformInfo mTransformInfo;//只有跟人物有关的effect才起作用

		/// child elements
		ElementList mElementList;

		/// the life time of this element, is zero by default, if it is zero, the element will live forever.
		Real mLifeTime;

		/// current life time of this element.
		Real mCurrentLifeTime;

		bool mAliveEffect;

		Real mIterateRemainTime;
		Real mIterativeInterval;

		bool mNeedSetVisibleFlags;
		uint32 mVisibleFlags;

		bool mRemoveParentNode;

		bool mDelayRemove;


		int  mPriority;
		bool mEnable;
		//end
		int  mVersion;

		static Real msDefaultIterativeInterval;

		std::map<String,Ogre::ParticleSystem*>			mParticleSystemTemplateNameMap;

		////////////////////////////////////////////////////////////////
		static CmdLifeTime msLifeTimeCmd;

		static std::map<String,ImpactModuleFactory*>	mElementFactoryMap;

	};
}

#endif // OGImpact_h__