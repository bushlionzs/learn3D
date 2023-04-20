#ifndef OgreMeshComponentRotationAffector_h__
#define OgreMeshComponentRotationAffector_h__


#include "OgreParticleAffector.h"
#include "OgreVector3.h"

namespace Ogre 
{
	enum RotationType
	{
		YAW,
		PITCH,
		ROLL,
	};
	class MeshComponentOrientationAffector : public ParticleAffector
	{
	public:

		class CmdYawOrientationSpeedRangeStart : public ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		class CmdYawOrientationSpeedRangeEnd : public ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		class CmdYawOrientationRangeStart : public ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		class CmdYawOrientationRangeEnd : public ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		class CmdPitchOrientationSpeedRangeStart : public ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		class CmdPitchOrientationSpeedRangeEnd : public ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		class CmdPitchOrientationRangeStart : public ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		class CmdPitchOrientationRangeEnd : public ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		class CmdRollOrientationSpeedRangeStart : public ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		class CmdRollOrientationSpeedRangeEnd : public ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		class CmdRollOrientationRangeStart : public ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		class CmdRollOrientationRangeEnd : public ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		MeshComponentOrientationAffector(ParticleSystem* psys);

		void _initParticle(Particle* pParticle);
		void _affectParticles(ParticleSystem* pSystem, Real timeElapsed);

		void setRotationOrientationRangeStart(const Radian& angle, RotationType type);
#ifndef OGRE_FORCE_ANGLE_TYPES
		inline void setRotationOrientationRangeStart(Real angle, RotationType type) 
		{
			setRotationOrientationRangeStart(Angle(angle), type);
		}
#endif//OGRE_FORCE_ANGLE_TYPES
		void setOrientationSpeedRangeEnd(const Radian& angle, RotationType type);
#ifndef OGRE_FORCE_ANGLE_TYPES
		inline void setOrientationSpeedRangeEnd(Real angle, RotationType type) 
		{
			setOrientationSpeedRangeEnd(Angle(angle), type);
		}
#endif//OGRE_FORCE_ANGLE_TYPES
		const Radian& getOrientationSpeedRangeStart(RotationType type) const;
		const Radian& getOrientationSpeedRangeEnd(RotationType type) const;

		void setOrientationRangeStart(const Radian& angle, RotationType type);
#ifndef OGRE_FORCE_ANGLE_TYPES
		inline void setOrientationRangeStart(Real angle, RotationType type) 
		{
			setOrientationRangeStart(Angle(angle), type);
		}
#endif//OGRE_FORCE_ANGLE_TYPES
		void setOrientationRangeEnd(const Radian& angle, RotationType type);
#ifndef OGRE_FORCE_ANGLE_TYPES
		inline void setOrientationRangeEnd(Real angle, RotationType type) 
		{
			setOrientationRangeEnd(Angle(angle), type);
		}
#endif//OGRE_FORCE_ANGLE_TYPES
		const Radian& getOrientationRangeStart(RotationType type) const;
		const Radian& getOrientationRangeEnd(RotationType type) const;

		virtual bool loadFromStream(Serializer* pSerializer,DataStreamPtr& stream);
		virtual bool saveToBinaryFile(Serializer* pSerializer);
		virtual std::size_t	calcSerializedSize();
		virtual char * readFromBuffer(char * pCurrent);
		virtual void saveToFile(std::ofstream & of);

		//////////////////////////////////////////////////////////////////////////
		static CmdYawOrientationSpeedRangeStart		msYawOrientationSpeedRangeStartCmd;
		static CmdYawOrientationSpeedRangeEnd		msYawOrientationSpeedRangeEndCmd;
		static CmdYawOrientationRangeStart			msYawOrientationRangeStartCmd;
		static CmdYawOrientationRangeEnd			msYawOrientationRangeEndCmd;

		static CmdPitchOrientationSpeedRangeStart	msPitchOrientationSpeedRangeStartCmd;
		static CmdPitchOrientationSpeedRangeEnd		msPitchOrientationSpeedRangeEndCmd;
		static CmdPitchOrientationRangeStart		msPitchOrientationRangeStartCmd;
		static CmdPitchOrientationRangeEnd			msPitchOrientationRangeEndCmd;

		static CmdRollOrientationSpeedRangeStart	msRollOrientationSpeedRangeStartCmd;
		static CmdRollOrientationSpeedRangeEnd		msRollOrientationSpeedRangeEndCmd;
		static CmdRollOrientationRangeStart			msRollOrientationRangeStartCmd;
		static CmdRollOrientationRangeEnd			msRollOrientationRangeEndCmd;

	protected:
		Radian mYawOrientationSpeedRangeStart;
		Radian mYawOrientationSpeedRangeEnd;
		Radian mYawOrientationRangeStart;
		Radian mYawOrientationRangeEnd;

		Radian mPitchOrientationSpeedRangeStart;
		Radian mPitchOrientationSpeedRangeEnd;
		Radian mPitchOrientationRangeStart;
		Radian mPitchOrientationRangeEnd;

		Radian mRollOrientationSpeedRangeStart;
		Radian mRollOrientationSpeedRangeEnd;
		Radian mRollOrientationRangeStart;
		Radian mRollOrientationRangeEnd;
	};
}

#endif // OgreMeshComponentRotationAffector_h__
