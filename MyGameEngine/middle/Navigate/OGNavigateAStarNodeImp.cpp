#include "OgreHeader.h"
#include "OGNavigateAStarNodeImp.h"
#include <assert.h>

namespace Orphigine 
{

NeAStarNodeImp::NeAStarNodeImp(/*const NeVisibilityPoints* vp*/)
: m_type(NE_PNT_ASTAR)
{
	m_f = 0;
	m_g = 0;
	m_h = 0; 
	//m_vp = /*vp*/NULL;
	m_parentNode = NULL;
	m_nextNode = NULL;
}

NeAStarNodeImp::~NeAStarNodeImp()
{

}

const NePathNode* NeAStarNodeImp::getParentNode() const
{
	return m_parentNode;
}

NeAStarNodeImp* NeAStarNodeImp::getParentNode()
{
	return (NeAStarNodeImp*)m_parentNode;	
}

void NeAStarNodeImp::setParentNode( NePathNode* val )
{
	assert(m_type == val->getType() && "设置的父节点类型与当前节点类型不一致");
	m_parentNode = val;
}

const NePathNode* NeAStarNodeImp::getNextNode() const
{
	return m_nextNode;
}

NeAStarNodeImp* NeAStarNodeImp::getNextNode()
{
	return (NeAStarNodeImp*)m_nextNode;
}

void NeAStarNodeImp::setNextNode( NePathNode* val )
{
	assert(m_type == val->getType() && "设置的子节点类型与当前节点类型不一致");
	m_nextNode = val;
}


float NeAStarNodeImp::getG() const
{
	return m_g;
}

void NeAStarNodeImp::setG( float val )
{
	m_g = val;
}

float NeAStarNodeImp::getH() const
{
	return m_h;
}

void NeAStarNodeImp::setH( float val )
{
	m_h = val;
}

float NeAStarNodeImp::getF() const
{
	return m_f;
}

void NeAStarNodeImp::setF( float val )
{
	m_f = val;
}

NeVector3 NeAStarNodeImp::getPosition() const
{
	return m_position;
}

void NeAStarNodeImp::setPosition( const NeVector3& position )
{
	m_position = position;
}

//const NeVisibilityPoints* NeAStarNodeImp::getVisibilityPoint() const
//{
//	return m_vp;
//}

NePathNodeType NeAStarNodeImp::getType() const
{
	return m_type;
}

void NeAStarNodeImp::reset()
{
	m_f = 0;
	m_g = 0;
	m_h = 0; 
	//m_vp = /*vp*/NULL;
	m_parentNode = NULL;
	m_nextNode = NULL;
}

NeVector3 NeAStarNodeImp::getVertexNormal() const
{
	return m_vertexNormal;
}

void NeAStarNodeImp::setVertexNormal( const NeVector3& normal )
{
	m_vertexNormal = normal;
}
} // namespace Orphigine