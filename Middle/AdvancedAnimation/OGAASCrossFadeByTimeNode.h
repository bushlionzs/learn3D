#ifndef OGAASCrossFadeByTimeNode_h__
#define OGAASCrossFadeByTimeNode_h__

#include "OGAASCrossFadeNode.h"

namespace Orphigine
{
	class AASCrossFadeByTimeNodeSerializerImpl;

	class AASCrossFadeByTimeNode : public AASCrossFadeNode
	{
	public:
		virtual ~AASCrossFadeByTimeNode();

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

		virtual void				tickAnimation(const float elapsedTime, ReachedAnimSequenceNodeCollection& reachedAnimSequenceNodeCollection);

		virtual void				initAnim(AASNode* parentNode);

		void						setBlendTarget(Real blendTarget,Real blendTime);

		static CmdBlendTime			ms_blendTimeCmd;

		static void					_initSerializers();
		static void					_deinitSerializers();

		typedef	std::map<String,AASCrossFadeByTimeNodeSerializerImpl*>	AASCrossFadeByTimeNodeSerializerMap;
		static AASCrossFadeByTimeNodeSerializerMap ms_serializersMap;
	protected:
		AASCrossFadeByTimeNode(const String& typeName,AdvancedAnimationSystem* system,unsigned short handle);

	protected:	
		//属性开始
		Real						m_blendTime;
		//属性结束
		Real						m_timeLeft;
		Real						m_child2WeightTarget;
	private:
	};

	class AASCrossFadeByTimeNodeSerializerImpl : public AASSerializerImplBase
	{
	public:
		virtual void	readFromBinary(AdvancedAnimationSystemSerializerImpl* serializer,Ogre::DataStreamPtr& stream,
			AdvancedAnimationSystem* system,AASCrossFadeByTimeNode* node);
	};
}
#endif // OGAASCrossFadeByTimeNode_h__
