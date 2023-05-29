#ifndef NeSolver_h__
#define NeSolver_h__

namespace Orphigine 
{

class NePathNode;
class NeSpace;

class NeSolver
{
public:
	//************************************
	// Brief:	  得到起始节点
	// Method:    getStarNode
	// FullName:  NeSolver::getStarNode
	// Access:    virtual public 
	// Returns:   const NePathNode*
	//************************************
	virtual const NePathNode*					getStartNode() const = 0;

	//************************************
	// Brief:	  得到终止节点
	// Method:    getEndNode
	// FullName:  NeSolver::getEndNode
	// Access:    virtual public 
	// Returns:   const NePathNode*
	//************************************
	virtual const NePathNode*					getEndNode() const = 0;

	//************************************
	// Brief:	  主解算器
	// Method:    performSolve
	// FullName:  NeSolver::performSolve
	// Access:    virtual public 
	// Returns:   bool
	//************************************
	virtual	 bool								performSolve() = 0;

	//************************************
	// Brief:	  设置空间
	// Method:    setSpace
	// FullName:  NeSolver::setSpace
	// Access:    virtual public 
	// Returns:   void
	// Parameter: NeSpace * space
	//************************************
	virtual void								setSpace(NeSpace* space) = 0;
protected:
	NeSolver(){}
	virtual ~NeSolver(){}
private:
};

} // namespace Orphigine

#endif // NeSolver_h__