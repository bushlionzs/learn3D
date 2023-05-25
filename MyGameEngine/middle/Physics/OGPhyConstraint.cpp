#include "OgreHeader.h"
#include "OGPhyConstraint.h"

#include "btBulletDynamicsCommon.h"

namespace Orphigine
{


	PhyConstraint::PhyConstraint()
		: m_constraint(NULL)
	{
		
	}

	PhyConstraint::~PhyConstraint()
	{
		delete m_constraint;
		m_constraint = NULL;
	}

	btTypedConstraint* PhyConstraint::getBtConstraint() const
	{
		return m_constraint;
	}

	void PhyConstraint::setBtConstraint( btTypedConstraint* val )
	{
		m_constraint = val;
	}
}