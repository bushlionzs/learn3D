

#include "stdafx.h"
#include "server_map_path.h"
#include "BaseTool.h"

#define CAN_GO_EDGE

#define RECURETIMES	16
#define OFFSETZ		128

/*
 =======================================================================================================================
 =======================================================================================================================
 */

Wayfinding::Wayfinding(MapInfo *owner, const char *filename, uint32 &mx, uint32 &mz)
{
	assert(false);
	ReadNavMap(filename, mx, mz);

	InitFourDirections();
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Wayfinding::ReadNavMap(const char *filename, uint32 &mx, uint32 &mz)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ FILE	*fp = fopen(filename, "rb");
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(NULL == fp)
	{
		char szDesc[64] = {0};
		tsnprintf_s(szDesc, 64, "Wayfinding::ReadNavMap[%s] Fail.", filename);
		KCheckEx(0, szDesc);
		return;
	}

	/*~~~~~~~~~~~~~~~~~*/
	_NAVMAP_HEAD	head;
	/*~~~~~~~~~~~~~~~~~*/

	fread(&head, sizeof(_NAVMAP_HEAD), 1, fp);

	mWidth = head.width;
	mHeight = head.height;
	mGridSize = 0.5;
	mInvGridSize = 1 / mGridSize;

	mx = (uint32) (mWidth * mGridSize);
	mz = (uint32) (mHeight * mGridSize);

	mLeftTopx = 0;
	mLeftTopz = 0;

	mMaxNode = mWidth * mHeight;

	mWorld = new _WORLD[mMaxNode];
	mNodes = new _NODES[mMaxNode + 1];

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	int32	size = sizeof(struct _NAVMAP_HEAD);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(int32 j = 0; j < mHeight; j++)
	{
		for(int32 i = 0; i < mWidth; i++)
		{
			/*~~~~~~~~~*/
			int32	info;
			/*~~~~~~~~~*/

			fread(&info, size, 1, fp);

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			_WORLD	*pWorld = mWorld + j * mWidth + i;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			pWorld->mBaseState = info;
		}
	}

	mNodes[0].zx = 0;
	mNodes[0].f = 0;
	mNodes[0].g = 0;

	curStep = 0;

	fclose(fp);

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Wayfinding::Reset()
{
	for(int32 j = 0; j < mHeight; j++)
	{
		for(int32 i = 0; i < mWidth; i++)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			_WORLD	*pWorld = mWorld + j * mWidth + i;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(pWorld->mBaseState == TEMP_IMPASSABLE)
				pWorld->mBaseState = UNKNOWN;
			else if(pWorld->mBaseState == TEMP_IMPASSABLE_CROSS)
				pWorld->mBaseState = IMPASSABLE;
		}
	}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Wayfinding::InitFourDirections()
{
	/*~~~~~~~~~~~~~~*/
	__GUARD__ int32 n;
	/*~~~~~~~~~~~~~~*/

	for(n = 0; n < FOUR_DIRECTIONS; n++)
	{
		DZX[n].costmultiplier = 10;
	}

	DZX[0].zx = -mWidth;
	DZX[0].route = 2;

	DZX[1].zx = 1;
	DZX[1].route = 3;

	DZX[2].zx = mWidth;
	DZX[2].route = 0;

	DZX[3].zx = -1;
	DZX[3].route = 1;

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
Wayfinding::~Wayfinding()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KSafeDelete_ARRAY(mWorld);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	KSafeDelete_ARRAY(mNodes);

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Wayfinding::Reset(int32 startz, int32 endz)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	KCheck(startz >= 0 && endz < mHeight);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	for(register int32 index = startz * mWidth; index < endz * mWidth; ++index)
	{
		CopyImpassableState(&mWorld[index]);
	}

	mBestFNode = 1;
	mNodes[mBestFNode].zx = mStartzx;
	mNodes[mBestFNode].g = 0;
	mNodes[mBestFNode].f = mNodes[mBestFNode].g + Distance(mStartzx);

	mWorld[mStartzx].route = NO_ROUTE;

	mFreeNode = 1;

	mHeap[0] = EMPTY_NODE;
	mLastHeapLeaf = 1;
	mHeap[mLastHeapLeaf] = mBestFNode;

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Wayfinding::RemoveRootFromHeap()
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__	mHeap[ROOT_HEAP] = mHeap[mLastHeapLeaf--];
	int32		k = ROOT_HEAP;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	while(NOTEMPTY_DOWN(k))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~*/
		int32	leftk = LEFT(k);
		int32	rightk = RIGHT(k);
		int32	bestk;
		/*~~~~~~~~~~~~~~~~~~~~~~*/

		if(NOTEMPTY_DOWN(leftk) && NOTEMPTY_DOWN(rightk))
		{
			if(mNodes[mHeap[leftk]].f < mNodes[mHeap[rightk]].f)
				bestk = leftk;
			else
				bestk = rightk;
		}
		else if(NOTEMPTY_DOWN(leftk))
			bestk = leftk;
		else
			break;

		if(mNodes[mHeap[bestk]].f < mNodes[mHeap[k]].f)
		{
			SwapHeap(k, bestk);
			k = bestk;
		}
		else
			break;
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Wayfinding::InsertNodeToHeap(uint16 node)
{
	__GUARD__ if(mLastHeapLeaf < MAX_HEAP_LEAFS) mLastHeapLeaf++;

	mHeap[mLastHeapLeaf] = node;

	/*~~~~~~~~~~~~~~~~~~~~~~*/
	int32	k = mLastHeapLeaf;
	/*~~~~~~~~~~~~~~~~~~~~~~*/

	while(NOTEMPTY_UP(k))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	parentk = PARENT(k);
		/*~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(NOTEMPTY_UP(parentk))
		{
			if(mNodes[mHeap[k]].f < mNodes[mHeap[parentk]].f)
			{
				SwapHeap(k, parentk);
				k = parentk;
			}
			else
				break;
		}
		else
			break;
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
inline int32 Wayfinding::LEFT(int32 k)
{
	__GUARD__ return k << 1;

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
inline int32 Wayfinding::RIGHT(int32 k)
{
	__GUARD__ return(k << 1) + 1;

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
inline int32 Wayfinding::PARENT(int32 k)
{
	__GUARD__ return(k >> 1);

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
inline BOOL Wayfinding::NOTEMPTY_UP(int32 k)
{
	__GUARD__ return k != 0;

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
inline BOOL Wayfinding::NOTEMPTY_DOWN(int32 k)
{
	__GUARD__ return k <= mLastHeapLeaf;

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
inline void Wayfinding::SwapHeap(const int32 k1, const int32 k2)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ uint16	tmp = mHeap[k1];
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	mHeap[k1] = mHeap[k2];
	mHeap[k2] = tmp;

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Wayfinding::FindPath
(
	GLPos	*startPt,
	GLPos	*endPt,
	GLPos	*posNode,
	int32		&numNode,
	BOOL		bLine,
	int32		maxRoute
)
{
	__GUARD__

	mfStartX = startPt->m_fX;
	mfStartZ = startPt->m_fZ;
	mfEndX = endPt->m_fX;
	mfEndZ = endPt->m_fZ;

	mStartx = (uint16) ((mfStartX - mLeftTopx) * mInvGridSize);
	mStartz = (uint16) ((mfStartZ - mLeftTopz) * mInvGridSize);

	mEndx = (uint16) ((mfEndX - mLeftTopx) * mInvGridSize);
	mEndz = (uint16) ((mfEndZ - mLeftTopz) * mInvGridSize);

	mStartzx = mStartz * mWidth + mStartx;
	mEndzx = mEndz * mWidth + mEndx;

	numNode = 0;

	mDistance = 0;

	if(bLine)
	{
		if(!IsImpassable(mWorld[mStartzx].mBaseState))
		{
			if(IsStraightLine(mfStartX, mfStartZ, mfEndX, mfEndZ, FALSE))
			{
				posNode[numNode++] = GLPos(mfEndX, mfEndZ);
				mDistance = RealDistance(mStartzx, mEndzx);
				return TRUE;
			}
			else
			{
				posNode[numNode++] = mFirstCanGoPos;
				mDistance = RealDistance
					(
						mStartzx,
						(uint16) ((mFirstCanGoPos.m_fZ - mLeftTopz) * mInvGridSize) * mWidth +
							(uint16) ((mFirstCanGoPos.m_fX - mLeftTopx) * mInvGridSize)
					);
				return TRUE;
			}
		}
		else
			return FALSE;
	}

	if(IsImpassable(mWorld[mStartzx].mBaseState) || IsImpassable(mWorld[mEndzx].mBaseState))
	{
		return FALSE;
	}
	else
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	deltax = abs(mEndx - mStartx);
		int32	deltaz = abs(mEndz - mStartz);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if((deltax + deltaz) > maxRoute)
		{
			mDistance = RealDistance
				(
					mStartzx,
					(uint16) ((mFirstCanGoPos.m_fZ - mLeftTopz) * mInvGridSize) * mWidth + (uint16)
						((mFirstCanGoPos.m_fX - mLeftTopx) * mInvGridSize)
				);
			return FALSE;
		}

		if(IsStraightLine(mfStartX, mfStartZ, mfEndX, mfEndZ, FALSE))
		{
			posNode[numNode++] = GLPos(mfEndX, mfEndZ);
			mDistance = RealDistance(mStartzx, mEndzx);
			return TRUE;
		}

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32	minz = min(mStartz, mEndz);
		int32	maxz = max(mStartz, mEndz);
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		minz = max(minz - OFFSETZ, 0);
		maxz = min(maxz + OFFSETZ, mHeight - 1);

		Reset(minz, maxz);

		/*~~~~~~~~~~~~~~~~~~~~~*/
		int32	count = maxRoute;
		/*~~~~~~~~~~~~~~~~~~~~~*/

		do
		{
			mBestFNode = mHeap[ROOT_HEAP];

			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			_NODES	*pparent_node = mNodes + mBestFNode;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(pparent_node->zx == mEndzx)
			{
				PackRoute(posNode, numNode);
				return TRUE;
			}

			mWorld[pparent_node->zx].mRuntimeState = CLOSED;
			RemoveRootFromHeap();

			for(uchar d = 0; d < FOUR_DIRECTIONS; d++)
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
#ifdef CAN_GO_EDGE
				int32	zx = (int32) (pparent_node->zx);
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				if((zx % mWidth == 0) && ((d == 3) || (d == 6) || (d == 7))) continue;
				if((zx % mWidth == (mWidth - 1)) && ((d == 1) || (d == 4) || (d == 5))) continue;

				zx += DZX[d].zx;
				if(zx < 0 || zx >= mWidth * mHeight) continue;

#else
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				uint16	zx = pparent_node->zx + DZX[d].zx;
#endif
				_WORLD	*pworld = mWorld + zx;
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				if(pworld->mRuntimeState == UNKNOWN)
				{
					pworld->mRuntimeState = OPEN;
					pworld->route = d;

					mFreeNode++;

					/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
					_NODES	*pfree_node = mNodes + mFreeNode;
					/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

					pfree_node->zx = zx;
					pfree_node->g = pparent_node->g + DZX[d].costmultiplier;
					pfree_node->f = pfree_node->g + Distance(zx);

					InsertNodeToHeap(mFreeNode);
				}
			}

			if(mLastHeapLeaf <= 0)
			{
				posNode[numNode++] = mFirstCanGoPos;
				mDistance = RealDistance
					(
						mStartzx,
						(uint16) ((mFirstCanGoPos.m_fZ - mLeftTopz) * mInvGridSize) * mWidth +
							(uint16) ((mFirstCanGoPos.m_fX - mLeftTopx) * mInvGridSize)
					);
				return TRUE;
			}
		} while(--count > 0);
#ifdef _DEBUG
		count;
#endif
	}

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
inline uint16 Wayfinding::Distance(const uint32 zx)
{
	__GUARD__ return(uint16) ((abs((int32) (zx & (mWidth - 1)) - (int32) mEndx) + abs((int32) (zx / mWidth) - (int32) mEndz)) * 10);

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
inline uint16 Wayfinding::RealDistance(const uint32 zxFirst, const uint32 zxSecond)
{
	__GUARD__ return(uint16) ((abs((int32) (zxFirst & (mWidth - 1)) - (int32) (zxSecond & (mWidth - 1))) + abs((int32) (zxFirst / mWidth) - (int32) (zxSecond / mWidth))));

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Wayfinding::PackRoute(GLPos *posNode, int32 &numNode)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ AIROUTE	airoute;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	memset(airoute.route, 0, MAX_ROUTES);

	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	uint32	zx = mEndzx;
	int32	start = MAX_ROUTES - 1;
	uchar	route = NO_ROUTE;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	mGridNum = 0;

	/*~~~~~~~~~~~~~~~~~~~~~*/
	GLPos	firstPos;
	/*~~~~~~~~~~~~~~~~~~~~~*/

	mGrids[mGridNum++] = zx;
	mDistance = 0;
	while(zx != mStartzx)
	{
		route = mWorld[zx].route;
		zx += DZX[DZX[route].route].zx;

		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32		x = zx % mWidth;
		int32		z = zx / mWidth;
		GLPos	goPos;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		goPos.m_fX = mLeftTopx + x * mGridSize + mGridSize / 2;
		goPos.m_fZ = mLeftTopz + z * mGridSize + mGridSize / 2;

		if(IsStraightLine(mfStartX, mfStartZ, goPos.m_fX, goPos.m_fZ, TRUE))
		{
			firstPos.m_fX = mLeftTopx + x * mGridSize + mGridSize / 2;
			firstPos.m_fZ = mLeftTopz + z * mGridSize + mGridSize / 2;

			posNode[numNode++] = firstPos;
			mDistance += RealDistance(zx, mGrids[mGridNum - 1]);
			break;
		}
		else
		{
			mGrids[mGridNum++] = zx;
			mDistance += RealDistance(zx, mGrids[mGridNum - 1]);
		}
	}

	if(mGridNum)
	{
		mCallTimes = 0;
		curStep = mGridNum;

		EditAStarPathOpt(firstPos.m_fX, firstPos.m_fZ, posNode, numNode);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
int32 Wayfinding::GetDistance()
{
	return mDistance;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Wayfinding::IsStraightLine
(
	float	mAStarBeginPtx,
	float	mAStarBeginPty,
	float	mAStarEndPtx,
	float	mAStarEndPty,
	BOOL	edit
)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 intersecttime = 0;
	GLPos	startPt(mAStarBeginPtx, mAStarBeginPty);
	GLPos	endPt(mAStarEndPtx, mAStarEndPty);
	int32		xinc1, yinc1;
	int32		x1, y1, x2, y2;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	x1 = (int32) ((startPt.m_fX - mLeftTopx) * mInvGridSize);
	y1 = (int32) ((startPt.m_fZ - mLeftTopz) * mInvGridSize);
	x2 = (int32) ((endPt.m_fX - mLeftTopx) * mInvGridSize);
	y2 = (int32) ((endPt.m_fZ - mLeftTopz) * mInvGridSize);

	/*~~~~~~~~~~~~~~~~~~~*/
	float	deltax, deltay;
	/*~~~~~~~~~~~~~~~~~~~*/

	deltax = (endPt.m_fX - startPt.m_fX) * mInvGridSize;
	deltay = (endPt.m_fZ - startPt.m_fZ) * mInvGridSize;

	mFirstCanGoPos = startPt;

	if(fabs(deltax) >= fabs(deltay))
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		float	slerp = deltay / deltax;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(x2 >= x1)
		{
			xinc1 = 1;

			for(int32 x = x1 + xinc1; x <= x2; x += xinc1)
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				int32	y = (int32)
					(
						((mLeftTopx + x * mGridSize - startPt.m_fX) * slerp + startPt.m_fZ - mLeftTopz) *
						mInvGridSize
					);
				int32	index = x + y * mWidth;
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				if(IsImpassable(mWorld[index].mBaseState) && (edit ? intersecttime++ : 1))
					return FALSE;

				mFirstCanGoPos = GLPos
					(
						mLeftTopx + x * mGridSize + mGridSize / 2,
						mLeftTopz + y * mGridSize + mGridSize / 2
					);

				index = x - xinc1 + y * mWidth;

				if(IsImpassable(mWorld[index].mBaseState) && (edit ? intersecttime++ : 1))
					return FALSE;

				mFirstCanGoPos = GLPos
					(
						mLeftTopx + (x - xinc1) * mGridSize + mGridSize / 2,
						mLeftTopz + y * mGridSize + mGridSize / 2
					);
			}
		}
		else
		{
			xinc1 = -1;
			for(int32 x = x1; x >= x2 - xinc1; x += xinc1)
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				int32	y = (int32)
					(
						(
							startPt.m_fZ +
							slerp *
							((mLeftTopx + x * mGridSize) - startPt.m_fX) -
							mLeftTopz
						) * mInvGridSize
					);
				int32	index = x + y * mWidth;
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				if(IsImpassable(mWorld[x + y * mWidth].mBaseState) && (edit ? intersecttime++ : 1))
					return FALSE;

				mFirstCanGoPos = GLPos
					(
						mLeftTopx + x * mGridSize + mGridSize / 2,
						mLeftTopz + y * mGridSize + mGridSize / 2
					);

				index = x + xinc1 + y * mWidth;

				if(IsImpassable(mWorld[index].mBaseState) && (edit ? intersecttime++ : 1))
					return FALSE;

				mFirstCanGoPos = GLPos
					(
						mLeftTopx + (x + xinc1) * mGridSize + mGridSize / 2,
						mLeftTopz + y * mGridSize + mGridSize / 2
					);
			}
		}
	}
	else
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		float	slerpInv = deltax / deltay;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		if(y2 >= y1)
		{
			yinc1 = 1;
			for(int32 y = y1 + yinc1; y <= y2; y += yinc1)
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				int32	x = (int32)
					(
						(
							((mLeftTopz + y * mGridSize) - startPt.m_fZ) *
							slerpInv +
							startPt.m_fX -
							mLeftTopx
						) * mInvGridSize
					);
				int32	index = x + y * mWidth;
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				if(IsImpassable(mWorld[index].mBaseState) && (edit ? intersecttime++ : 1))
					return FALSE;

				mFirstCanGoPos = GLPos
					(
						mLeftTopx + x * mGridSize + mGridSize / 2,
						mLeftTopz + y * mGridSize + mGridSize / 2
					);

				index = x + (y - yinc1) * mWidth;

				if(IsImpassable(mWorld[index].mBaseState) && (edit ? intersecttime++ : 1))
					return FALSE;

				mFirstCanGoPos = GLPos
					(
						mLeftTopx + x * mGridSize + mGridSize / 2,
						mLeftTopz + (y - yinc1) * mGridSize + mGridSize / 2
					);
			}
		}
		else
		{
			yinc1 = -1;
			for(int32 y = y1; y >= y2 - yinc1; y += yinc1)
			{
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
				int32	x = (int32)
					(
						(
							startPt.m_fX +
							slerpInv *
							((mLeftTopz + y * mGridSize) - startPt.m_fZ) -
							mLeftTopx
						) * mInvGridSize
					);
				int32	index = x + y * mWidth;
				/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

				if(IsImpassable(mWorld[index].mBaseState) && (edit ? intersecttime++ : 1))
					return FALSE;

				mFirstCanGoPos = GLPos
					(
						mLeftTopx + x * mGridSize + mGridSize / 2,
						mLeftTopz + y * mGridSize + mGridSize / 2
					);

				index = x + (y + yinc1) * mWidth;

				if(IsImpassable(mWorld[index].mBaseState) && (edit ? intersecttime++ : 1))
					return FALSE;

				mFirstCanGoPos = GLPos
					(
						mLeftTopx + x * mGridSize + mGridSize / 2,
						mLeftTopz + (y + yinc1) * mGridSize + mGridSize / 2
					);
			}
		}
	}

	__UNGUARD__ return TRUE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Wayfinding::EditAStarPathOpt(float startPtx, float startPty, GLPos *posNode, int32 &numNode)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ float tempStartX = startPtx;
	float		tempStartZ = startPty;
	int32		tempCurrentStep = curStep;
	bool		flag = false;
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	while(tempCurrentStep != 0 && numNode <= RECURETIMES)
	{
		for(int32 i = 0; i < curStep; i++)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32		x = mGrids[i] % mWidth;
			int32		y = mGrids[i] / mWidth;
			GLPos	goPos;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

			if(i != 0)
			{
				goPos.m_fX = mLeftTopx + x * mGridSize + mGridSize / 2;
				goPos.m_fZ = mLeftTopz + y * mGridSize + mGridSize / 2;
			}
			else
			{
				goPos = GLPos(mfEndX, mfEndZ);
			}

			if(IsStraightLine(tempStartX, tempStartZ, goPos.m_fX, goPos.m_fZ, TRUE))
			{
				posNode[numNode++] = goPos;
				tempStartX = goPos.m_fX;
				tempStartZ = goPos.m_fZ;
				curStep = i;
				flag = true;
				break;
			}
		}

		if(flag)
		{
			tempCurrentStep = curStep;
			flag = false;
		}
		else
		{
			break;
		}
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Wayfinding::EditAStarPath(float startPtx, float startPty, GLPos *posNode, int32 &numNode)
{
	__GUARD__ if(mCallTimes++ >= RECURETIMES) return;

	/*~~~~~~~~~~~~~~~~*/
	int32	curGrid = 0;
	/*~~~~~~~~~~~~~~~~*/

	for(int32 i = mGridNum - 1; i >= curStep; i--)
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32		x = mGrids[i] % mWidth;
		int32		y = mGrids[i] / mWidth;
		GLPos	goPos;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		goPos.m_fX = mLeftTopx + x * mGridSize + mGridSize / 2;
		goPos.m_fZ = mLeftTopz + y * mGridSize + mGridSize / 2;

		if(IsStraightLine(startPtx, startPty, goPos.m_fX, goPos.m_fZ, TRUE))
		{
			curStep = i;
			posNode[numNode++] = goPos;

			curGrid = mGrids[i];

			break;
		}
	}

	if(curGrid != mGrids[mGridNum - 1])
	{
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
		int32		x = curGrid % mWidth;
		int32		y = curGrid / mWidth;
		GLPos	startPos;
		/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

		startPos.m_fX = mLeftTopx + x * mGridSize + mGridSize / 2;
		startPos.m_fZ = mLeftTopz + y * mGridSize + mGridSize / 2;

		EditAStarPath(startPos.m_fX, startPos.m_fZ, posNode, numNode);
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Wayfinding::IsCanGo(const GLPos &pos)
{
	__GUARD__ 

	//rj 2010-8-30 对于 -0.x 的小数形式必须作判定否则下面将被转换成 0 
	if (pos.m_fX < 0.0f || pos.m_fZ < 0.0f)
	{
		return FALSE;
	}

	int32 gridx = (uint16) ((pos.m_fX - mLeftTopx) * mInvGridSize);
	int32		gridz = (uint16) ((pos.m_fZ - mLeftTopz) * mInvGridSize);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if((gridx >= 0 && gridx < mWidth) && (gridz >= 0 && gridz < mHeight))
	{
		return !IsImpassable(mWorld[gridz * mWidth + gridx].mBaseState);
	}

	return FALSE;
	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Wayfinding::IsImpassable(const uchar bState)
{
	__GUARD__ if(bState == IMPASSABLE || bState == TEMP_IMPASSABLE || bState == TEMP_IMPASSABLE_CROSS) return TRUE;

	return FALSE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void Wayfinding::CopyImpassableState(_WORLD *pWorld)
{
	__GUARD__ if(pWorld == NULL) return;

	switch(pWorld->mBaseState)
	{
	case TEMP_IMPASSABLE:
	case TEMP_IMPASSABLE_CROSS:
		pWorld->mRuntimeState = IMPASSABLE;
		break;

	default:
		pWorld->mRuntimeState = pWorld->mBaseState;
	}

	__UNGUARD__
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Wayfinding::AddUserDefineBar(const GLPos &lt, const GLPos &rb)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 ltx = (uint16) ((lt.m_fX - mLeftTopx) * mInvGridSize);
	int32		ltz = (uint16) ((lt.m_fZ - mLeftTopz) * mInvGridSize);
	int32		rbx = (uint16) ((rb.m_fX - mLeftTopx) * mInvGridSize);
	int32		rbz = (uint16) ((rb.m_fZ - mLeftTopz) * mInvGridSize);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(ltx >= rbx) return FALSE;
	if(ltz >= rbz) return FALSE;
	if(rbx >= mWidth || rbz >= mHeight) return FALSE;

	/*~~~~~~*/
	int32	i;
	int32	j;
	/*~~~~~~*/

	for(i = ltx; i < rbx; i++)
	{
		for(j = ltz; j < rbz; j++)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	pos = j * mWidth + i;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

			switch(mWorld[pos].mBaseState)
			{
			case UNKNOWN:		mWorld[pos].mBaseState = TEMP_IMPASSABLE; break;
			case IMPASSABLE:	mWorld[pos].mBaseState = TEMP_IMPASSABLE_CROSS; break;
			}
		}
	}

	return TRUE;

	__UNGUARD__ return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL Wayfinding::DelUserDefineBar(const GLPos &lt, const GLPos &rb)
{
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/
	__GUARD__ int32 ltx = (uint16) ((lt.m_fX - mLeftTopx) * mInvGridSize);
	int32		ltz = (uint16) ((lt.m_fZ - mLeftTopz) * mInvGridSize);
	int32		rbx = (uint16) ((rb.m_fX - mLeftTopx) * mInvGridSize);
	int32		rbz = (uint16) ((rb.m_fZ - mLeftTopz) * mInvGridSize);
	/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

	if(ltx >= rbx) return FALSE;
	if(ltz >= rbz) return FALSE;
	if(rbx >= mWidth || rbz >= mHeight) return FALSE;

	/*~~~~~~*/
	int32	i;
	int32	j;
	/*~~~~~~*/

	for(i = ltx; i < rbx; i++)
	{
		for(j = ltz; j < rbz; j++)
		{
			/*~~~~~~~~~~~~~~~~~~~~~~~~~*/
			int32	pos = j * mWidth + i;
			/*~~~~~~~~~~~~~~~~~~~~~~~~~*/

			switch(mWorld[pos].mBaseState)
			{
			case TEMP_IMPASSABLE:		mWorld[pos].mBaseState = UNKNOWN; break;
			case TEMP_IMPASSABLE_CROSS:	mWorld[pos].mBaseState = IMPASSABLE; break;
			}
		}
	}

	return TRUE;
	__UNGUARD__ return FALSE;
}
