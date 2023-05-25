#ifndef OGPhyConstraint_h__
#define OGPhyConstraint_h__

class btTypedConstraint;

namespace Orphigine
{
	class PhyConstraint
	{
	public:
		PhyConstraint();
		virtual ~PhyConstraint();

		btTypedConstraint*			getBtConstraint() const;
		void						setBtConstraint(btTypedConstraint* val);

	protected:
		btTypedConstraint*			m_constraint;

	private:
	};
}
#endif // OGPhyConstraint_h__
