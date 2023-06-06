#include "stdafx.h"
#include "PathComponent.h"
#include "GameMapPath.h"
#include "kcharacter.h"
#include "game_scene_manager.h"
#include "game_scene.h"
#include "engine_manager.h"
#include "GameMath.h"


PathComponent::PathComponent(KCharacter* character)
{
	mCharacter = character;
}


PathComponent::~PathComponent()
{

}

bool PathComponent::moveTo(Ogre::Vector2& ownerPos, Ogre::Vector2& targetPos)
{
	static CMapPath pathFinder;
	// ����·��	
	if (FALSE == pathFinder.MoveTo(ownerPos, targetPos, 0.0f, false))
	{
		return false;
	}

	mPathList.clear();
	const GLPos* glpos = pathFinder.GetFinalPath();
	int32_t count = pathFinder.GetFinalPathCount();

	for (int32_t i = count - 1; i >= 0; i--)
	{
		mPathList.push_back(Ogre::Vector2(glpos[i].m_fX, glpos[i].m_fZ));
	}

	mPathIndex = mPathList.size() - 1;

	return true;
}

void PathComponent::update(float deltatime)
{
	if (mPathList.empty())
		return;
	const Ogre::Vector3& playerPos = mCharacter->getPosition();

	Ogre::Vector2 currentPos(playerPos.x, playerPos.z);

	Ogre::Vector2 targetPos = mPathList.back();

	Ogre::Real fDistToTarget = currentPos.distance(targetPos); 

	Ogre::Real fElapseTime = (FLOAT)deltatime;
	Ogre::Real fSpeed = 3.5f;


	Ogre::Real fMoveDist = fSpeed * fElapseTime;

	if (fMoveDist < 0.000001f)
		return;

	bool bStopMove = false;

	Ogre::Vector2 fvSetToPos = currentPos;

	Ogre::Real fSetToDir = getFaceDir();

	while (true)
	{
		if (fMoveDist < fDistToTarget)
		{
			if (0.f == fDistToTarget)
				break;

			Ogre::Real fDistX = (fMoveDist * (targetPos.x - currentPos.x)) / fDistToTarget;
			Ogre::Real fDistZ = (fMoveDist * (targetPos.y - currentPos.y)) / fDistToTarget;

			fvSetToPos.x = currentPos.x + fDistX;
			fvSetToPos.y = currentPos.y + fDistZ;

			auto a = vector2(currentPos.x, currentPos.y);
			auto b = vector2(targetPos.x, targetPos.y);
			fSetToDir = CGameMath::KLU_GetYAngle(a, b);

			break;
		}
		else
		{
			mPathList.pop_back();

			if (mPathList.empty())
			{
				// �ߵ���
				bStopMove = TRUE;
				fvSetToPos = targetPos;
				if (currentPos != targetPos)// ԭ��, ���ı䳯��
				{
					auto a = vector2(currentPos.x, currentPos.y);
					auto b = vector2(targetPos.x, targetPos.y);
					fSetToDir = CGameMath::KLU_GetYAngle(a, b);
				}
				break;
			}
			else
			{
				// �ı�m_StateDate_Move�еĸ���ֵ
				fMoveDist -= fDistToTarget;
				currentPos = targetPos;
				targetPos = mPathList.back();

				fDistToTarget = currentPos.distance(targetPos);
			}
		}
	}

	calculateNodePos(fvSetToPos, 0.0f);

	toFaceDir(fSetToDir, getFaceDir());
	updateToFaceDir(deltatime);

	if (bStopMove)
	{
		mCharacter->ChangeAction(CA_MOVING, 0.0f);
	}
}

void PathComponent::toFaceDir(Ogre::Real targetdir, Ogre::Real facedir)
{
	Ogre::Real todir = targetdir;
	if (todir < 0.f)
	{
		todir = KLU_PI * 2.f + targetdir;
	}
	if (fabs(todir - mfToRotation) > 0.01f)
	{
		FLOAT fAddDir = fabs(todir - facedir);

		if (fAddDir >= KLU_PI)
		{
			fAddDir = KLU_PI * 2.f - fAddDir;
		}
		mfToRotation = fAddDir / KLU_PI * KLU_PI / 150.f;
		if (mfToRotation < 0.f)
			mfToRotation = fabs(mRotationSpeed);
	}

	mfToRotation = todir;
}

void PathComponent::updateToFaceDir(float deltatime)
{
	FLOAT fDir = getFaceDir();
	if (mfToRotation != fDir)
	{
		FLOAT fCha = mfToRotation - fDir;
		if (fabs(fCha) < 0.01f) // С��1��
		{
			setFaceDir(mfToRotation);
			return;
		}

		FLOAT fDirAdd = deltatime * mRotationSpeed;

		if (fDirAdd > fabs(fCha))
			fDirAdd = fabs(fCha);

		BOOL bTurnLeft = TRUE;
		if (fCha < -KLU_PI || (fCha > 0 && fCha < KLU_PI))
		{
			bTurnLeft = FALSE;
		}
		if (FALSE == bTurnLeft)
		{
			fDir += fDirAdd;
			if (fDir > KLU_PI * 2.f)
			{
				fDir -= KLU_PI * 2.f;
				if (fDir > mfToRotation)
				{
					fDir = mfToRotation;
				}
			}
		}
		else
		{
			fDir -= fDirAdd;
			if (fDir < 0.f)
			{
				fDir += KLU_PI * 2.f;
				if (fDir < mfToRotation)
				{
					fDir = mfToRotation;
				}
			}
		}
		setFaceDir(fDir);
	}
}


Ogre::Real PathComponent::getFaceDir()
{
	return mCharacter->getDirection();
}

void PathComponent::setFaceDir(Ogre::Real dir)
{
	mCharacter->setDirection(dir);
}

void PathComponent::calculateNodePos(const Ogre::Vector2 & fvPosition, FLOAT fModifyHeight)
{
	auto pActiveScene = GameSceneManager::getSingleton().GetActiveScene();


		//��ǰλ��
	Ogre::Vector3	fvCurObjPos = mCharacter->getPosition();
	FLOAT	fInAirHeight = fvCurObjPos.y;

	//---------------------------------------------------
	//����ȡ���ڵ����ϵĸ߶�
	Ogre::Vector3 fvAtTerrain;
	FLOAT fHeight = -FLT_MAX;

	EngineManager::getSingleton().positionAxisTrans(GAT_GAME, Ogre::Vector3(fvPosition.x, 0.0f, fvPosition.y),
		GAT_SCENE, fvAtTerrain);

	//---------------------------------------------------
	//ȡ�����������ϸ߶�
	if (FALSE == pActiveScene->getCollision().Get3DMapHeight(fvPosition.x, fvCurObjPos.y, fvPosition.y, fHeight))
	{
		fHeight = -FLT_MAX;
	}

	// �������ո߶ȣ� ���������Ƿ����������ϵ�״̬
	FLOAT fRealHeight = 0.0f;

	if (fHeight > fvAtTerrain.y)
	{
		fRealHeight = fHeight;
	}
	else
	{
		fRealHeight = fvAtTerrain.y;
	}

	Ogre::Vector3 position(fvPosition.x, fRealHeight + fModifyHeight, fvPosition.y);
	mCharacter->setPosition(position, false);
	

}

