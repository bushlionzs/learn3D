
#ifndef __PATHFINDER_H__
#define __PATHFINDER_H__

#include "TypeDefine.h"

#define MAX_ROUTES	1024 * 2
#define FOUR_DIRECTIONS 4

class	MapInfo;

class	Wayfinding
{
/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	struct _D2XZLOOKUP
	{
		uint16	costmultiplier;
		short	zx;
		uchar	route;
	} DZX[FOUR_DIRECTIONS];

	struct AIROUTE
	{
		uint16	count;

		uint16	walkpoint;
		uint32	startzx;
		uint32	endzx;

		uchar	route[MAX_ROUTES];
	};

	struct _WORLD
	{
		uchar	mBaseState : 3;
		uchar	mRuntimeState : 2;
		uchar	route : 3;
	};

	struct _NODES
	{
		uint16	f;
		uint16	g;

		uint32	zx;
	};

	struct _NAVMAP_HEAD
	{
		uint16	width;
		uint16	height;
	};

	enum
	{
		EMPTY_NODE	= 0,
		MIN_NODE	= 1,
		NO_ROUTE	= FOUR_DIRECTIONS,
		MAX_HEAP_LEAFS	= MAX_ROUTES,
	};

	enum
	{
		UNKNOWN			= 0,
		IMPASSABLE		= 1,
		OPEN			= 2,
		CLOSED			= 3,
		TEMP_IMPASSABLE		= 4,
		TEMP_IMPASSABLE_CROSS	= 5,
	};

	enum { FINDING = 0, NO_PATH = 1, PATH_FOUND = 2, };
	enum { ROOT_HEAP = 1 };

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	int32		mWidth;
	int32		mHeight;

	float		mGridSize;
	float		mInvGridSize;

	float		mLeftTopx;
	float		mLeftTopz;

	_WORLD		*mWorld;

	_NODES		*mNodes;

	uint16		mLastHeapLeaf;
	uint16		mHeap[MAX_HEAP_LEAFS];

	uint16		mBestFNode;
	uint16		mFreeNode;
	int32		mMaxNode;

	uint32		mStartzx, mEndzx;
	uint16		mStartx, mStartz, mEndx, mEndz;
	float		mfStartX, mfStartZ, mfEndX, mfEndZ;

	int32		mCallTimes;
	int32		mGridNum;
	int32		mGrids[MAX_ROUTES];

	GLPos	mFirstCanGoPos;
	int32		mDistance;
	int32		curStep;

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
public:
	Wayfinding(MapInfo *owner, const char *filename, uint32 &mx, uint32 &mz);
	virtual ~Wayfinding();

	void	Reset();
	void	Reset(int32 startz, int32 endz);

	BOOL	FindPath
		(
			GLPos	*startPt,
			GLPos	*endPos,
			GLPos	*posNode,
			int32		&numNode,
			BOOL		bLine = FALSE,
			int32		maxRoute = MAX_ROUTES
		);
	void	PackRoute(GLPos *posNode, int32 &numNode);
	int32	GetDistance();
	BOOL	IsCanGo(const GLPos &pos);

	BOOL	AddUserDefineBar(const GLPos &lt, const GLPos &rb);
	BOOL	DelUserDefineBar(const GLPos &lt, const GLPos &rb);

/*
 -----------------------------------------------------------------------------------------------------------------------
 -----------------------------------------------------------------------------------------------------------------------
 */
private:
	inline uint16	Distance(const uint32 zx);
	inline uint16	RealDistance(const uint32 zxFirst, const uint32 zxSecond);
	inline int32	LEFT(int32 k);
	inline int32	RIGHT(int32 k);
	inline int32	PARENT(int32 k);
	inline BOOL	NOTEMPTY_UP(int32 k);
	inline BOOL	NOTEMPTY_DOWN(int32 k);
	inline void	SwapHeap(const int32 k1, const int32 k2);

	void		InsertNodeToHeap(uint16 node);
	void		RemoveRootFromHeap();

	void		ReadNavMap(const char *filename, uint32 &mx, uint32 &mz);

	void		InitFourDirections();
	BOOL		IsStraightLine
			(
				float	mAStarBeginPtx,
				float	mAStarBeginPty,
				float	mAStarEndPtx,
				float	mAStarEndPty,
				BOOL	edit
			);
	void		EditAStarPath(float startPtx, float startPty, GLPos *posNode, int32 &numNode);
	void		EditAStarPathOpt(float startPtx, float startPty, GLPos *posNode, int32 &numNode);

	inline BOOL	IsImpassable(const uchar bState);
	inline void	CopyImpassableState(_WORLD *pDestState);
};
#endif
