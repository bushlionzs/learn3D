/********************************************************************
	created:	2008/04/08
	created:	8:4:2008   16:02
	file base:	OGAASAnimSequenceNode
	file ext:	h
	author:		姜威
	email:		jiang628@hotmail.com
	purpose:	 
*********************************************************************/
#ifndef OGAASAnimSequenceNode_h__
#define OGAASAnimSequenceNode_h__

#include "OGAASNode.h"

#include "OgreAnimationState.h"

namespace Orphigine
{
	class AdvancedAnimationSystem;
	class AASPort;
	class AASAnimation;
	class AASAnimSequenceNodeSerializerImpl;

	class AASAnimSequenceNode : public AASNode
	{
	public:
		AASAnimSequenceNode(AdvancedAnimationSystem* system,unsigned short handle);
		virtual ~AASAnimSequenceNode();

		virtual bool	initParameter(const String& typeName);

		virtual void	copyParameters(AASNode* dest);

		virtual void	initAnim(AASNode* parentNode);

		class CmdRate : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		class CmdAnimationName : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		class CmdIsLooping : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		class CmdIsCauseAnimEndEvent : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};
		
		class CmdIsCauseAnimPlayEvent : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		class CmdSynchGroupName : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		virtual	void			tickAnimation(const float elapsedTime,
				ReachedAnimSequenceNodeCollection& reachedAnimSequenceNodeCollection);

		void					advanceAnimation(Real deltaSeconds);

		virtual void			writeToBinary(AdvancedAnimationSystemSerializerImpl* serializer,
				AdvancedAnimationSystem* system);

		virtual void			readFromBinary(AdvancedAnimationSystemSerializerImpl* serializer,Ogre::DataStreamPtr& stream,
				AdvancedAnimationSystem* system);


		Real				getRate() const;
		void					setRate(Real val);

		const Ogre::String&	getAnimationName() const;
		void					setAnimationName(const Ogre::String& val);

		bool					getLooping() const;
		void					setLooping(bool val);

		bool					getCauseAnimEndEvent() const;
		void					setCauseAnimEndEvent(bool val);

		bool					getCauseAnimPlayEvent() const;
		void					setCauseAnimPlayEvent(bool val);

		const Ogre::String&	getSynchGroupName() const;
		void					setSynchGroupName(const Ogre::String& val);

		int						getAnimationID() const;
		void					setAnimationID(int val);

		bool					_getRefreshAnimNameDirty() const;
		void					_setRefreshAnimNameDirty(bool val);

		virtual	void			_refreshAnimation();

		void					_disableAnimState();

		void					_enableAnimState();

		virtual void			playAnim(bool isLooping = false,Real rate = 1.0f,Real startTime = 0.0f);

		inline bool				getPlaying() const
		{
			return m_isPlaying;
		}
		inline void				setPlaying(bool val)
		{
			m_isPlaying = val;
		}

		Real					getCurrentTime() const;
		void					setCurrentTime(Real val);

		Real					getTimeLeft() const;

		virtual bool			isAnimSequenceNode();

		static	CmdRate					ms_rateCmd;
		static	CmdAnimationName		ms_animationNameCmd;
		static  CmdIsLooping			ms_isLoopingCmd;
		static  CmdIsCauseAnimEndEvent	ms_isCauseAnimEndEvent;
		static  CmdIsCauseAnimPlayEvent	ms_isCauseAnimPlayEvent;
		static  CmdSynchGroupName		ms_synchGroupNameCmd;

		static void				_initSerializers();
		static void				_deinitSerializers();

		typedef	std::map<String,AASAnimSequenceNodeSerializerImpl*>	AASAnimSequenceNodeSerializerMap;
		static AASAnimSequenceNodeSerializerMap ms_serializersMap;

	protected:
		AASAnimSequenceNode(const String& typeName,AdvancedAnimationSystem* system,unsigned short handle);

		size_t					calcSize(AdvancedAnimationSystemSerializerImpl* serializer);

		virtual	void			_onBecomeActive();

		virtual void			_onCeaseActive();
	protected:
		//属性开始
		Real								m_rate;
		Ogre::String						m_animationName;
		bool								m_isLooping;
		bool								m_isCauseAnimEndEvent;
		bool								m_isCauseAnimPlayEvent;
		Ogre::String						m_synchGroupName;
		//属性结束
		int									m_animationID;
		AASAnimation*						m_animation;
		bool								m_refreshAnimNameDirty;
		bool								m_isPlaying;
		Real								m_currentTime;

	private:
	};

	class AASAnimSequenceNodeSerializerImpl : public AASSerializerImplBase
	{
	public:
		virtual void	readFromBinary(AdvancedAnimationSystemSerializerImpl* serializer,Ogre::DataStreamPtr& stream,
			AdvancedAnimationSystem* system,AASAnimSequenceNode* node);
	};

	class AASAnimSequenceNodeSerializerImpl_v1_2 : public AASAnimSequenceNodeSerializerImpl
	{
	public:
		virtual void	readFromBinary(AdvancedAnimationSystemSerializerImpl* serializer,Ogre::DataStreamPtr& stream,
			AdvancedAnimationSystem* system,AASAnimSequenceNode* node);
	};
}
#endif // OGAASAnimSequenceNode_h__
