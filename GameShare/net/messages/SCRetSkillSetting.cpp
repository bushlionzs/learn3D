#include "stdafx.h"
#include "SCRetSkillSetting.h"
#include "server/server_manager.h"

SCRetSkillSetting::SCRetSkillSetting():
	NetPacket(SC_SKILL_SETTING)
{

}

SCRetSkillSetting::~SCRetSkillSetting()
{

}

bool SCRetSkillSetting::process()
{
	
	ACTION_SYS_PTR->MainMenuBar_SetID
	(
		mIndex - SETTING_TYPE_K0,
		mPlayerSetting.m_SettingType,
		mPlayerSetting.m_SettingData
	);

	return true;
}

void SCRetSkillSetting::setObjectId(int32_t id)
{
	mObjectId = id;
}

void SCRetSkillSetting::setPlayerSetting(_PLAYER_SETTING& setting)
{
	mPlayerSetting = setting;
}

void SCRetSkillSetting::setIndex(int32_t index)
{
	mIndex = index;
}
