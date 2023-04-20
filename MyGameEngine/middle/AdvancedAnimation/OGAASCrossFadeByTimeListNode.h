#ifndef OGAASCrossFadeByTimeListNode_h__
#define OGAASCrossFadeByTimeListNode_h__

#include "OGAASCrossFadeNode.h"

namespace Orphigine
{
	class AASCrossFadeByTimeListNodeSerializerImpl;

	class AASCrossFadeByTimeListNode : public AASCrossFadeNode
	{
	public:
		AASCrossFadeByTimeListNode(const String& typeName,AdvancedAnimationSystem* system,unsigned short handle);

		virtual ~AASCrossFadeByTimeListNode();

		virtual bool	initParameter(const String& typeName);

		virtual void	copyParameters(AASNode* dest);

		virtual void	writeToBinary(AdvancedAnimationSystemSerializerImpl* serializer,
			AdvancedAnimationSystem* system);

		virtual void	readFromBinary(AdvancedAnimationSystemSerializerImpl* serializer,Ogre::DataStreamPtr& stream,
			AdvancedAnimationSystem* system);

		virtual size_t	calcSize(AdvancedAnimationSystemSerializerImpl* serializer);

		class CmdBlendTime : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		Real					getBlendTime() const;
		void						setBlendTime(const Real val);

		Real					getTimeLeft() const;
		void						setTimeLeft(const Real val);

		virtual void tickAnimation(const float elapsedTime, ReachedAnimSequenceNodeCollection& reachedAnimSequenceNodeCollection);

		virtual void				setActiveChild(unsigned short childIndex,Real blendTime = 0.25f);

		virtual void				initAnim(AASNode* parentNode);

		static CmdBlendTime			ms_blendTimeCmd;

		static	void				_initSerializers();
		static  void				_deinitSerializers();

		typedef	std::map<String,AASCrossFadeByTimeListNodeSerializerImpl*>	AASCrossFadeByTimeListNodeSerializerMap;
		static AASCrossFadeByTimeListNodeSerializerMap ms_serializersMap;
	protected:
		virtual void				setActiveChild(AASPort* activePort,Real	blendTime = 0.25f);

	protected:
		int							m_activeChildIndex;	
		//属性开始
		Real						m_blendTime;
		//属性结束
		Real						m_timeLeft;
	private:
	};


	class AASCrossFadeByTimeListNodeSerializerImpl : public AASSerializerImplBase
	{
	public:
		virtual void	readFromBinary(AdvancedAnimationSystemSerializerImpl* serializer,Ogre::DataStreamPtr& stream,
			AdvancedAnimationSystem* system,AASCrossFadeByTimeListNode* node);
	};
}

#endif // OGAASCrossFadeByTimeListNode_h__
