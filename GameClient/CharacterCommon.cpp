
#include "ogreheader.h"
#include "CharacterCommon.h"
#include "Basics.h"

LPCSTR GetCharaLocatorName( ENUM_CHARACTER_LOCATOR eLocator )
{
	switch( eLocator )
	{
	case LOCATOR_CHAR_HEAD:			return "����ͷ���󶨵�";
	case LOCATOR_CHAR_FRONT:		return "��������ǰ�õ�";
	case LOCATOR_CHAR_ATTACK:		return "���������ܻ���";
	case LOCATOR_CHAR_CENTER:		return "�����������ĵ�";
	case LOCATOR_CHAR_FOOT:			return "����Ų��󶨵�";
	case LOCATOR_CHAR_HAND_L:		return "�������ְ󶨵�";
	case LOCATOR_CHAR_HAND_R:		return "�������ְ󶨵�";
	case LOCATOR_CHAR_SHOULDER_L:	return "�������󶨵�";
	case LOCATOR_CHAR_SHOULDER_R:	return "�����Ҽ�󶨵�";
	case LOCATOR_CHAR_SHIELD_L:		return "������۶��ư󶨵�";
	};

	return "";
}

LPCSTR GetMountLocatorName( ENUM_MOUNT_LOCATOR eLocator )
{
	switch( eLocator )
	{
	case LOCATOR_MOUNT_LF:		return "��������ǰ��󶨵�";
	case LOCATOR_MOUNT_RF:		return "��������ǰ��󶨵�";
	case LOCATOR_MOUNT_LB:		return "�����������󶨵�";
	case LOCATOR_MOUNT_RB:		return "�������Һ���󶨵�";
	case LOCATOR_MOUNT_FOOT:	return "������Ų��󶨵�";
	case LOCATOR_MOUNT_HEAD:	return "������ͷ���󶨵�";
	case LOCATOR_MOUNT_BOSOM:	return "�������ز��󶨵�";
	case LOCATOR_MOUNT_BACK:	return "���������󶨵�";	
		// ��������NOX��󶨵�
	};

	return "";
}

LPCSTR GetWeaponLocatorName( ENUM_WEAPON_LOCATOR eLocator )
{
	switch( eLocator )
	{
	case LOCATOR_WEAPON_1:		return "�����󶨵�_01";
	case LOCATOR_WEAPON_2:		return "�����󶨵�_02";
	case LOCATOR_WEAPON_3:		return "�����󶨵�_03";
	case LOCATOR_WEAPON_4:		return "�����󶨵�_04";
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

const char *szIDSTRING_DROPITEM = ("������Ʒ�󶨵�_01");


