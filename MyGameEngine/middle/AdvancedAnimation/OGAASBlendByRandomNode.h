#ifndef OGAASBlendByRandomNode_h__
#define OGAASBlendByRandomNode_h__

#include "OGAASCrossFadeByTimeListNode.h"

#include <vector>

namespace Orphigine
{
	struct AASRandomInfo : public Ogre::StringInterface
	{
		AASRandomInfo();

		void	copyParameters(AASRandomInfo* dest) const;

		class CmdChildLoopCount : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		unsigned int				getChildLoopCount() const;
		void						setChildLoopCount(unsigned int val);

		static  CmdChildLoopCount	ms_childLoopCountCmd;

		//属性开始
		unsigned int				m_childLoopCount;
		//属性结束
	};

	class AASBlendByRandomNodeSerializerImpl : public AASSerializerImplBase
	{
	public:
		virtual void	readFromBinary(AdvancedAnimationSystemSerializerImpl* serializer,Ogre::DataStreamPtr& stream,
			AdvancedAnimationSystem* system,AASBlendByRandomNode* node);
	};
	class AASBlendByRandomNodeSerializerImpl_v1_2 : public AASBlendByRandomNodeSerializerImpl
	{
	public:
		virtual void	readFromBinary(AdvancedAnimationSystemSerializerImpl* serializer,Ogre::DataStreamPtr& stream,
			AdvancedAnimationSystem* system,AASBlendByRandomNode* node);
	};

	class AASBlendByRandomNodeSerializerImpl_v1_1 : public AASBlendByRandomNodeSerializerImpl_v1_2
	{
	public:
		virtual void	readFromBinary(AdvancedAnimationSystemSerializerImpl* serializer,Ogre::DataStreamPtr& stream,
			AdvancedAnimationSystem* system,AASBlendByRandomNode* node);
	};


	class AASPort;
	class AdvancedAnimationSystem;

	class _OrphigineExport AASBlendByRandomNode : public AASCrossFadeByTimeListNode
	{
	public:
		AASBlendByRandomNode(AdvancedAnimationSystem* system,unsigned short handle);
		virtual ~AASBlendByRandomNode();

		virtual void tickAnimation(const float elapsedTime, ReachedAnimSequenceNodeCollection& reachedAnimSequenceNodeCollection);

		virtual void	writeToBinary(AdvancedAnimationSystemSerializerImpl* serializer,
			AdvancedAnimationSystem* system);

		virtual void	readFromBinary(AdvancedAnimationSystemSerializerImpl* serializer,Ogre::DataStreamPtr& stream,
			AdvancedAnimationSystem* system);

		virtual size_t	calcSize(AdvancedAnimationSystemSerializerImpl* serializer);

		void									addRandomInfo(const AASRandomInfo& randomInfo);

		const	AASRandomInfo*					getRandomInfo(unsigned int index) const;

		AASRandomInfo*							getRandomInfo(unsigned int index);

		unsigned int							getNumRandomInfos() const;

		static	void							_initSerializers();
		static  void							_deinitSerializers();

		typedef		std::map<String,AASBlendByRandomNodeSerializerImpl*>	AASBlendByRandomNodeSerializerImplMap;
		static AASBlendByRandomNodeSerializerImplMap	ms_serializersMap;

	protected:
		virtual	void							_notifyAddPort(AASPort*	port);

		virtual void							_notifyDisconnectPort(AASPort* port);

		virtual void							copyParameters(AASNode* dest);

		void									playNextAnimation(Real deltaSeconds,Real timeLeft,Real blendTime = 0.25f,Real startTime = 0.0f);

		void									decidingNextChildPort();

		virtual	void							_onBecomeActive();

	protected:
		int										m_nextPortIndex;
		std::vector<AASRandomInfo>				m_randomInfos;
		unsigned int							m_currentAnimLoopCountDirty;
		bool									m_randomDirty;

		static	String							ms_currentVersion;
	private:
	};
}
#endif // OGAASBlendByRandomNode_h__