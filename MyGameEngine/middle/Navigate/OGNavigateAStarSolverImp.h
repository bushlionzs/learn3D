#ifndef NeAStarSolverImp_h__
#define NeAStarSolverImp_h__

#include <vector>
#include "algorithm"
#include "OGNavigateAStarSolver.h"
using namespace std;


namespace Orphigine 
{

class	NeAStarNode;
class	NeAStarNodeImp;
class	NeVisibilityPoints;
class   NeSpace;

class NeAStarSolverImp : public NeAStarSolver
{
public:
	NeAStarSolverImp();
	virtual ~NeAStarSolverImp();

	virtual const NePathNode*			getStartNode() const;

	virtual const NePathNode*			getEndNode() const;

	virtual void						setSpace(NeSpace* space);

	virtual void						flush(const NeVector3& startPoint,const NeVector3& endPoint);

	virtual bool						performSolve();

	virtual void						smoothPath();

protected:
	NeAStarNodeImp*						getStartNode();

	void								setStartNode(NeAStarNodeImp* node);

	NeAStarNodeImp*						getEndNode();

	void								setEndNode(NeAStarNodeImp* node);

	// 设置当前节点，以及将当前节点从open列表移到close列表 [11/29/2007 姜威]
	void								setCurrentNode(NeAStarNodeImp* node); 

	NeAStarNodeImp*						getCurrentNode() const;

	void								addToOpenList(NeAStarNodeImp* node);

	void								addToCloseList(NeAStarNodeImp* node);

	virtual float						computeG(NeAStarNodeImp* childNode);

	virtual float						computeH(NeAStarNodeImp* childNode);

	virtual float						computeF(float g,float h);

	virtual void						searchChildNode();

	NeAStarNodeImp*						findInOpenList(const NeVisibilityPoints* vp);

	NeAStarNodeImp*						findInCloseList(const NeVisibilityPoints* vp);

	bool								canSeeEndPoint();

	bool								isStartPointToEndPointDirect();
protected:

	std::vector<NeAStarNodeImp*>				m_openList;
	std::vector<NeAStarNodeImp*>				m_closeList;
	NeAStarNodeImp*						m_startNode;
	NeAStarNodeImp*						m_endNode;
	NeAStarNodeImp*						m_currentNode;

	bool								m_isArriveEndPoint;
	bool								m_hasPath;
	bool								m_isStartToEndDirect;
	NeSpace*							m_space;
private:
};

} // namespace Orphigine

#endif // NeAStarSolverImp_h__
