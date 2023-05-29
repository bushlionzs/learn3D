#include "OgreHeader.h"
#include "OGPhySoftBody.h"
#include "BulletSoftBody/btSoftBody.h"
#include "OgreAxisAlignedBox.h"

namespace Orphigine
{


	PhySoftBody::PhySoftBody()
		: m_softBody(NULL)
	{

	}

	PhySoftBody::~PhySoftBody()
	{
		delete m_softBody;
		m_softBody = NULL;
	}

	btSoftBody* PhySoftBody::getBtSoftBody() const
	{
		return m_softBody;
	}

	void PhySoftBody::setBtSoftBody( btSoftBody* val )
	{
		m_softBody = val;
	}

	const String& PhySoftBody::getMovableType( void ) const
	{
		static String movableType = "PhySoftBody";
		return movableType;
	}

	const Ogre::AxisAlignedBox& PhySoftBody::getBoundingBox( void ) const
	{
		return m_boundingBox;
	}

	Ogre::Real PhySoftBody::getBoundingRadius( void ) const
	{
		return 0.0f;
	}

	void PhySoftBody::_updateRenderQueue( Ogre::RenderQueue* queue )
	{
		
	}

}