x305011_g_ScriptId = 305011

-- СBoss���ñ�
x305011_g_MinorBossTable        = { 
                                    { bossId = 9717, posX = 161, posZ = 141, ai = 0, aiscript = -1, objGuid = -1, campId = 21, liveTime = 1800000}, 
                                    { bossId = 9717, posX = 121, posZ = 141, ai = 0, aiscript = -1, objGuid = -1, campId = 21, liveTime = 1800000}, 
                                    { bossId = 9717, posX = 120, posZ = 115, ai = 0, aiscript = -1, objGuid = -1, campId = 21, liveTime = 1800000}, 
                                    { bossId = 9717, posX = 154, posZ = 115, ai = 0, aiscript = -1, objGuid = -1, campId = 21, liveTime = 1800000}, 
                                    { bossId = 9717, posX = 129, posZ = 121, ai = 0, aiscript = -1, objGuid = -1, campId = 21, liveTime = 1800000}, 
                                    { bossId = 9717, posX = 151, posZ = 129, ai = 0, aiscript = -1, objGuid = -1, campId = 21, liveTime = 1800000}, 
}

-- create table
x305011_g_LiveTable				= { 0, 0, 0, 0, 0, 0, 0 }

function x305011_OnTimerDoingStart( sceneId, actId, Param1, Param2, Param3, Param4, Param5)
    -- ����СBoss
    for i, item in x305011_g_MinorBossTable do
        x305011_g_LiveTable[i] = CreateMonster( sceneId, item.bossId, item.posX, item.posZ, item.ai, item.aiscript, x305011_g_ScriptId, item.objGuid, item.campId, item.liveTime, 0, "��������Ů��˾" )
    end

    -- ������Boss
    x305011_g_LiveTable[7] = CreateMonster( sceneId, 9716, 143, 129, 0, 408, x305011_g_ScriptId, -1, 21, 1800000, 0, "��������", "�������������" )
	
	msg = "������������������������"
	msg3 = "������������롪����������һ�λָ��������������������޵����ĵش�"
	LuaAllScenceM2Wrold(sceneId, msg, CHAT_PLANE_SCROLL, 1)
	LuaAllScenceM2Wrold(sceneId, msg3, CHAT_LEFTDOWN, 1)
end

-- ������Boss��ɱ����
function x305011_OnDie( sceneId, selfId, killerId)
    local name = GetName( sceneId, killerId)
    local countryId = GetCurCountry( sceneId, killerId)
    local ownerId = GetOwnerID( sceneId, killerId)
    if ownerId ~= -1 then
        -- ������ӥɱ������
        name = GetName( sceneId, ownerId)
        countryId = GetCurCountry( sceneId, ownerId)
    end

	if selfId == x305011_g_LiveTable[7] then
		local countryName = GetCountryName(countryId)
		local msg1 = "�������������-���������ѱ�"..countryName..name.."ɱ����"
		LuaAllScenceM2Wrold( sceneId, msg1, 5, 1)
        LuaAllScenceM2Wrold( sceneId, msg1, 1, 1)
	else
		for i, item in x305011_g_LiveTable do
			if selfId == item then
				local countryName = GetCountryName(countryId)
				local msg2 = "��������Ů��˾�ѱ�"..countryName..name.."ɱ����"
				LuaAllScenceM2Wrold( sceneId, msg2, 5, 1)
                LuaAllScenceM2Wrold( sceneId, msg2, 1, 1)
			end
		end
	end
end

