x305011_g_ScriptId = 305011

-- 小Boss配置表
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
    -- 创建小Boss
    for i, item in x305011_g_MinorBossTable do
        x305011_g_LiveTable[i] = CreateMonster( sceneId, item.bossId, item.posX, item.posZ, item.ai, item.aiscript, x305011_g_ScriptId, item.objGuid, item.campId, item.liveTime, 0, "加里曼丹女祭司" )
    end

    -- 创建总Boss
    x305011_g_LiveTable[7] = CreateMonster( sceneId, 9716, 143, 129, 0, 408, x305011_g_ScriptId, -1, 21, 1800000, 0, "萨拉曼陀", "加里曼丹大祭祀" )
	
	msg = "加里曼丹大祭祀出现在婆罗洲"
	msg3 = "加里曼丹大祭祀—萨拉曼陀再一次恢复了力量，出现在婆罗洲的中心地带"
	LuaAllScenceM2Wrold(sceneId, msg, CHAT_PLANE_SCROLL, 1)
	LuaAllScenceM2Wrold(sceneId, msg3, CHAT_LEFTDOWN, 1)
end

-- 创建的Boss被杀处理
function x305011_OnDie( sceneId, selfId, killerId)
    local name = GetName( sceneId, killerId)
    local countryId = GetCurCountry( sceneId, killerId)
    local ownerId = GetOwnerID( sceneId, killerId)
    if ownerId ~= -1 then
        -- 狗或者鹰杀死敌人
        name = GetName( sceneId, ownerId)
        countryId = GetCurCountry( sceneId, ownerId)
    end

	if selfId == x305011_g_LiveTable[7] then
		local countryName = GetCountryName(countryId)
		local msg1 = "加里曼丹大祭祀-萨拉曼陀已被"..countryName..name.."杀死！"
		LuaAllScenceM2Wrold( sceneId, msg1, 5, 1)
        LuaAllScenceM2Wrold( sceneId, msg1, 1, 1)
	else
		for i, item in x305011_g_LiveTable do
			if selfId == item then
				local countryName = GetCountryName(countryId)
				local msg2 = "加里曼丹女祭司已被"..countryName..name.."杀死！"
				LuaAllScenceM2Wrold( sceneId, msg2, 5, 1)
                LuaAllScenceM2Wrold( sceneId, msg2, 1, 1)
			end
		end
	end
end

