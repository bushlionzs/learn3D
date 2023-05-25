#include "OgreHeader.h"
#include "OGPhyShape.h"
#include "OGPhyCollection.h"
#include "OGPhyCollectionSerializer.h"

#include "btBulletCollisionCommon.h"

namespace Orphigine
{


	PhyShape::PhyShape(const String& type)
		: m_type(type),m_shape(NULL)
	{

	}

	PhyShape::~PhyShape()
	{
		delete m_shape;
		m_shape = NULL;
	}

	btCollisionShape* PhyShape::getBtShape() const
	{
		return m_shape;
	}

	bool PhyShape::_initBaseAttribute( const String& type )
	{
		if (createParamDictionary(type + "Dict"))
		{
			Ogre::ParamDictionary* tmpDict = getParamDictionary();

			return true;
		}

		return false;
	}

	const String& PhyShape::getType() const
	{
		return m_type;
	}

	void PhyShape::setType( const String& val )
	{
		m_type = val;
	}

	size_t PhyShape::calcSize()
	{
		return m_type.length() + 1;
	}

	void PhyShape::writeToBinary( PhyCollectionSerializer* serializer, PhyCollection* system )
	{
		
	}

	void PhyShape::readFromBinary( PhyCollectionSerializer* serializer,Ogre::DataStreamPtr& stream, PhyCollection* system )
	{
		m_type = serializer->readString(stream);
	}
}