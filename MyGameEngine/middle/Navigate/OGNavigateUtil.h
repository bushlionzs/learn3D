#ifndef NeUtil_h__
#define NeUtil_h__

#include "vectormath_aos.h"
//#include "GIMath.h"
#include <iostream>
#include <algorithm>

namespace Orphigine 
{

typedef Vectormath::Aos::Vector3	NeVector3;

typedef float						NeReal;

typedef int							NeInt;

typedef unsigned int				NeUInt;

typedef bool						NeBool;

namespace NeMath = Vectormath::Aos;

using namespace std;

class NeUtilLib
{
public:

protected:
	NeUtilLib() {}
	virtual ~NeUtilLib() {}
private:
};

} // namespace Orphigine

#endif // NeUtil_h__