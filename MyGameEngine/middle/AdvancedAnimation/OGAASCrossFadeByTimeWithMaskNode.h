#ifndef OGAASCrossFadeByTimeWithMaskNode_h__
#define OGAASCrossFadeByTimeWithMaskNode_h__

#include "OGAASCrossFadeByTimeNode.h"
#include "OGAASMask.h"

namespace Orphigine
{
	class AASPort;
	class AASCrossFadeByTimeWithMaskNodeSerializerImpl;

	class AASCrossFadeByTimeWithMaskNode : public AASCrossFadeByTimeNode
	{
	protected:
		typedef std::vector<unsigned short> BoneHandles;
	public:
		AASCrossFadeByTimeWithMaskNode(const String& typeName,AdvancedAnimationSystem* system,
			unsigned short handle);

		virtual ~AASCrossFadeByTimeWithMaskNode();

		class CmdBranchBoneName : public Ogre::ParamCommand
		{
		public:
			String doGet(const void* target) const;
			void doSet(void* target, const String& val);
		};

		virtual void	writeToBinary(AdvancedAnimationSystemSerializerImpl* serializer,
			AdvancedAnimationSystem* system);

		virtual void	readFromBinary(AdvancedAnimationSystemSerializerImpl* serializer,Ogre::DataStreamPtr& stream,
			AdvancedAnimationSystem* system);

		virtual size_t	calcSize(AdvancedAnimationSystemSerializerImpl* serializer);

		virtual bool	initParameter(const String& typeName);

		virtual void	copyParameters(AASNode* dest);

		virtual void	initAnim(AASNode* parentNode);

		virtual void	tickAnimation(const float elapsedTime, ReachedAnimSequenceNodeCollection& reachedAnimSequenceNodeCollection);

		virtual void	accumulateNodeTotalWeights(unsigned int index);


		const Ogre::String&		getBonesNameVec() const;
		void						setBonesNameVec(const Ogre::String& val);
		void						setBonesNameVec(const Ogre::String& val, const BoneHandles& valList);

		unsigned short				getBonesHandle(unsigned short index) const;

		unsigned short				getNumBonesHandle() const;

		static CmdBranchBoneName	ms_branchBonesNameCmd;
		
		static void	    _initSerializers();
		static void		_deinitSerializers();

		typedef		std::map<String,AASCrossFadeByTimeWithMaskNodeSerializerImpl*>	AASCrossFadeByTimeWithMaskNodeSerializerImplMap;
		static AASCrossFadeByTimeWithMaskNodeSerializerImplMap	ms_serializersMap;
	protected:
		void						setSourcePort(AASPort* sourcePort);
		void						setTargetPort(AASPort* targetPort);
	private:
		void						_accumulateTraverseMaskCollection(AASPort* port);

		Real						_accumulateMaskPortsWeight();
	protected:
		AASPort*					m_sourcePort;
		AASPort*					m_targetPort;
		//属性开始
		Ogre::String				m_maskedBonesHandleStr;
		//属性结束
		BoneHandles m_maskedBoneHandles;

	private:
	};


	class AASCrossFadeByTimeWithMaskNodeSerializerImpl : public AASSerializerImplBase
	{
	public:
		virtual void	readFromBinary(AdvancedAnimationSystemSerializerImpl* serializer,Ogre::DataStreamPtr& stream,
			AdvancedAnimationSystem* system,AASCrossFadeByTimeWithMaskNode* node);

	};
	class AASCrossFadeByTimeWithMaskNodeSerializerImpl_v1_2 : public AASCrossFadeByTimeWithMaskNodeSerializerImpl
	{
	public:
		virtual void	readFromBinary(AdvancedAnimationSystemSerializerImpl* serializer,Ogre::DataStreamPtr& stream,
			AdvancedAnimationSystem* system,AASCrossFadeByTimeWithMaskNode* node);
	};

}
#endif // OGAASCrossFadeByTimeWithMaskNode_h__
