#ifndef OGAASPort_h__
#define OGAASPort_h__

#include "OGAdvancedAnimationSystem.h"


namespace Orphigine
{
	class AASNode;

	class _OrphigineExport AASPort
	{
	public:
		AASPort(const String& name ,unsigned int handle);
		virtual ~AASPort();

		AASNode*		getParentNode() const;
		void			setParentNode(AASNode* val);

		AASNode*		getConnectedNode() const;
		void			setConnectedNode(AASNode* val);

		String			getName() const;
		void			setName(const String& val);

		unsigned int	getHandle() const;
		void			setHandle(unsigned int val);

		Real			getTargetWeight() const;
		void			setTargetWeight(Real val);

		inline Real		getBlendWeight() const
		{
			return m_blendWeight;
		}
		inline void		setBlendWeight(Real val)
		{
			m_blendWeight = val;
		}

		TraverseBranchMaskCollection*	getBranchBonesWeightCollection() const;
		void							setBranchBonesWeightCollection(TraverseBranchMaskCollection* val);

		TraverseBranchMaskCollection* 	createBranchBonesWeightCollection();
		void							destroyBranchBonesWeightCollection();

	protected:
		AASNode*		m_parentNode;
		AASNode*		m_connectedNode;
		String			m_name;
		unsigned int	m_handle;
		Real			m_targetWeight;
		Real			m_blendWeight;
		Real			m_maskedBonesWeight;
		Real			m_nonmaskedBonesWeight;
		TraverseBranchMaskCollection*		m_branchBonesWeightCollection;

	private:
	};
}
#endif // OGAASPort_h__