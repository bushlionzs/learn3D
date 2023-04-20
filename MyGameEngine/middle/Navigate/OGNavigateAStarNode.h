#ifndef NeAStarNode_h__
#define NeAStarNode_h__

#include "OGNavigatePathNode.h"
#include "OGNavigateRegion.h"

namespace Orphigine 
{

class NeAStarNode : public NePathNode
{
public:
	//************************************
	// Brief:	  得到实际路程值
	// Method:    getG
	// FullName:  NeAStarNode::getG
	// Access:    virtual public 
	// Returns:   float
	//************************************
	virtual float								getG() const = 0;

	//************************************
	// Brief:	  得到启发式路程估算值
	// Method:    getH
	// FullName:  NeAStarNode::getH
	// Access:    virtual public 
	// Returns:   float
	//************************************
	virtual float								getH() const = 0;

    //************************************
    // Brief:	  得到实际路程值加启发式路程估算值之和
    // Method:    getF
    // FullName:  NeAStarNode::getF
    // Access:    virtual public 
    // Returns:   float
    //************************************
    virtual	float								getF() const = 0;

	//************************************
	// Brief:	  得到此节点包裹的可视点对象
	// Method:    getVisibilityPoint
	// FullName:  NeAStarNode::getVisibilityPoint
	// Access:    virtual public 
	// Returns:   const NeVisibilityPoints*
	//************************************
	//virtual const NeVisibilityPoints*			getVisibilityPoint() const = 0;
protected:
	NeAStarNode(){}
	virtual ~NeAStarNode(){}
private:
};
} // namespace Orphigine
#endif // NeAStarNode_h__