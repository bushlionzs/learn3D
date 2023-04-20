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
	// Brief:	  �õ�ʵ��·��ֵ
	// Method:    getG
	// FullName:  NeAStarNode::getG
	// Access:    virtual public 
	// Returns:   float
	//************************************
	virtual float								getG() const = 0;

	//************************************
	// Brief:	  �õ�����ʽ·�̹���ֵ
	// Method:    getH
	// FullName:  NeAStarNode::getH
	// Access:    virtual public 
	// Returns:   float
	//************************************
	virtual float								getH() const = 0;

    //************************************
    // Brief:	  �õ�ʵ��·��ֵ������ʽ·�̹���ֵ֮��
    // Method:    getF
    // FullName:  NeAStarNode::getF
    // Access:    virtual public 
    // Returns:   float
    //************************************
    virtual	float								getF() const = 0;

	//************************************
	// Brief:	  �õ��˽ڵ�����Ŀ��ӵ����
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