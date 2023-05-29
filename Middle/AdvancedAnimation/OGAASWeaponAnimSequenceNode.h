#ifndef OGAASWeaponAnimSequenceNode_h__
#define OGAASWeaponAnimSequenceNode_h__

#include "OGAASAnimSequenceNode.h"

#include "OgreAnimationState.h"

namespace Orphigine
{
	class AdvancedAnimationSystem;

	class AASWeaponAnimSequenceNode : public AASAnimSequenceNode
	{
	public:
		AASWeaponAnimSequenceNode(AdvancedAnimationSystem* system,unsigned short handle);
		AASWeaponAnimSequenceNode(String name, AdvancedAnimationSystem* system,unsigned short handle);
		
		virtual bool	initParameter(const String& typeName);

		virtual ~AASWeaponAnimSequenceNode();

		virtual void	writeToBinary(AdvancedAnimationSystemSerializerImpl* serializer,
			AdvancedAnimationSystem* system);

		virtual void	readFromBinary(AdvancedAnimationSystemSerializerImpl* serializer,Ogre::DataStreamPtr& stream,
			AdvancedAnimationSystem* system);

		virtual size_t	calcSize(AdvancedAnimationSystemSerializerImpl* serializer);

		virtual void	copyParameters(AASNode* dest);

		const Ogre::String&			getLongHandle() const;
		void							setLongHandle(const Ogre::String& val);

		const Ogre::String&			getFalchion() const;
		void							setFalchion(const Ogre::String& val);

		const Ogre::String&			getGavel() const;
		void							setGavel(const Ogre::String& val);

		const Ogre::String&			getBow() const;
		void							setBow(const Ogre::String& val);

		const Ogre::String&			getGun() const;
		void							setGun(const Ogre::String& val);

		const Ogre::String&			getSword() const;
		void							setSword(const Ogre::String& val);

		const Ogre::String&			getFlag() const;
		void							setFlag(const Ogre::String& val);

		const Ogre::String&			getUnarmed() const;
		void							setUnarmed(const Ogre::String& val);

		const Ogre::String&			getWand() const;
		void							setWand(const Ogre::String& val);

		const Ogre::String&			getEpee() const;
		void							setEpee(const Ogre::String& val);

		virtual	void					_refreshAnimation();

		class CmdLongHandle : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		class CmdFalchion : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		class CmdGavel : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		class CmdBow : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		class CmdGun : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		class CmdSword : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		class CmdFlag : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		class CmdUnarmed : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		class CmdWand : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		class CmdEpee : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		static	CmdLongHandle		ms_longHandleCmd;
		static	CmdFalchion			ms_falchionCmd;
		static	CmdGavel			ms_gavelCmd;
		static	CmdBow				ms_bowCmd;
		static	CmdGun				ms_gunCmd;
		static	CmdSword			ms_swordCmd;
		static	CmdFlag				ms_flagCmd;
		static	CmdUnarmed			ms_unarmedCmd;
		static	CmdWand				ms_wandCmd;
		static	CmdEpee				ms_epeeCmd;
	protected:
		virtual String   			_getAnimationByWeaponTypeName(const String& weaponType);
	protected:
		//std::map<String,String>	m_animByWeaponPair;

		/*
		
		³¤±ú	LongHandle
			µ¶ falchion
			é³	gavel
			¹­¼ý bow
			»ðÇ¹ Gun
			½£ sword
			Æì×Ó flag
			Í½ÊÖ	unarmed
			ÕÈ	wand
			ÖØ½£ epee
			*/
		//ÊôÐÔ¿ªÊ¼
		Ogre::String					m_longHandle;
		Ogre::String					m_falchion;
		Ogre::String					m_gavel;
		Ogre::String					m_bow;
		Ogre::String					m_gun;
		Ogre::String					m_sword;
		Ogre::String					m_flag;
		Ogre::String					m_unarmed;
		Ogre::String					m_wand;
		Ogre::String					m_epee;
		//ÊôÐÔ½áÊø
		Ogre::String					m_currentWeaponType;
	private:
	};
}
#endif // OGAASWeaponAnimSequenceNode_h__
