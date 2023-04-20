#ifndef NeAStarNodeImp_h__
#define NeAStarNodeImp_h__

#include "OGNavigateUtil.h"
#include "OGNavigateAStarNode.h"

namespace Orphigine 
{

class NeAStarNodeImp : public NeAStarNode
{
public:

	NeAStarNodeImp(/*const NeVisibilityPoints* vp*/);
	virtual ~NeAStarNodeImp();

	/*
	 *	接口实现
	 */
	virtual NeVector3						getPosition() const;

	virtual void							setPosition(const NeVector3& position);

	virtual NeVector3						getVertexNormal() const;

	virtual void							setVertexNormal(const NeVector3& normal);

	virtual const NePathNode*				getParentNode() const;

	virtual void							setParentNode(NePathNode* val);
 
	virtual const NePathNode*				getNextNode() const;

	virtual void							setNextNode(NePathNode* val);

	virtual NePathNodeType					getType() const;

	virtual float							getG() const;
	virtual void							setG(float val);

	virtual float							getH() const;
	virtual void							setH(float val);

	virtual float							getF() const;
	virtual void							setF(float val);

	//virtual const NeVisibilityPoints*		getVisibilityPoint() const;
	void									reset();

	/*
	 *	非接口实现
	 */
	NeAStarNodeImp*							getParentNode();

	NeAStarNodeImp*							getNextNode();
protected:
	float									m_f;
	float									m_g;
	float									m_h;
	NePathNode*								m_parentNode;
	NePathNode*								m_nextNode;
	NePathNodeType							m_type;
};

} // namespace Orphigine

#endif // NeAStarNodeImp_h__