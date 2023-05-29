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

		// ��������
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
		void setTempParticleSystemName(const String &name) { mParticleSystemName = name; }// ��ʱ���� [2009/06/25 dscky add �����ʹ��]

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

		/// ����visible flag
		virtual void setVisibleFlag(uint32 flags);

		/// ������Ч����ʾ������
		virtual void setVisible(bool visible);

		int				getParticleSystemRenderQueueLevel() const;
		void			setParticleSystemRenderQueueLevel(int val);

		bool			getIsProjector() const { return mIsProjector; }
		void			setIsProjector(bool bIsProjector) { mIsProjector = bIsProjector; }

		void			setAllProjectorVisible(bool bVisible);

	protected:

		bool _createParticleSystem(void);
		void _destroyParticleSystem(void);

		/// ����colour affector�е���ɫ
		void _setAffectorColour(void);

		bool _createProjector();
		void _destroyProjector();

		void _updateProjectorFromParticle(Projector * pProjector,Ogre::Particle * pParticle);

	protected:
		int					m_particleSystemRenderQueueLevel;
		bool				mIsProjector;
		String				mParticleSystemName;

		Ogre::ParticleSystem *mParticleSystem;//��Ӧ������ϵͳ����

		bool mIsEmitterEnabled;

		/// ��������ϵͳ��ԭ������ɫ����������ɫӰ�����е�ԭ��ɫ��Ҳ����������ϵͳ����ɫ
		typedef std::map<String, Ogre::ColourValue> ColourMap;
		ColourMap mColourMap;

		/// ��Ҫ��update��ʱ�������ɫ
		bool mNeedUpdateColour;
		/// ��ǰ���õ���ɫ
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