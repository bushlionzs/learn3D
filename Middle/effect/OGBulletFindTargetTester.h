#ifndef OGBulletFindTargetTester_h__
#define OGBulletFindTargetTester_h__

#include "OGBulletTester.h"


namespace Orphigine
{
	class BulletEventSystem;
	class BulletSystem;

	class BulletFindTargetTester : public BulletTester
	{
	public:
		BulletFindTargetTester(BulletEventSystem* eventSystem);
		virtual ~BulletFindTargetTester();

		enum PursuitType
		{
			PT_POINTING,
			PT_BEELINE,
			PT_BIZZARD,
			PT_BEAM
		};

		class CmdPursuitType : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif
		};

		class CmdPursuitSpeed : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif
		};

		class CmdArriveDistance : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif
		};

		class CmdTargetOffset : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif
		};

		class CmdForceSourceIndex : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif
		};

		class CmdForceTargetIndex : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
#if OGRE_STRING_INTERFACE_COPY
			virtual void doCopy(void* target, const void* source);
#endif
		};

		virtual void						operateBulletEventSystem(Real timeElapsed);

		const PursuitType&					getPursuitType() const;
		void								setPursuitType(const PursuitType& val);

		const Real&					getPursuitSpeed() const;
		void								setPursuitSpeed(const Real& val);

		const Real&					getArriveDistance() const;
		void								setArriveDistance(const Real& val);

		const Ogre::Vector3&				getTargetOffset() const;
		void								setTargetOffset(const Ogre::Vector3& val);

		int									getForceSourceIndex() const;
		void								setForceSourceIndex(int val);

		int									getForceTargetIndex() const;
		void								setForceTargetIndex(int val);

		static CmdPursuitType				ms_pursuitTypeCmd;
		static CmdPursuitSpeed				ms_pursuitSpeedCmd;
		static CmdArriveDistance			ms_arriveDistanceCmd;
		static CmdTargetOffset				ms_targetOffsetCmd;
		static CmdForceSourceIndex			ms_forceSourceIndexCmd;
		static CmdForceTargetIndex			ms_forceTargetIndexCmd;

	protected:
		void								pursuitTargetAsPointingType();
		void								pursuitTargetAsBeelineType();
		void								pursuitTargetAsBizzardType();
		void								pursuitTargetAsBeamType();
	protected:
		PursuitType							m_pursuitType;
		Real								m_pursuitSpeed;
		Real								m_arriveDistance;
		Ogre::Vector3						m_targetOffset;
		int									m_forceSourceIndex;
		int									m_forceTargetIndex;

		Ogre::Vector3						m_beforePursuitVelocityCache;
		bool								m_isInit;
	};
}
#endif // OGBulletFindTargetTester_h__