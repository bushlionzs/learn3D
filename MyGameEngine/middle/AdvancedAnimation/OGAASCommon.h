#ifndef OGAASCommon_h__
#define OGAASCommon_h__


namespace Orphigine
{
	class AASNode;
	class AASAnimation;
	class AASAnimSequenceNode;
	struct AnimSeqSynchGroup;

	typedef std::vector<AASNode* >							AASNodeVector;
	typedef std::vector<AASAnimation* >					AASAnimationVector;	
	typedef std::vector<AnimSeqSynchGroup >		AnimSynchGropVector;
	typedef std::vector<AASAnimSequenceNode* >	AASAnimSequNodeVector;	

	typedef std::map< String, int >					AnimationIndexMap;

	typedef std::unordered_map< Ogre::String, AASNode* >		NodeNameMap;
}
#endif // OGAASCommon_h__