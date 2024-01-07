#ifndef OGAASMask_h__
#define OGAASMask_h__


namespace Orphigine
{
	class AdvancedAnimationSystem;

	class AASMask
	{
	public:
		AASMask(AdvancedAnimationSystem* system);
		virtual ~AASMask();

		String					getBonesNameVec() const;
		void							setBonesNameVec(String val);

		unsigned short					getBonesHandle(unsigned short index) const;
		
		std::vector<unsigned short>&	getBonesHandleVec();

		unsigned short					getNumBonesHandle() const;

	protected:
		std::vector<unsigned short> m_maskedBoneHandles;
		String						m_bonesNameVec;
		AdvancedAnimationSystem*	m_parent;
	private:
	};
}
#endif // OGAASMask_h__