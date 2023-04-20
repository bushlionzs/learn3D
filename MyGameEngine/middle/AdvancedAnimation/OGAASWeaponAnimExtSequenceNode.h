#ifndef OGAASWeaponAnimExtSequenceNode_h__
#define OGAASWeaponAnimExtSequenceNode_h__

#include "OGAASWeaponAnimSequenceNode.h"

#include "OgreAnimationState.h"
#include "OGAASNodeFactory.h"

namespace Orphigine
{
	class AdvancedAnimationSystem;

	class AASWeaponAnimExtSequenceNode : public AASWeaponAnimSequenceNode
	{
	public:
		AASWeaponAnimExtSequenceNode(AdvancedAnimationSystem* system,unsigned short handle);
		virtual ~AASWeaponAnimExtSequenceNode();

		virtual void	writeToBinary(AdvancedAnimationSystemSerializerImpl* serializer,
			AdvancedAnimationSystem* system);

		virtual void	readFromBinary(AdvancedAnimationSystemSerializerImpl* serializer,Ogre::DataStreamPtr& stream,
			AdvancedAnimationSystem* system);

		virtual size_t	calcSize(AdvancedAnimationSystemSerializerImpl* serializer);

		virtual void	copyParameters(AASNode* dest);		

		//---------------------------
		const Ogre::String&					getSpear() const { return m_Spear;}
		void                            setSpear(const Ogre::String& val) { m_Spear = val;}

		const Ogre::String&					getToken() const { return m_Token;}
		void                            setToken(const Ogre::String& val) { m_Token = val;}

		const Ogre::String&					getCrossbow() const { return m_Crossbow;}
		void                            setCrossbow(const Ogre::String& val) { m_Crossbow = val;}

		const Ogre::String&					getFiregun() const { return m_Firegun;}
		void                            setFiregun(const Ogre::String& val) { m_Firegun = val;}

		const Ogre::String&					getCross() const { return m_Cross;}
		void                            setCross(const Ogre::String& val) { m_Cross = val;}

		const Ogre::String&					getFan() const { return m_Fan;}
		void                            setFan(const Ogre::String& val) { m_Fan = val;}
		//---------------------------

		//virtual	void					_refreshAnimation();
	
		//-----------------------------------
		class CmdSpear : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};
		class CmdToken : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};
		class CmdCrossbow : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};
		class CmdFiregun : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};
		class CmdCross : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};
		class CmdFan : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		//------------------------------------
		static	CmdSpear				ms_spearCmd;
		static	CmdToken				ms_tokenCmd;
		static	CmdCrossbow				ms_crossbowCmd;
		static	CmdFiregun				ms_firegunCmd;
		static	CmdCross				ms_crossCmd;
		static	CmdFan					ms_fanCmd;
		//------------------------------------
	protected:
		virtual String		_getAnimationByWeaponTypeName(const String& weaponType);
	protected:

		/*
		³¤Ã¬	Áî	       åó	  »ðï¥	    Ê®×Ö¼Ü	    ·«	
		spear   token   Crossbow  Firegun   Cross       Fan
		*/
		//ÊôÐÔ¿ªÊ¼
		Ogre::String					m_Spear;
		Ogre::String					m_Token;
		Ogre::String					m_Crossbow;
		Ogre::String					m_Firegun;
		Ogre::String					m_Cross;
		Ogre::String					m_Fan;		
	private:
	};

	class AASWeaponAnimExtSequenceNodeFactory : public AASNodeFactory
	{
	public:
		virtual String getName() const
		{
			return "WeaponAnimExtSequence";
		}

		virtual AASNode* createNode(AdvancedAnimationSystem* system,unsigned short handle)
		{
			AASNode* tmpNode = OGRE_NEW AASWeaponAnimExtSequenceNode(system,handle);
			m_nodes.push_back(tmpNode);

			return tmpNode;
		}
	protected:
	private:
	};

}
#endif // OGAASWeaponAnimExtSequenceNode_h__
