#ifndef NePathNode_h__
#define NePathNode_h__

#include "OGNavigateUtil.h"
#include "OGNavigateRegion.h"

namespace Orphigine 
{

enum NePathNodeType
{
	NE_PNT_ASTAR = 0
};

class NePathNode : public NeVisibilityPoints
{
public:
	//************************************
	// Brief:	  得到位置信息
	// Method:    getPosition
	// FullName:  NePathNode::getPosition
	// Access:    virtual public 
	// Returns:   const NeVector3
	//************************************
	virtual  NeVector3					getPosition() const = 0;

	virtual void						setPosition(const NeVector3& position) = 0;

	virtual NeVector3					getVertexNormal() const = 0;

	virtual void						setVertexNormal(const NeVector3& normal) = 0;

	//************************************
	// Brief:	  得到父节点
	// Method:    getParentNode
	// FullName:  NePathNode::getParentNode
	// Access:    virtual public 
	// Returns:   const NePathNode*
	//************************************
	virtual const NePathNode*			getParentNode() const = 0;
	//************************************
	// Brief:	  设置父节点
	// Method:    setParentNode
	// FullName:  NePathNode::setParentNode
	// Access:    virtual public 
	// Returns:   void
	// Parameter: NePathNode * node
	//************************************
	virtual void						setParentNode(NePathNode* node) = 0;

	//************************************
	// Brief:	  得到下一个节点
	// Method:    getNextNode
	// FullName:  NePathNode::getNextNode
	// Access:    virtual public 
	// Returns:   const NePathNode*
	//************************************
	virtual const NePathNode*			getNextNode() const = 0;
	//************************************
	// Brief:	  设置下一个
	// Method:    setNextNode
	// FullName:  NePathNode::setNextNode
	// Access:    virtual public 
	// Returns:   void
	// Parameter: NePathNode * node
	//************************************
	virtual void						setNextNode(NePathNode* node) = 0;

	//************************************
	// Brief:	  得到类型
	// Method:    getType
	// FullName:  NePathNode::getType
	// Access:    virtual public 
	// Returns:   NePathNodeType
	//************************************
	virtual NePathNodeType				getType() const = 0;
protected:
	NePathNode(){}
	virtual ~NePathNode(){}
private:
};

} // namespace Orphigine

#endif // NePathNode_h__