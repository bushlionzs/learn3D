#ifndef OGImpactParticleModule_h__
#define OGImpactParticleModule_h__



#include "OGImpactModule.h"

#include <OgreColourValue.h>

// ogre header
namespace Ogre	{
	class ParticleSystem;
	class Particle;
}

namespace Orphigine	{


	class Projector;

	class ImpactParticleModule : public ImpactModule
	{
	public:

		// 参数命令
		class CmdParticleSystem : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif 
		};       

		class CmdParticleSystemRenderQueueLevel : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif 
		};

		class CmdIsProjector : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif 
		};

		/////////////////////////////////////////////////////////////
		ImpactParticleModule(const String &type);
		~ImpactParticleModule();

		virtual bool createRenderInstance(void);
		virtual void destroyRenderInstance(void);
		virtual void updateRenderInstance( Real time, TransformInfo &info );
		virtual void destroyMe(void);
		virtual bool loadFromStream(Ogre::Serializer* pSerializer,Ogre::DataStreamPtr& stream);
		virtual bool saveToBinaryFile(Ogre::Serializer* pSerializer);
		virtual std::size_t	calcSerializedSize();
		virtual char * readFromBuffer(char * pCurrent);
		virtual void saveToFile(std::ofstream & of);

		void setParticleSystemName(const String &name);

		const String &getParticleSystemName(void) const	{	return mParticleSystemName;	}
		void setTempParticleSystemName(const String &name) { mParticleSystemName = name; }// 临时更改 [2009/06/25 dscky add 请谨慎使用]

		Ogre::ParticleSystem * getParticleSystem(void)	
		{
			return mParticleSystem;
		}

		void setParticleSystem(Ogre::ParticleSystem *system)
		{
			assert (system);
			mParticleSystem = system;
		}



		virtual void sleep(void);

		virtual void active(void);

		virtual bool existVisualElements(void);

		virtual void shutdown(void);

		virtual void setColour( const Ogre::ColourValue& colour );

		/// 设置visible flag
		virtual void setVisibleFlag(uint32 flags);

		/// 设置特效的显示或隐藏
		virtual void setVisible(bool visible);

		int				getParticleSystemRenderQueueLevel() const;
		void			setParticleSystemRenderQueueLevel(int val);

		bool			getIsProjector() const { return mIsProjector; }
		void			setIsProjector(bool bIsProjector) { mIsProjector = bIsProjector; }

		void			setAllProjectorVisible(bool bVisible);

	protected:

		bool _createParticleSystem(void);
		void _destroyParticleSystem(void);

		/// 设置colour affector中的颜色
		void _setAffectorColour(void);

		bool _createProjector();
		void _destroyProjector();

		void _updateProjectorFromParticle(Projector * pProjector,Ogre::Particle * pParticle);

	protected:
		int					m_particleSystemRenderQueueLevel;
		bool				mIsProjector;
		String				mParticleSystemName;

		Ogre::ParticleSystem *mParticleSystem;//对应的粒子系统名称

		bool mIsEmitterEnabled;

		/// 保存粒子系统中原来的颜色，可能是颜色影响器中的原颜色，也可能是粒子系统的颜色
		typedef std::map<String, Ogre::ColourValue> ColourMap;
		ColourMap mColourMap;

		/// 需要在update的时候更改颜色
		bool mNeedUpdateColour;
		/// 当前设置的颜色
		Ogre::ColourValue mCurrentColour;

		////////////////////////////////////////////////////////////////
		static	CmdParticleSystem msParticleSystemCmd;
		static	CmdParticleSystemRenderQueueLevel	ms_particleSystemRenderQueueLevelCmd;
		static  CmdIsProjector msIsProjector;



		//Projector *			mProjector;
		std::vector<Projector *>	mProjectors;

	};
}

#endif // OGImpactParticleModule_h__