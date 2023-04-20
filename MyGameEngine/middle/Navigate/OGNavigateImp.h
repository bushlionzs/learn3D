#ifndef NeSDKImp_h__
#define NeSDKImp_h__

#include "OGNavigate.h"
#include <vector>

namespace Orphigine 
{

class NeSpace;
class NeUtilLib;

class NeSDKImp : public NeSDK
{
public:
	NeSDKImp();
	~NeSDKImp();

	virtual NeSpace*	createSpace();

	virtual void		removeSpace(NeSpace* space);

	virtual NeSpace*	getSpace(int index) const;

	virtual NeUtilLib*	getUtilLib();

protected:
	std::vector<NeSpace*>	m_spaces;
	NeUtilLib*				m_utilLib;
private:
};

} // namespace Orphigine

#endif // NeSDKImp_h__