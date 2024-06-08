#include "OgreHeader.h"
#include <complex>
#include "GameMath.h"
#include "OGNavigateAStarSolver.h"
#include "OGNavigateSpace.h"
#include "OGNavigate.h"
#include "OGNavigateAStarNode.h"

#include <OgreSimpleRenderable.h>
#include <OgreHardwareVertexBuffer.h>

#include <OgreQuaternion.h>
#include <OgreSimpleRenderable.h>
#include <OgreVector3.h>
#include <OgreHardwareBufferManager.h>
#include <OgreHardwareBuffer.h>
#include <OgreViewport.h>
#include <OgreCamera.h>
#include <OgreRoot.h>
#include <OgreMatrix4.h>
#include <OgreSceneNode.h>
#include <OgrePlane.h>
#include <OgreRay.h>
#include <OgreVector2.h>
#include <OgreStringConverter.h>
#include "GameMapRegion.h"
#include "GameMapZone.h"
#include "GameMapPath.h"
#include "game_scene_manager.h"
#include  "engine_manager.h"
#include "DefineResult.h"
#include "OgreSceneManager.h"
#include "game_scene.h"
#include "Terrain.h"
#define INVALID_PATH_EXCEPTION	_T("Invalid Path!")
#define LINE_CROSS_RANGE		0.0001f
#define PATH_DEPTH				250		/* �ݹ���� */
#define PATH_NODE_OFFSET		0.7f	

/*
 =======================================================================================================================
 =======================================================================================================================
 */

CMapPath::CMapPath()
{
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
CMapPath::~CMapPath()
{
}

CMapPath::PathUnit & CMapPath::GetPathUnit(int32 nIndex)
{
	if(m_vPosStack.empty() || nIndex >= (int32) m_vPosStack.size() || 0 > nIndex)
	{
		OGRE_EXCEPT(Exception::ERR_INTERNAL_ERROR, "path param error");
	}
	return m_vPosStack[nIndex];
}
const CMapPath::PathUnit & CMapPath::GetConstPathUnit(int32 nIndex) const
{
	return const_cast<CMapPath *>(this)->GetPathUnit(nIndex);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL CMapPath::CheckCross(Ogre::Vector2 fvmStart, Ogre::Vector2 fvmEnd, const CMapRegion *pcr)
{
	Ogre::Vector2 fv0;
	Ogre::Vector2 fv1;

	if(NULL == pcr)
	{
		return FALSE;
	}

	for(int32 i = 0; i < (int32) pcr->m_vfPoints.size(); i++)
	{
		fv0 = *(pcr->GetPoint(i));
		fv1 = *(pcr->GetPoint(i + 1));
		if(!(fvEuqual(fvmStart, fv0) || fvEuqual(fvmStart, fv1) || fvEuqual(fvmEnd, fv0) || fvEuqual(fvmEnd, fv1)))
		{
			if(CheckCross(fvmStart, fvmEnd, fv0, fv1))
			{
				return true;
			}
		}
	}

	return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL CMapPath::CheckCross(
	Ogre::Vector2 fvMS, Ogre::Vector2 fvME, Ogre::Vector2 fvNS, Ogre::Vector2 fvNE)
{
	if(std::max(fvMS.x, fvME.x) <= std::min(fvNS.x, fvNE.x))
	{
		return FALSE;
	}

	if(std::min(fvMS.x, fvME.x) >= std::max(fvNS.x, fvNE.x))
	{
		return FALSE;
	}

	if(std::max(fvMS.y, fvME.y) <= std::min(fvNS.y, fvNE.y))
	{
		return FALSE;
	}

	if(std::min(fvMS.y, fvME.y) >= std::max(fvNS.y, fvNE.y))
	{
		return FALSE;
	}

	FLOAT temp1 = fvMulti(fvSub(fvMS, fvNS), fvSub(fvNE, fvNS)) * fvMulti(fvSub(fvNE, fvNS), fvSub(fvME, fvNS));
	FLOAT temp2 = fvMulti(fvSub(fvNS, fvMS), fvSub(fvME, fvMS)) * fvMulti(fvSub(fvME, fvMS), fvSub(fvNE, fvMS));

	if((temp1 >= 0) && (temp2 >= 0))
	{
		return true;
	}

	return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
Ogre::Vector2 CMapPath::fvAdd(Ogre::Vector2 fv1, Ogre::Vector2 fv2)
{
	Ogre::Vector2 fvResult = Ogre::Vector2(fv1.x + fv2.x, fv1.y + fv2.y);

	return fvResult;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
Ogre::Vector2 CMapPath::fvSub(Ogre::Vector2 fv1, Ogre::Vector2 fv2)
{
	Ogre::Vector2 fvResult = Ogre::Vector2(fv1.x - fv2.x, fv1.y - fv2.y);

	return fvResult;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
FLOAT CMapPath::fvMulti(Ogre::Vector2 fv1, Ogre::Vector2 fv2)
{
	return(fv1.x * fv2.y - fv1.y * fv2.x);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL CMapPath::fvEuqual(Ogre::Vector2 fv1, Ogre::Vector2 fv2)
{
	if((abs(fv1.x - fv2.x) < 1e-10) && (abs(fv1.y - fv2.y) < 1e-10))
	{
		return true;
	}

	return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
FLOAT CMapPath::fvDistancePow(Ogre::Vector2 fv1, Ogre::Vector2 fv2)
{
	return pow((fv1.x - fv2.x), 2) + pow((fv1.y - fv2.y), 2);
}
/*
 =======================================================================================================================
    ����ӿ�ʼ�㵽�������·��
 =======================================================================================================================
 */
BOOL CMapPath::CreateMovePath(const Ogre::Vector2&fvCurrent, const Ogre::Vector2&fvTarget)
{
	/* �����·��. */
	m_vPosStack.clear();

	if(IsPointInUnreachRegion(fvTarget))
	{
		return FALSE;
	}

	BOOL bRes = TRUE;
	GameScene*tmpActiveScene = (GameScene*)GameSceneManager::getSingleton().GetActiveScene();

	Orphigine::NeSDK * tmpNeSDK = tmpActiveScene->getNeSDK();

	Orphigine::NeSpace * tmpSpace = tmpNeSDK->getSpace(0);

	Orphigine::NeAStarSolver * tmpSolver = (Orphigine::NeAStarSolver *) tmpSpace->getSolver();

	tmpSolver->flush
		(
			Orphigine::NeVector3(fvCurrent.x, 0.0f, fvCurrent.y),
			Orphigine::NeVector3(fvTarget.x, 0.0f, fvTarget.y)
		);

	bool hasPath = tmpSolver->performSolve();

	tmpSolver->smoothPath();

	Orphigine::NeAStarNode * tmpParentNode = (Orphigine::NeAStarNode *) tmpSolver->getEndNode();

	std::vector<Orphigine::NeAStarNode *>	tmpAStarNodeArray;

	tmpAStarNodeArray.clear();

	while(NULL != tmpParentNode)
	{
		tmpAStarNodeArray.push_back(tmpParentNode);
		tmpParentNode = (Orphigine::NeAStarNode *) tmpParentNode->getParentNode();
	}

	for(int32 i = (int32) tmpAStarNodeArray.size() - 1; i > 0; i--)
	{
		PathUnit newPathUnit;
		Orphigine::NeVector3 tmpStart = tmpAStarNodeArray[i]->getPosition() +
			tmpAStarNodeArray[i]->getVertexNormal() *
			PATH_NODE_OFFSET;	

		newPathUnit.fvStart = Ogre::Vector2(tmpStart.getX(), tmpStart.getZ());

		Orphigine::NeVector3	tmpTarget = tmpAStarNodeArray[i - 1]->getPosition() +
			tmpAStarNodeArray[i - 1]->getVertexNormal() *
			PATH_NODE_OFFSET;	

		newPathUnit.fvTarget = Ogre::Vector2(tmpTarget.getX(), tmpTarget.getZ());
		m_vPosStack.push_back(newPathUnit);
	}

	if(!bRes)
	{
		m_vPosStack.clear();
	}

	return bRes;
}

/*
 =======================================================================================================================
    ;
    ��ǰ���Ƿ��ڲ�����������֮�� Ŀ����Ƿ�Ϸ� ;
 =======================================================================================================================
 */
BOOL CMapPath::IsPointInUnreachRegion(const Ogre::Vector2&fvTarget)
{
	Orphigine::NeVector3	tmpTarget = Orphigine::NeVector3(fvTarget.x, 0.0f, fvTarget.y);
	GameScene* tmpActiveScene = (GameScene*)GameSceneManager::getSingleton().GetActiveScene();

	Orphigine::NeSDK * tmpNeSDK = tmpActiveScene->getNeSDK();

	Orphigine::NeSpace * tmpSpace = tmpNeSDK->getSpace(0);

	Orphigine::NeVisibilityPoints	pov;

	pov.m_position = tmpTarget;

	return tmpSpace->isCurrentPointInOtherRegion(&pov);
}

bool CMapPath::IsPassRegion(
	const Ogre::Vector2&fvCurrPos,
	const Ogre::Vector2&fvTargetPos,
	PassRegionInfo &outRegionData)
{
	GameScene*pActiveScene = (GameScene*)GameSceneManager::getSingleton().GetActiveScene();

	if(NULL == pActiveScene) return FALSE;

	static Ogre::Vector2 q1;
	static Ogre::Vector2 q2;
	static Ogre::Vector2 p1;
	static Ogre::Vector2 p2;
	static Ogre::Vector2 fvCrossPos;
	static Ogre::Vector2 fvRegionPos1;					/* �赲���� */
	static Ogre::Vector2 fvRegionPos2;
	static Orphigine::NeVector3 vertexNormal;		/* �赲�ߵķ��� */

	p1 = fvCurrPos;
	p2 = fvTargetPos;
	fvCrossPos = fvTargetPos;

	FLOAT fMinDis = 1000.0f;						/* ���������򽻵��о�����̵� */
	BOOL bCross = FALSE;

	Orphigine::NeSDK * pNeSDK = pActiveScene->getNeSDK();
	Orphigine::NeSpace * pNeSpace = pNeSDK->getSpace(0);

	/* �������е����� */
	for(int32_t i = 0; i < (int32_t) pActiveScene->GetRegionCount(); ++i)
	{
		const Orphigine::NeRegion * pNeRegion = pNeSpace->getRegionByIndex(i);
		if(NULL == pNeRegion) continue;
		if(0 >= pNeRegion->getNumPointsOfVisibility()) continue;

		/* ��Χ�м�� */
		if
		(
			!pNeSpace->isLineSegmentIntersectAABBOfRegion
				(
					Orphigine::NeVector3(fvCurrPos.x, 0.f, fvCurrPos.y),
					Orphigine::NeVector3(fvTargetPos.x, 0.f, fvTargetPos.y),
					pNeRegion
				)
		)
		{
			continue;
		}

	    CMapRegion* cr = pActiveScene->GetRegion(i);
		int32 nRegionPointSize = (int32_t) cr->m_vfPoints.size();

		/* ���������ҵ�һ��ֱ��. */
		for(int32 j = 0; j < nRegionPointSize; j++)
		{
			if(nRegionPointSize - 1 == j)
			{
				q1 = cr->m_vfPoints[j].m_position;
				q2 = cr->m_vfPoints[0].m_position;
			}
			else
			{
				q1 = cr->m_vfPoints[j].m_position;
				q2 = cr->m_vfPoints[j + 1].m_position;
			}

			/* ���ֱ���Ƿ��뵱ǰ��·���ཻ. */
			if(CheckCross(fvCurrPos, fvTargetPos, q1, q2))
			{
				FLOAT fCrossPosX = 0.f;
				FLOAT fCrossPosY = 0.f;

				/* x */
				FLOAT tempLeft = (q2.x - q1.x) * (p1.y - p2.y) - (p2.x - p1.x) * (q1.y - q2.y);
				FLOAT tempRight = (p1.y - q1.y) *
					(p2.x - p1.x) *
					(q2.x - q1.x) +
					q1.x *
					(q2.y - q1.y) *
					(p2.x - p1.x) -
					p1.x *
					(p2.y - p1.y) *
					(q2.x - q1.x);

				if(fabs(tempRight) < 0.00001f)
				{
					continue;
				}
				else
				{
					fCrossPosX = tempRight / tempLeft;
				}

				/* y */
				tempLeft = (p1.x - p2.x) * (q2.y - q1.y) - (p2.y - p1.y) * (q1.x - q2.x);
				tempRight = p2.y *
					(p1.x - p2.x) *
					(q2.y - q1.y) +
					(q2.x - p2.x) *
					(q2.y - q1.y) *
					(p1.y - p2.y) -
					q2.y *
					(q1.x - q2.x) *
					(p2.y - p1.y);
				if(fabs(tempRight) < 0.00001f)
				{
					continue;
				}
				else
				{
					fCrossPosY = tempRight / tempLeft;
				}

				FLOAT fTempDis = fvCurrPos.squaredDistance(Ogre::Vector2(fCrossPosX, fCrossPosY));

				if(fMinDis > fTempDis)
				{
					fMinDis = fTempDis;
					fvCrossPos.x = fCrossPosX;
					fvCrossPos.y = fCrossPosY;
					bCross = TRUE;

					fvRegionPos1 = q1;
					fvRegionPos2 = q2;

					/* ����߷��� */
					if(nRegionPointSize - 1 == j)
					{
						const Orphigine::NeVisibilityPoints * pNVP1 = pNeRegion->getPointOfVisibility(j);
						const Orphigine::NeVisibilityPoints * pNVP2 = pNeRegion->getPointOfVisibility(0);
						if(pNVP1 && pNVP2)
						{
							vertexNormal = pNVP1->m_vertexNormal + pNVP2->m_vertexNormal;
						}
					}
					else
					{
						const Orphigine::NeVisibilityPoints * pNVP1 = pNeRegion->getPointOfVisibility(j);
						const Orphigine::NeVisibilityPoints * pNVP2 = pNeRegion->getPointOfVisibility(j + 1);
						if(pNVP1 && pNVP2)
						{
							vertexNormal = pNVP1->m_vertexNormal + pNVP2->m_vertexNormal;
						}
					}
				}
			}
		}
	}

	if(bCross)
	{
		outRegionData.fvRegionPos1 = fvRegionPos1;
		outRegionData.fvRegionPos2 = fvRegionPos2;
		outRegionData.fvCrossPos = fvCrossPos;
		outRegionData.fvVertexNormal.x = vertexNormal.getX();
		outRegionData.fvVertexNormal.y = vertexNormal.getZ();
		outRegionData.fvVertexNormal.normalise();	/* ��λ��, ȡ���� */
		return TRUE;
	}
	return FALSE;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL CMapPath::GetPathDirect(
	const Ogre::Vector2&fvCurrent,
	const Ogre::Vector2&fvTarget, BOOL bOffset, FLOAT fMinDist)
{
	m_vPosStack.clear();

	/* �ƶ�������� */
	FLOAT fToTargetDist = fvCurrent.distance(fvTarget);

	if(fToTargetDist < fMinDist)
	{
		return FALSE;
	}

	Ogre::Vector2 fvFinalPos = fvTarget;
	static PassRegionInfo RegionInfo;

	if(IsPassRegion(fvCurrent, fvTarget, RegionInfo))
	{
		BOOL bOffsetRes = FALSE;

		/* �Ƿ������� */
		if(bOffset)
		{
			Ogre::Vector2 fvOffsetPos = RegionInfo.fvCrossPos;

			if
			(
				GetRegionOffsetPos
					(
						fvCurrent,
						RegionInfo.fvCrossPos,
						RegionInfo.fvRegionPos1,
						RegionInfo.fvRegionPos2,
						fToTargetDist,
						fvOffsetPos
					)
			)
			{
				static PassRegionInfo OffsetRegionInfo;

				if(IsPassRegion(fvCurrent, fvOffsetPos, OffsetRegionInfo))
				{
					fvFinalPos = OffsetRegionInfo.fvVertexNormal * 0.1f + OffsetRegionInfo.fvCrossPos;
					bOffsetRes = TRUE;
				}
				else if(FALSE == IsPointInUnreachRegion(fvOffsetPos))
				{
					fvFinalPos = fvOffsetPos;
					bOffsetRes = TRUE;
				}
			}
		}

		/* ���赲�ߵķ��߷�����һ�������ƫ��, �����ߵ��赲�� */
		if(FALSE == bOffsetRes)
		{
			fvFinalPos = RegionInfo.fvVertexNormal * 0.3f + RegionInfo.fvCrossPos;
		}

		/* ���ڽӽ�����������,��ֹͻȻת�� */
		if(fvCurrent.squaredDistance(fvFinalPos) < 0.1f) return FALSE;
	}

	PathUnit newPathUnit;

	newPathUnit.fvStart = fvCurrent;
	newPathUnit.fvTarget = fvFinalPos;
	m_vPosStack.push_back(newPathUnit);

	return TRUE;
}


FLOAT V2_Multiply(
	const Ogre::Vector2& fvSp, const Ogre::Vector2& fvEp, const Ogre::Vector2& fvOp)
{
	return((fvSp.x - fvOp.x) * (fvEp.y - fvOp.y) - (fvEp.x - fvOp.x) * (fvSp.y - fvOp.y));
}

/*
 =======================================================================================================================
    ײ���赲ʱ, ��������赲�ܽ�, �����赲�߼���һ��ƫ��, �ý�ɫ���赲����
 =======================================================================================================================
 */
BOOL CMapPath::GetRegionOffsetPos
(
	const Ogre::Vector2&fvCurrPos,
	const Ogre::Vector2&fvCrossPos,
	const Ogre::Vector2 fvRegionPos1,
	const Ogre::Vector2 fvRegionPos2,
	FLOAT fOffsetDist,
	Ogre::Vector2&fvOutPos
)
{
	FLOAT fToRegionDist = 1.f;
	FLOAT fMult = V2_Multiply(fvRegionPos1, fvCurrPos, fvRegionPos2);
	FLOAT fRegionLength = fvRegionPos1.distance(fvRegionPos2);

	if(fRegionLength > 0.0001f)
	{
		fToRegionDist = fabs(fMult / fRegionLength);
	}

	if(fToRegionDist <= 0.5f)	/* ��ǰλ�õ��赲�ľ����㹻�� */
	{
		FLOAT fToCrossDist = fvCurrPos.distance(fvCrossPos);
		FLOAT fSin = 1.f;

		if(fToCrossDist > 0.0001f)
		{
			fSin = fToRegionDist / fToCrossDist;
		}

		static const FLOAT fNeed = sin(KLU_PI / 180.f * 75.f);

		if(fSin < fNeed)		/* ����Ǵ���һ���Ƕ� */
		{
			Ogre::Vector2 fvRegionWay = fvRegionPos2 - fvRegionPos1;

			fvRegionWay.normalise();

			Ogre::Vector2 fvToCrossWay = fvCrossPos - fvCurrPos;

			fvToCrossWay.normalise();

			if(fvRegionWay.x * fvToCrossWay.x + fvRegionWay.y * fvToCrossWay.y < 0.f)	/* ��� */
			{
				fvRegionWay.x = -fvRegionWay.x;
				fvRegionWay.y = -fvRegionWay.y;
			}

			fvOutPos = fvCurrPos + fvRegionWay * fOffsetDist;
			return TRUE;
		}
	}
	return FALSE;
}


/*
 =======================================================================================================================
    ���ҵ�ǰ��ֱ����һ�������Ƿ��ཻ������ཻ���ؽ��������������ֱཻ�ߵ�����ֵ
 =======================================================================================================================
 */
BOOL CMapPath::CheckCross
(
	Ogre::Vector2 fvStart,	/* ֱ�ߵĿ�ʼ�㡣 */
	Ogre::Vector2 fvEnd,		/* ֱ�ߵĽ����㡣 */
	const CMapRegion *pcr, /* Ҫ���ҵ�ֱ�ߡ� */
	FLOAT &fFindX,		/* �ҵ��Ľ���x�� */
	FLOAT &fFindY,		/* �ҵ��Ľ���y */
	FLOAT &fFindDis,	/* �ҵ���ֱ�ߵľ��� */
	int32 &iFindLineIndex /* �ҵ���ֱ�ߵ����� */
)
{
	if(NULL == pcr)
	{
		return FALSE;
	}

	Ogre::Vector2 p1;
	Ogre::Vector2 p2;
	FLOAT fDistance = 10000.0f;
	FLOAT fDis = 0;
	BOOL bFind = FALSE;
	FLOAT fCurFindX = 0;
	FLOAT fCurFindY = 0;
	int32 iPointSize = (int32) pcr->m_vfPoints.size();

	for(int32 i = 0; i < iPointSize; i++)
	{
		if(i == iPointSize - 1)
		{
			p1 = pcr->m_vfPoints[i].m_position;
			p2 = pcr->m_vfPoints[0].m_position;
		}
		else
		{
			p1 = pcr->m_vfPoints[i].m_position;
			p2 = pcr->m_vfPoints[i + 1].m_position;
		}

		if(CheckLineCross(fvStart, fvEnd, p1, p2, fCurFindX, fCurFindY))
		{
			bFind = true;
			fDis = sqrt
				(
					(fvStart.x - fCurFindX) * (fvStart.x - fCurFindX) + (fvStart.y - fCurFindY) *
						(fvStart.y - fCurFindY)
				);
			if(fDis < fDistance)
			{
				fDistance = fDis;
				fFindX = fCurFindX;
				fFindY = fCurFindY;
				iFindLineIndex = i;
				fFindDis = fDis;
			}
		}
	}

	return bFind;
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
BOOL CMapPath::CheckLineCross
(
	Ogre::Vector2 fv1Start,	/* ֱ��1�Ŀ�ʼ�㡣 */
	Ogre::Vector2 fv1End,		/* ֱ��1�Ľ����㡣 */
	Ogre::Vector2 fv2Start,	/* ֱ��2�Ŀ�ʼ�㡣 */
	Ogre::Vector2 fv2End,		/* ֱ��2�Ľ����㡣 */
	FLOAT &fcrossx,		/* �ҵ��Ľ���x�� */
	FLOAT &fcrossy		/* �ҵ��Ľ���y */
)
{
	FLOAT fsx1 = fv1Start.x;
	FLOAT fsy1 = fv1Start.y;
	FLOAT fex1 = fv1End.x;
	FLOAT fey1 = fv1End.y;
	FLOAT fsx2 = fv2Start.x;
	FLOAT fsy2 = fv2Start.y;
	FLOAT fex2 = fv2End.x;
	FLOAT fey2 = fv2End.y;
	FLOAT k1 = 0;
	FLOAT b1 = 0;
	FLOAT k2 = 0;
	FLOAT b2 = 0;
	BOOL bLine1infinite = FALSE;	/* ֱ��1��б���Ƿ�������� */
	BOOL bLine2infinite = FALSE;	/* ֱ��2��б���Ƿ�������� */
	FLOAT tempY = 0;
	FLOAT tempX = 0;

	/* ��ֱ�ߵ�k��bֵ */
	if(abs(fex1 - fsx1) < 0.0001)
	{
		bLine1infinite = true;
	}
	else
	{
		k1 = (fey1 - fsy1) / (fex1 - fsx1);
		b1 = -fsx1 * k1 + fsy1;
	}

	if(abs(fex2 - fsx2) < 0.0001)
	{
		bLine2infinite = true;
	}
	else
	{
		k2 = (fey2 - fsy2) / (fex2 - fsx2);
		b2 = -fsx2 * k2 + fsy2;
	}

	/* �ж�ֱ���Ƿ��ཻ */
	if(bLine1infinite)
	{				/* ֱ��1�Ǵ��ߵ������ */
		if(bLine2infinite)
		{
			if(abs(fsx1 - fsx2) < 0.0001)
			{
				/*
				 * ����ֱ�߶��Ǵ�ֱ�ߡ� ���xֵ��Ⱦ���ͬһ��ֱ���ϡ� ;
				 * �����һ��ֱ�ߵĿ�ʼyֵ
				 * �ڵڶ���ֱ�ߵ�yֵ֮���һ��ֱ�ߵĿ�ʼ�������Ϊ�ǽ��㣨������ֱ�߿����кܴ��غϣ�
				 */
				if((fsy1 - fsy2) * (fsy1 - fey2) < 0)
				{
					fcrossx = fsx1;
					fcrossy = fsy1;
					return true;
				}
				else if((fey1 - fsy2) * (fey1 - fey2) < 0)
				{
					fcrossx = fex1;
					fcrossy = fey1;
					return true;
				}

				return FALSE;
			}
			else
			{
				/* �����߶β���ͬһ��ֱ���ϡ� */
				return FALSE;
			}
		}
		else		/* ֱ��2���Ǵ�ֱ�ߵ������ */
		{
			tempY = k2 * fsx1 + b2;
			if(((tempY - fsy2) * (tempY - fey2) < 0) && ((tempY - fsy1) * (tempY - fey1) < 0))
			{
				fcrossx = fsx1;
				fcrossy = tempY;
				return true;
			}
			else
			{
				return FALSE;
			}
		}
	}
	else
	{				/* ֱ��1���Ǵ��ߵ������ */
		if(bLine2infinite)
		{
			tempY = k1 * fsx2 + b1;
			if(((tempY - fsy2) * (tempY - fey2) < 0) && ((tempY - fsy1) * (tempY - fey1) < 0))
			{
				fcrossx = fsx2;
				fcrossy = tempY;
				return true;
			}
			else
			{
				return FALSE;
			}
		}
		else		/* if(bLine2infinite) */
		{
			if(abs(k1 - k2) < 0.0001)
			{		/* ����ֱ��ƽ�� */
				if(abs(b1 - b2) < 0.0001)
				{	/* ����ֱ���غ� */
					if((fsy1 - fsy2) * (fsy1 - fey2) < 0)
					{
						fcrossx = fsx1;
						fcrossy = fsy1;
						return true;
					}
					else if((fey1 - fsy2) * (fey1 - fey2) < 0)
					{
						fcrossx = fex1;
						fcrossy = fey1;
						return true;
					}

					return FALSE;
				}	/* if(abs(b1 - b2) < 0.0001) */
				else
				{
					return FALSE;
				}
			}
			else
			{
				tempX = (b1 - b2) / (k2 - k1);

				FLOAT ft1 = 0;
				FLOAT ft2 = 0;

				ft1 = (tempX - fsx1) / (fex1 - fsx1);
				ft2 = (tempX - fsx2) / (fex2 - fsx2);

				/* if(((tempX - fsx2)*(tempX - fex2) < 0)&&((tempX - fsx1)*(tempX - fex1) < 0)) */
				if((ft1 > -0.0002) && (ft1 < 1.0002) && (ft2 > -0.0002) && (ft2 < 1.0002))
				{
					fcrossx = tempX;
					fcrossy = k1 * tempX + b1;
					return true;
				}
				else
				{
					return FALSE;
				}
			}
		}
	}
}

BOOL CMapPath::MoveTo(
	const Ogre::Vector2 fvOrigin ,
	const Ogre::Vector2 fvTarget, FLOAT fModifyDist, BOOL bDirectMove)
{
	Ogre::Vector2	fvCurPos		= fvOrigin;
	Ogre::Vector2	fvTargetPos		= fvTarget;
	FLOAT	fContainDist	= 0.f;		/* �ݴ���� */
	BOOL	bResult			= TRUE;
	BOOL	bHaveOutlet		= FALSE;	/* ��Ҫ����·�� */

	BOOL	bCurrInRegion	= IsPointInUnreachRegion(fvCurPos);
	BOOL	bTargetInRegion = IsPointInUnreachRegion(fvTargetPos);

	if (bCurrInRegion && bTargetInRegion)
		return FALSE;

	/* �Ƿ��ǰ�ס����Զ����� */
	if (bDirectMove)
	{
		bResult = GetPathDirect(fvCurPos, fvTargetPos, TRUE);
	}
	/* �����ƶ�·�� */
	else
	{
		/* �Ѿ������赲ʱ, ��4��������չ1�׾���, Ѱ�ҳ��� */
		if(bCurrInRegion)
		{
			if(FALSE == IsPointInUnreachRegion(Ogre::Vector2(fvCurPos.x + 1.f, fvCurPos.y)))
			{
				fvCurPos.x += 1.f;
				bHaveOutlet = TRUE;
			}
			else if(FALSE == IsPointInUnreachRegion(Ogre::Vector2(fvCurPos.x - 1.f, fvCurPos.y)))
			{
				fvCurPos.x -= 1.f;
				bHaveOutlet = TRUE;
			}
			else if(FALSE == IsPointInUnreachRegion(Ogre::Vector2(fvCurPos.x, fvCurPos.y + 1.f)))
			{
				fvCurPos.y += 1.f;
				bHaveOutlet = TRUE;
			}
			else if(FALSE == IsPointInUnreachRegion(Ogre::Vector2(fvCurPos.x, fvCurPos.y - 1.f)))
			{
				fvCurPos.y -= 1.f;
				bHaveOutlet = TRUE;
			}
			else
			{
				/* �Ե���ķ�����ƫ��, Ѱ�ҳ���, ������Ϊ��һ��·�� */
				const Ogre::Vector2&fvOutlet = GetTargetPos(fvCurPos, fvTargetPos, 1.f, 0.f);

				if(FALSE == IsPointInUnreachRegion(fvOutlet))
				{
					fvCurPos.x = fvOutlet.x;
					fvCurPos.y = fvCurPos.y;
					bHaveOutlet = TRUE;
				}
			}
		}

		/* Ŀ������赲��, ������ƫ��ֵ. ��������npcվ���赲����� */
		if (bTargetInRegion)
		{
			/*
			* �ݴ�. ��4��������չ1�׾���,�ٴγ���Ѱ·.
			* Ŀ���Ƿ�ֹNPCվ���赲��Ե��ʱ,�޷�Ѱͨ�����.
			*/
			fContainDist = 1.0f;
			if(fModifyDist > fContainDist)
			{
				if(FALSE == IsPointInUnreachRegion(Ogre::Vector2(fvTargetPos.x + fContainDist, fvTargetPos.y)))
				{
					fvTargetPos.x += fContainDist;
				}
				else if(FALSE == IsPointInUnreachRegion(Ogre::Vector2(fvTargetPos.x - fContainDist, fvTargetPos.y)))
				{
					fvTargetPos.x -= fContainDist;
				}
				else if(FALSE == IsPointInUnreachRegion(Ogre::Vector2(fvTargetPos.x, fvTargetPos.y + fContainDist)))
				{
					fvTargetPos.y += fContainDist;
				}
				else if(FALSE == IsPointInUnreachRegion(Ogre::Vector2(fvTargetPos.x, fvTargetPos.y - fContainDist)))
				{
					fvTargetPos.y -= fContainDist;
				}
			}
		}
		bResult = CreateMovePath(fvCurPos, fvTargetPos);
		if (FALSE == bResult)
		{
			bResult = GetPathDirect(fvCurPos, fvTargetPos, FALSE, 0.5f);
		}
	}

	if (FALSE == bResult)
	{
		return FALSE;
	}

	m_uFinalPathNodeCount = GetUnitNum();

	if (m_uFinalPathNodeCount <= 0)
	{
		return OR_INVALID_TARGET_POS;
	}

	if (m_uFinalPathNodeCount > MAX_PATH_NODE_NUM)
	{
		m_uFinalPathNodeCount = MAX_PATH_NODE_NUM;
	}

	if(bHaveOutlet)
	{
		m_posFinalPathNode[0].m_fX = fvCurPos.x;
		m_posFinalPathNode[0].m_fZ = fvCurPos.y;
	}

	for (int32 i = 0; i < m_uFinalPathNodeCount; ++i)
	{
		const PathUnit& puTemp = GetConstPathUnit(i);

		if(bHaveOutlet)
		{
			m_posFinalPathNode[i+1].m_fX = puTemp.fvTarget.x;
			m_posFinalPathNode[i+1].m_fZ = puTemp.fvTarget.y;
		}
		else
		{
			m_posFinalPathNode[i].m_fX = puTemp.fvTarget.x;
			m_posFinalPathNode[i].m_fZ = puTemp.fvTarget.y;
		}
	}

	if(bHaveOutlet)
	{
		++m_uFinalPathNodeCount;
	}

	/* ��ƫ�ƾ���ü�·�� */
	if(fModifyDist > 0.f)
	{
		uint32 uNodeCount = m_uFinalPathNodeCount;
		ModifyPathNode(fvOrigin, fvTarget, m_posFinalPathNode, uNodeCount, fModifyDist - fContainDist);
		m_uFinalPathNodeCount = uNodeCount;
	}
	return TRUE;
}


/*
=======================================================================================================================
=======================================================================================================================
*/
void CMapPath::ModifyPathNode(
	const Ogre::Vector2&fvCurPos,
	const Ogre::Vector2&TargetPos,
	GLPos *pPathNode, uint32 &uNodeNum, FLOAT fModifyDist)
{
	FLOAT fDist = fModifyDist - 0.5f; /* ������� */

	if(NULL == pPathNode)
		return;

	if(fDist <= 0.001f)
		return;

	if(1 == uNodeNum)
	{
		Ogre::Vector2 fvPos = GetTargetPos(fvCurPos, TargetPos, fDist);
		pPathNode[0].m_fX = fvPos.x;
		pPathNode[0].m_fZ = fvPos.y;
	}
	else if(uNodeNum >= 2)
	{
		Ogre::Vector2 fvCur(pPathNode[uNodeNum-2].m_fX, pPathNode[uNodeNum-2].m_fZ);
		int32	nCount = 0;

		for (uint32 i = uNodeNum - 1; i >= 1; --i)
		{
			if(nCount >= 20) /* �����20�� */
				return;
			++nCount;

			Ogre::Vector2 fvTarget(pPathNode[i].m_fX, pPathNode[i].m_fZ);

			if(ModifyTargetPos(fvCur, fvTarget, fDist))
			{
				pPathNode[i].m_fX = fvTarget.x;
				pPathNode[i].m_fZ = fvTarget.y;

				uNodeNum = i + 1;
				break;
			}

			fvCur.x = pPathNode[i - 1].m_fX;
			fvCur.y = pPathNode[i - 1].m_fZ;
		}
	}
}

/*
=======================================================================================================================
=======================================================================================================================
*/
BOOL CMapPath::ModifyTargetPos(
	const Ogre::Vector2& fvCurPos,
	Ogre::Vector2& fvTargetOut, FLOAT fModifyDist)
{
	if(fModifyDist <= 0.f)
		return FALSE;

	Ogre::Vector3 currPos(fvCurPos.x, 0.f, fvCurPos.y);
	Ogre::Vector3 targetPos(fvTargetOut.x, 0.f, fvTargetOut.y);

	Ogre::Vector3	dir = targetPos - currPos;

	dir.normalise();

	Ogre::Ray	currPath;

	currPath.setOrigin(currPos);
	currPath.setDirection(dir);

	Ogre::Sphere range(targetPos, fModifyDist);

	/* ��ȡ���� */
	std::pair<bool, Ogre::Real> res = Ogre::Math::intersects(currPath, range, true);

	if(res.first)
	{
		FLOAT t = res.second;

		if(t >= 0.f)
		{
			/* ���� */
			Ogre::Vector3	pos = currPos + t * dir;

			/* �����Ƿ����߶��� */
			FLOAT fDistX1 = fabs(pos.x - currPos.x);
			FLOAT fDistX2 = fabs(targetPos.x - currPos.x);

			if(fDistX1 <= fDistX2)
			{
				/* ·���ü� */
				fvTargetOut.x = pos.x;
				fvTargetOut.y = pos.z;
				return TRUE;
			}
		}
	}
	return FALSE;
}

/*
=======================================================================================================================
=======================================================================================================================
*/
Ogre::Vector2 CMapPath::GetTargetPos(
	const Ogre::Vector2& fvCurPos,
	const Ogre::Vector2& TargetPos, FLOAT fDist, FLOAT fWarp)
{
	Ogre::Vector2 fvTarget;
	FLOAT fMTDist = fvCurPos.distance(TargetPos);

	if(0.f == fMTDist)	/* �����0 */
	{
		return TargetPos;
	}
	FLOAT fGoDist = fMTDist - fDist + fWarp;
	if(fGoDist <= 0.f)
	{
		return fvCurPos;
	}
	fvTarget.x = fvCurPos.x + fGoDist * (TargetPos.x - fvCurPos.x) / fMTDist;
	fvTarget.y = fvCurPos.y + fGoDist * (TargetPos.y - fvCurPos.y) / fMTDist;
	return fvTarget;
}


/*
 =======================================================================================================================
    �赲����
 =======================================================================================================================
 */
RegionGrid::RegionGrid(Ogre::SceneManager *sceneMgr) :
	m_bWindowActive(FALSE)
{
	m_pSceneMgr = sceneMgr;
	m_pBaseSceneNode = m_pSceneMgr->getRoot()->createChildSceneNode(BLANKSTRING);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
RegionGrid::~RegionGrid()
{
	DestroyRenderable();
	
	m_pBaseSceneNode->getParent()->removeChild(m_pBaseSceneNode);
	m_pBaseSceneNode->getCreator()->destroySceneNode(m_pBaseSceneNode);
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void RegionGrid::CreateRenderable()
{
	assert(false);
	//if(NULL == m_pBaseSceneNode) return;

	//DestroyRenderable();

	//auto pTerrainData = EngineManager::getSingleton().getTerrain();

	//CMap	*pScene = (CMap *)GameSceneManager::getSingleton().GetActiveScene();

	//Orphigine::NeSDK * tmpNeSDK = pScene->getNeSDK();
	//Orphigine::NeSpace * tmpSpace = tmpNeSDK->getSpace(0);

	//int32 nNumRegion = tmpSpace->getNumRegions();

	//for(int32 i = 0; i < nNumRegion; ++i)
	//{
	//	Orphigine::NeRegion * tmpRegion = tmpSpace->getRegionByIndex(i);
	//	if(NULL == tmpRegion) continue;

	//	int32 nNumPOV = tmpRegion->getNumPointsOfVisibility();

	//	if(0 == nNumPOV) continue;

	//	Line3D	*normalLine = new Line3D();

	//	for(int32 j = 0; j < nNumPOV; ++j)
	//	{
	//		Orphigine::NeVisibilityPoints * tmpVP = tmpRegion->getPointOfVisibility(j);
	//		if(tmpVP)
	//		{
	//			// ��ȡ���θ߶�
	//			vector3 fvAtTerrain;
	//			EngineManager::getSingleton().positionAxisTrans(GAT_GAME,vector3(tmpVP->m_position.getX(), 0.f, tmpVP->m_position.getZ()),GAT_SCENE,fvAtTerrain);

	//			FLOAT fMapHeight = -FLT_MAX;
	//			if (FALSE == EngineManager::getSingleton().GetActiveScene()->m_WalkCollisionMng.Get3DMapHeight( tmpVP->m_position.getX(), 0.f, tmpVP->m_position.getZ(), fMapHeight ))
	//			{
	//				fMapHeight = -FLT_MAX;
	//			}
	//			if( fMapHeight > fvAtTerrain.y )
	//			{
	//				fvAtTerrain.y = fMapHeight;
	//			}
	//			fvAtTerrain.y += 0.2f;
	//			vector3 fvGfxPos;
	//			EngineManager::getSingleton().positionAxisTrans(GAT_SCENE, fvAtTerrain, GAT_ENGINE, fvGfxPos);

	//			normalLine->addPoint(fvGfxPos);
	//		}
	//	}

	//	Orphigine::NeVisibilityPoints * tmpVP = tmpRegion->getPointOfVisibility(0);
	//	if(tmpVP)
	//	{
	//		vector3 fvAtTerrain;

	//		EngineManager::getSingleton().positionAxisTrans
	//			(
	//				GAT_GAME,
	//				vector3(tmpVP->m_position.getX(), 0.f, tmpVP->m_position.getZ()),
	//				GAT_SCENE,
	//				fvAtTerrain
	//			);

	//		fvAtTerrain.y += 0.2f;
	//		vector3 fvGfxPos;

	//		EngineManager::getSingleton().positionAxisTrans(GAT_SCENE, fvAtTerrain, GAT_ENGINE, fvGfxPos);

	//		/*
	//		 * Ogre::Vector3 pos = pTerrainData->_getPosition(tmpVP->m_position.getX(), tmpVP->m_position.getZ());
	//		 */
	//		normalLine->addPoint(fvGfxPos);
	//	}

	//	normalLine->drawLines();

	//	m_pBaseSceneNode->attachObject(normalLine);
	//	m_vRegionLine.push_back(normalLine);
	//}
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void RegionGrid::DestroyRenderable()
{
	/*std::vector<Line3D *>::iterator it = m_vRegionLine.begin();

	for(; it != m_vRegionLine.end(); ++it)
	{
		if(*it)
		{
			m_pBaseSceneNode->detachObject((*it)->getName());
		}

		delete(*it);
	}

	m_vRegionLine.clear();*/
}

/*
 =======================================================================================================================
 =======================================================================================================================
 */
void RegionGrid::SetActive(BOOL bActive)
{
	/*if(!m_vRegionLine.empty())
	{
		std::vector<Line3D *>::iterator it = m_vRegionLine.begin();

		for(; it != m_vRegionLine.end(); ++it)
		{
			(*it)->setVisible(!((*it)->isVisible()));
		}
	}
	else
	{
		CreateRenderable();
	}*/
}
