#ifndef NeAStarSolver_h__
#define NeAStarSolver_h__

#include "OGNavigateSolver.h"
#include "OGNavigateAStarNode.h"

namespace Orphigine 
{

class NeAStarSolver : public NeSolver
{
public:

	//************************************
	// Brief:	  解算器开始之前进行刷新
	// Method:    flush
	// FullName:  NeAStarSolver::flush
	// Access:    virtual public 
	// Returns:   void
	// Parameter: const NeVector3 & startPoint
	// Parameter: const NeVector3 & endPoint
	//************************************
	virtual void								flush(const NeVector3& startPoint,const NeVector3& endPoint) = 0;

	virtual void								smoothPath() = 0;
protected:
	NeAStarSolver() {}
	virtual ~NeAStarSolver() {}
private:
};
} // namespace Orphigine

#endif // NeAStarSolver_h__