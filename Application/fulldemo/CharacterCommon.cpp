
#include "ogreheader.h"
#include "CharacterCommon.h"
#include "Basics.h"


ModelPartData::ModelPartData()
{
	Clear();
}

void ModelPartData::Clear()
{
	m_bUpdateFlag = FALSE;
	m_strBackUp = "";
	m_strValue = "";
	m_nBackUp = INVALID_ID;
	m_nValue = INVALID_ID;
}

void ModelPartData::Update()
{
	m_bUpdateFlag = FALSE;
	m_strBackUp = m_strValue;
	m_nBackUp = m_nValue;
}

BOOL ModelPartData::IsFlag()
{
	if (m_bUpdateFlag)
	{
		if (m_strBackUp != m_strValue)
		{
			return TRUE;
		}
		if (m_nValue != m_nBackUp)
		{
			return TRUE;
		}
		m_bUpdateFlag = FALSE;
	}
	return FALSE;
}

void ModelPartData::SetValue(LPCSTR szValue)
{
	if (szValue && m_strValue != szValue)
	{
		m_strValue = szValue;
		m_bUpdateFlag = TRUE;
	}
}

void ModelPartData::SetValue(int32 nValue)
{
	if (m_nValue != nValue)
	{
		m_nValue = nValue;
		m_bUpdateFlag = TRUE;
	}
}

// -------------------------------------------------------------------------
// 列表
ModelPartDataList::ModelPartDataList()
{
	m_bUpdateFlag = FALSE;

	m_strPartName[BODY_PART_HAIR] = g_szIDSTR_HAIR_MESH;
	m_strPartName[BODY_PART_FACE] = g_szIDSTR_FACE_MESH;
	m_strPartName[BODY_PART_RIGHTHAND] = g_szIDSTR_CURRENT_RIGHTWEAPON;
	m_strPartName[BODY_PART_LEFTHAND] = g_szIDSTR_CURRENT_LEFTWEAPON;
	m_strPartName[BODY_PART_SHIELD] = szIDSTRING_SHIELD_RIGHTWEAPON;
	m_strPartName[BODY_PART_MANTLE] = szIDSTRING_SHOULDER_MESH;
	m_strPartName[BODY_PART_BODY] = g_szIDSTR_MAINBODY_MESH;
	m_strPartName[BODY_PART_HAND] = g_szIDSTR_ARM_MESH;
	m_strPartName[BODY_PART_FEET] = g_szIDSTR_FOOT_MESH;
}

void ModelPartDataList::SetValue(int32 nPart, int32 nValue)
{
	if (0 > nPart || nPart >= BODY_PART_NUMBER)
		return;

	m_ModelPartData[nPart].SetValue(nValue);
	m_bUpdateFlag = TRUE;
}

void ModelPartDataList::SetValue(int32 nPart, LPCSTR szValue)
{
	if (0 > nPart || nPart >= BODY_PART_NUMBER)
		return;

	m_ModelPartData[nPart].SetValue(szValue);
	m_bUpdateFlag = TRUE;
}

void ModelPartDataList::Clear()
{
	for (int32 i = 0; i < BODY_PART_NUMBER; ++i)
	{
		m_ModelPartData[i].Clear();
	}
	m_bUpdateFlag = FALSE;
}

void ModelPartDataList::Update()
{
	for (int32 i = 0; i < BODY_PART_NUMBER; ++i)
	{
		m_ModelPartData[i].Update();
	}
	m_bUpdateFlag = FALSE;
}

// ------------------------------------------------------------


LPCSTR GetCharaLocatorName( ENUM_CHARACTER_LOCATOR eLocator )
{
	switch( eLocator )
	{
	case LOCATOR_CHAR_HEAD:			return "人物头部绑定点";
	case LOCATOR_CHAR_FRONT:		return "人物身体前置点";
	case LOCATOR_CHAR_ATTACK:		return "人物身体受击点";
	case LOCATOR_CHAR_CENTER:		return "人物身体中心点";
	case LOCATOR_CHAR_FOOT:			return "人物脚部绑定点";
	case LOCATOR_CHAR_HAND_L:		return "人物左手绑定点";
	case LOCATOR_CHAR_HAND_R:		return "人物右手绑定点";
	case LOCATOR_CHAR_SHOULDER_L:	return "人物左肩绑定点";
	case LOCATOR_CHAR_SHOULDER_R:	return "人物右肩绑定点";
	case LOCATOR_CHAR_SHIELD_L:		return "人物左臂盾牌绑定点";
	};

	return "";
}

LPCSTR GetMountLocatorName( ENUM_MOUNT_LOCATOR eLocator )
{
	switch( eLocator )
	{
	case LOCATOR_MOUNT_LF:		return "坐骑马左前蹄绑定点";
	case LOCATOR_MOUNT_RF:		return "坐骑马右前蹄绑定点";
	case LOCATOR_MOUNT_LB:		return "坐骑马左后蹄绑定点";
	case LOCATOR_MOUNT_RB:		return "坐骑马右后蹄绑定点";
	case LOCATOR_MOUNT_FOOT:	return "坐骑马脚部绑定点";
	case LOCATOR_MOUNT_HEAD:	return "坐骑马头部绑定点";
	case LOCATOR_MOUNT_BOSOM:	return "坐骑马胸部绑定点";
	case LOCATOR_MOUNT_BACK:	return "坐骑马背部绑定点";	
		// 坐骑马背部NOX轴绑定点
	};

	return "";
}

LPCSTR GetWeaponLocatorName( ENUM_WEAPON_LOCATOR eLocator )
{
	switch( eLocator )
	{
	case LOCATOR_WEAPON_1:		return "武器绑定点_01";
	case LOCATOR_WEAPON_2:		return "武器绑定点_02";
	case LOCATOR_WEAPON_3:		return "武器绑定点_03";
	case LOCATOR_WEAPON_4:		return "武器绑定点_04";
	};

	return "";
}



const char *g_szIDSTR_FACE_MESH		= ("FaceMesh");
const char *g_szIDSTR_FACE_MAT			= ("FaceMat");

const char *g_szIDSTR_HAIR_MESH		= ("HairMesh");
const char *g_szIDSTR_HAIR_MAT			= ("HairMat");

const char *szIDSTRING_SHOULDER_MESH	= ("ShoulderMesh");
const char *szIDSTRING_SHOULDER_MAT		= ("ShoulderMat");

const char *g_szIDSTR_MAINBODY_MESH	= ("MainBodyMesh");
const char *g_szIDSTR_MAINBODY_MAT		= ("MainBodyMat");

const char *g_szIDSTR_FOOT_MESH		= ("FootMesh");
const char *g_szIDSTR_FOOT_MAT			= ("FootMat");

const char *g_szIDSTR_CAP_MESH			= ("CapMesh");
const char *g_szIDSTR_CAP_MAT			= ("CapMat");

const char *g_szIDSTR_ARM_MESH			= ("ArmMesh");
const char *g_szIDSTR_ARM_MAT			= ("ArmMat");


const char *g_szIDSTR_CURRENT_LEFTWEAPON	= ("LeftWeaponObj");
const char *g_szIDSTR_CURRENT_RIGHTWEAPON	= ("RightWeaponObj");
const char *szIDSTRING_SHIELD_RIGHTWEAPON   = ("LeftShieldObj");

const char *szIDSTRING_DROPITEM = ("掉落物品绑定点_01");


