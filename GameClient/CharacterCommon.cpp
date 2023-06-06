
#include "ogreheader.h"
#include "CharacterCommon.h"
#include "Basics.h"

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


