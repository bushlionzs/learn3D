#include "OgreHeader.h"
#include "OGNavigateAStarSolverImp.h"
#include "OGNavigateAStarNodeImp.h"
#include "OGNavigateSpaceImp.h"
#include <assert.h>
using namespace std;

namespace Orphigine 
{

NeAStarSolverImp::NeAStarSolverImp()
{
	m_openList.clear();
	m_closeList.clear();
	m_currentNode		= NULL;
	m_startNode			= NULL;
	m_endNode			= NULL;

	m_isArriveEndPoint	= false;
	m_hasPath			= true;
}

NeAStarSolverImp::~NeAStarSolverImp()
{
	/*for (int i = 0;i < (int)m_openList.size();i ++)
	{
		delete m_openList[i];
		m_openList[i] = NULL;
	}

	for (int i = 0;i < (int)m_closeList.size();i ++)
	{
		delete m_closeList[i];
		m_closeList[i] = NULL;
	}*/

	m_openList.clear();

	m_closeList.clear();

	if (NULL != m_startNode)
	{
		delete m_startNode;
		m_startNode = NULL;
	}

	if(NULL != m_endNode)
	{
		delete m_endNode;
		m_endNode = NULL;
	}
}

void NeAStarSolverImp::addToOpenList( NeAStarNodeImp* node )
{

	if (NULL != m_currentNode)// 如果node是起始节点，则此时m_currentNode为空指针 [11/29/2007 姜威]
	{
		float tmpF = 0;
		float tmpG = 0;
		float tmpH = 0;

		tmpG = computeG(node);	
		node->setG(tmpG);
		tmpH = computeH(node);
		node->setH(tmpH);
		tmpF = computeF(tmpG,tmpH);
		node->setF(tmpF);

	}

	m_openList.push_back(node);
}

void NeAStarSolverImp::addToCloseList( NeAStarNodeImp* node )
{
	m_closeList.push_back(node);
}

void NeAStarSolverImp::setStartNode( NeAStarNodeImp* node )
{
	m_startNode = node;
}

const NePathNode* NeAStarSolverImp::getStartNode() const
{
	return m_startNode;
}

NeAStarNodeImp* NeAStarSolverImp::getStartNode()
{
	return m_startNode;
}

void NeAStarSolverImp::setEndNode( NeAStarNodeImp* node )
{
	m_endNode = node;
}

const NePathNode* NeAStarSolverImp::getEndNode() const
{
	return m_endNode;
}

NeAStarNodeImp* NeAStarSolverImp::getEndNode()
{
	return m_endNode;
}

void NeAStarSolverImp::setCurrentNode( NeAStarNodeImp* node )
{
	m_currentNode = node;

	std::vector<NeAStarNodeImp*>::iterator iter= find(m_openList.begin(),m_openList.end(),m_currentNode);// 从Open列表迁移到Close列表 [11/29/2007 姜威]
	if(m_openList.end() != iter)
	{
		m_openList.erase(iter);
		addToCloseList(m_currentNode);
	}
}

NeAStarNodeImp* NeAStarSolverImp::getCurrentNode() const
{
	return m_currentNode;
}


bool NeAStarSolverImp::performSolve()
{
	assert(NULL != m_startNode && "Start点不能为空");
	assert(NULL != m_endNode && "End点不能为空");

	if(m_isStartToEndDirect)
	{
		m_isArriveEndPoint = true;
		m_endNode->setParentNode(m_startNode);
	}

	while (!m_isArriveEndPoint && m_hasPath) 
	{
		if(m_openList.empty())
			return false;
		auto iter = m_openList.begin();

		NeAStarNodeImp* tmpMinNode = *m_openList.begin();
		if (iter != m_openList.end())
		{
			for (;++ iter != m_openList.end();)
			{
				if(tmpMinNode->getF() > (*iter)->getF())
					tmpMinNode = (*iter);
			}
		}
	
		setCurrentNode(tmpMinNode);

		bool canSenEndPoint = canSeeEndPoint();
		if(canSenEndPoint)
		{
			m_isArriveEndPoint = true;
			m_endNode->setParentNode(m_currentNode);
		}
		if(!m_isArriveEndPoint)
			searchChildNode();// 搜索且处理子节点
	}

	return m_hasPath;
}
 
void NeAStarSolverImp::searchChildNode()
{
	const NeVisibilityPoints* tmpCurrentVP = m_currentNode/*->getVisibilityPoint()*/;
	for (int i = 0;i < (int)tmpCurrentVP->m_visibilityPointsList.size();i ++)
	{
		const NeVisibilityPoints* tmpTargetPoint = tmpCurrentVP->m_visibilityPointsList[i];

		NeAStarNodeImp* tmpNodeInOpenList = findInOpenList(tmpTargetPoint);
		NeAStarNodeImp* tmpNodeInCloseList = findInCloseList(tmpTargetPoint);

		if (NULL == tmpNodeInOpenList && NULL == tmpNodeInCloseList)
		{
			//NeAStarNodeImp* tmpChildNode = new NeAStarNodeImp(/*tmpTargetPoint*/);
			NeAStarNodeImp* tmpChildNode = (NeAStarNodeImp*)tmpTargetPoint;
			tmpChildNode->reset();

			tmpChildNode->setParentNode(m_currentNode);
			addToOpenList(/*tmpChildNode*/tmpChildNode);
		}

		if (NULL != tmpNodeInOpenList)// 如果子节点在Open列表中，则判断从当前节点到此节点的g值是否更小，如果更小则刷新此节点的g,h,f值和更新其父节点为当前节点 
		{
			float tmpG = computeG(tmpNodeInOpenList);

			if (tmpG < tmpNodeInOpenList->getG())
			{
				tmpNodeInOpenList->setG(tmpG);
				float tmpH = tmpNodeInOpenList->getH();
				float tmpF = computeF(tmpG,tmpH);
				tmpNodeInOpenList->setF(tmpF);

				tmpNodeInOpenList->setParentNode(m_currentNode);
			}
		}
	}
}

NeAStarNodeImp* NeAStarSolverImp::findInOpenList( const NeVisibilityPoints* vp )
{
	auto iter = std::find(m_openList.begin(),m_openList.end(),vp);
	if (m_openList.end() != iter)
		return *iter;

	return NULL;
	/*vector<NeAStarNodeImp*>::iterator iter = m_openList.begin();
	for (;iter != m_openList.end();iter ++)
	{
		if((*iter)->getVisibilityPoint() == vp)
			return (*iter);
	}
	return 0;*/
}

NeAStarNodeImp* NeAStarSolverImp::findInCloseList( const NeVisibilityPoints* vp )
{
	std::vector<NeAStarNodeImp*>::iterator iter = std::find(m_closeList.begin(),m_closeList.end(),vp);
	if(m_closeList.end() != iter)
		return *iter;

	return NULL;
	/*std::vector<NeAStarNodeImp*>::iterator iter = m_closeList.begin();
	for (;iter != m_closeList.end();iter ++)
	{
		if((*iter)->getVisibilityPoint() == vp)
			return (*iter);
	}
	return 0;*/
}

float NeAStarSolverImp::computeG( NeAStarNodeImp* childNode )
{
	float tmpG = 0.0f;

	NeVector3 tmpVec = m_currentNode->getPosition() - childNode->getPosition();
	tmpG = Vectormath::Aos::length(tmpVec) + m_currentNode->getG();	

	return tmpG;
}

float NeAStarSolverImp::computeH( NeAStarNodeImp* childNode )
{
	NeVector3 tmpVec = m_endNode->getPosition() - childNode->getPosition();
	return Vectormath::Aos::length(tmpVec);
}

float NeAStarSolverImp::computeF( float g,float h )
{
	return g + h;
}

void NeAStarSolverImp::flush( const NeVector3& startPoint,const NeVector3& endPoint )
{

	/*for (int i = 0;i < (int)m_openList.size();i ++)
	{
		delete m_openList[i];
		m_openList[i] = NULL;
	}

	for (int i = 0;i < (int)m_closeList.size();i ++)
	{
		delete m_closeList[i];
		m_closeList[i] = NULL;
	}*/

	if(NULL != m_startNode)
	{
		delete m_startNode;
		m_startNode = NULL;
	}

	if(NULL != m_endNode)
	{
		delete m_endNode;
		m_endNode = NULL;
	}

	m_openList.clear();
	m_closeList.clear();
	m_currentNode		= NULL;
	m_startNode			= NULL;
	m_endNode			= NULL;

	m_isArriveEndPoint	= false;
	m_hasPath			= true;


	/*NeVisibilityPoints* tmpStartVP = new NeVisibilityPoints;
	tmpStartVP->m_position = startPoint;

	NeVisibilityPoints* tmpEndVP = new NeVisibilityPoints;
	tmpEndVP->m_position = endPoint;*/

	NeAStarNodeImp* tmpStartNode = new NeAStarNodeImp(/*tmpStartVP*/);
	tmpStartNode->m_position = startPoint;
	setStartNode(tmpStartNode);

	NeAStarNodeImp* tmpEndNode = new NeAStarNodeImp(/*tmpEndVP*/);
	tmpEndNode->m_position = endPoint;
	setEndNode(tmpEndNode);

	addToOpenList(tmpStartNode);

	m_isStartToEndDirect = isStartPointToEndPointDirect();

	if(m_isStartToEndDirect)
	{

		return;
	}

	for (int i = 0;i < m_space->getNumRegions();i++)
	{
		NeRegion* tmpTargetRegion = m_space->getRegionByIndex(i);

		NeSpaceImp* tmpSpace = (NeSpaceImp*)m_space;

		tmpSpace->linkPointsOfVisibilityComplete(*tmpStartNode,*tmpTargetRegion);

		tmpSpace->linkPointsOfVisibilityComplete(*tmpEndNode,*tmpTargetRegion);
	}
}

/*
 *	检测当前点是否在终点的可视点列表中
 */
bool NeAStarSolverImp::canSeeEndPoint()
{
	const NeVisibilityPoints* tmpVP = m_endNode/*->getVisibilityPoint()*/;

	std::vector<const NeVisibilityPoints*>::const_iterator iter = find(
		tmpVP->m_visibilityPointsList.begin(),tmpVP->m_visibilityPointsList.end(),m_currentNode/*->getVisibilityPoint()*/);

	if(tmpVP->m_visibilityPointsList.end() != iter)
		return true;

	return false;
}

bool NeAStarSolverImp::isStartPointToEndPointDirect()
{
	const NeVisibilityPoints* tmpStartVP = m_startNode/*->getVisibilityPoint()*/;
	const NeVisibilityPoints* tmpEndVP = m_endNode/*->getVisibilityPoint()*/;

	NeSpaceImp* tmpSpace = (NeSpaceImp*)m_space;
	bool isCross = tmpSpace->checkCrossForPrecomputePOV(tmpStartVP,tmpEndVP);
	if(!isCross)
		return true;

	return false;
}

void NeAStarSolverImp::setSpace( NeSpace* space )
{
	m_space = space;
}

void NeAStarSolverImp::smoothPath()
{
	/*NeAStarNodeImp* parentPathNode = getEndNode();

	while (NULL != parentPathNode)
	{
		NeVector3 pathNodePos = parentPathNode->getPosition() +
			parentPathNode->m_vertexNormal * 1.6f;

		parentPathNode->setPosition(pathNodePos);

		parentPathNode = parentPathNode->getParentNode();
	}*/
}

} // namespace Orphigine