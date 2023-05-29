#ifndef NeSDK_h__
#define NeSDK_h__

namespace Orphigine 
{

class NeSpace;
class NeUtilLib;

class _OrphigineExport NeSDK
{
public:
	//************************************
	// Brief:	  创建空间
	// Method:    createSpace
	// FullName:  NeSDK::createSpace
	// Access:    virtual public 
	// Returns:   NeSpace*
	//************************************
	virtual NeSpace*	createSpace() = 0;
	
	//************************************
	// Brief:	  移除空间
	// Method:    removeSpace
	// FullName:  NeSDK::removeSpace
	// Access:    virtual public 
	// Returns:   void
	// Parameter: NeSpace * space
	//************************************
	virtual void		removeSpace(NeSpace* space) = 0;

	//************************************
	// Brief:	  得到空间
	// Method:    getSpace
	// FullName:  NeSDK::getSpace
	// Access:    virtual public 
	// Returns:   NeSpace*
	// Parameter: int index
	//************************************
	virtual NeSpace*	getSpace(int index) const = 0;
	
	virtual NeUtilLib*	getUtilLib() = 0;

protected:
	NeSDK(){}
	~NeSDK(){}
private:
};


_OrphigineExport NeSDK*  NeCreateSDK();
_OrphigineExport bool  NeRemoveSDK(NeSDK* pNesdk);

} // namespace Orphigine

#endif // NeSDK_h__