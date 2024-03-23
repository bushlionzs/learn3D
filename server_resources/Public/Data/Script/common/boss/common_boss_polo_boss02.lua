x305012_g_ScriptId = 305012

-- 怪物创建后世界广播消息
x305012_g_MonsterAppeared       = "莫斯科大公--伊凡雷帝不甘失败，又一次带着手下出现在莫斯科公国！"

-- Boss表
x305012_g_BossTable             = { 
                                    { bossId = 9751, posX = 31, posZ = 154, ai = 0, aiscript = 976, objGuid = -1, campId = 21, liveTime = -1, bossName = "伊凡雷帝", bossTitle = "莫斯科大公" }, 
                                    { bossId = 9751, posX =  167, posZ =  94, ai = 0, aiscript = 976, objGuid = -1, campId = 21, liveTime = -1, bossName = "伊凡雷帝", bossTitle = "莫斯科大公" }, 
                                    { bossId = 9751, posX =  174, posZ = 166, ai = 0, aiscript = 976, objGuid = -1, campId = 21, liveTime = -1, bossName = "伊凡雷帝", bossTitle = "莫斯科大公" }, 
                                    { bossId = 9751, posX = 74, posZ = 185, ai = 0, aiscript = 976, objGuid = -1, campId = 21, liveTime = -1, bossName = "伊凡雷帝", bossTitle = "莫斯科大公" }, 
                                    { bossId = 9751, posX = 131, posZ =  175, ai = 0, aiscript = 976, objGuid = -1, campId = 21, liveTime = -1, bossName = "伊凡雷帝", bossTitle = "莫斯科大公" }, 
                                    { bossId = 9751, posX = 174, posZ = 136, ai = 0, aiscript = 976, objGuid = -1, campId = 21, liveTime = -1, bossName = "伊凡雷帝", bossTitle = "莫斯科大公" }, 
                                    { bossId = 9751, posX =  48, posZ =  49, ai = 0, aiscript = 976, objGuid = -1, campId = 21, liveTime = -1, bossName = "伊凡雷帝", bossTitle = "莫斯科大公" }, 
                                    { bossId = 9751, posX =  67, posZ = 125, ai = 0, aiscript = 976, objGuid = -1, campId = 21, liveTime = -1, bossName = "伊凡雷帝", bossTitle = "莫斯科大公" }, 
                                    { bossId = 9751, posX = 58, posZ = 168, ai = 0, aiscript = 976, objGuid = -1, campId = 21, liveTime = -1, bossName = "伊凡雷帝", bossTitle = "莫斯科大公" }, 
                                    { bossId = 9751, posX = 170, posZ =  190, ai = 0, aiscript = 976, objGuid = -1, campId = 21, liveTime = -1, bossName = "伊凡雷帝", bossTitle = "莫斯科大公" }, 
                                    { bossId = 9751, posX = 196, posZ = 147, ai = 0, aiscript = 976, objGuid = -1, campId = 21, liveTime = -1, bossName = "伊凡雷帝", bossTitle = "莫斯科大公" }, 
                                    { bossId = 9751, posX = 168, posZ =  188, ai = 0, aiscript = 976, objGuid = -1, campId = 21, liveTime = -1, bossName = "伊凡雷帝", bossTitle = "莫斯科大公" }, 								
}

function x305012_OnTimerDoingStart( sceneId, actId, Param1, Param2, Param3, Param4, Param5)
	
	if sceneId == 17 then 
		local boss = x305012_g_BossTable[ random( 1, getn( x305012_g_BossTable) ) ]
		CreateMonster( sceneId, boss.bossId, boss.posX, boss.posZ, boss.ai, boss.aiscript, x305012_g_ScriptId, boss.objGuid, boss.campId, 60*60*1000, 0, boss.bossName, boss.bossTitle)
		LuaAllScenceM2Wrold( sceneId, x305012_g_MonsterAppeared, CHAT_PLANE_SCROLL, 1)
		LuaAllScenceM2Wrold( sceneId, "莫斯科大公--伊凡雷帝出现在莫斯科公国！", 5, 1)
		LuaAllScenceM2Wrold(sceneId, "莫斯科大公--伊凡雷帝出现在莫斯科公国！", CHAT_PLANE_SCROLL, 1)
		LuaAllScenceM2Wrold(sceneId, "莫斯科大公--伊凡雷帝出现在莫斯科公国！", CHAT_LEFTDOWN, 1)
		LuaAllScenceM2Wrold(sceneId, "莫斯科大公--伊凡雷帝出现在莫斯科公国！", CHAT_MAIN_RIGHTDOWN, 1)
	end
end

-- Boss被杀后处理
function x305012_OnDie( sceneId, selfId, killerId)
	local ObjType = GetObjType(sceneId,killerId)
	if ObjType == 3 then		-- 被PET杀死
		ObjType = 1
		killerId = GetOwnerID(sceneId, killerId)
	end
	if ObjType ~= 1 then
		return
	end
	if IsPlayerStateNormal( sceneId,killerId ) ~= 1 then
		return
	end
	local name = GetName( sceneId, killerId)
    local countryId = GetCurCountry( sceneId, killerId)
	local countryName = GetCountryName(countryId)
	local msg1 = "莫斯科大公--伊凡雷帝已被"..countryName..name.."击败！"
    LuaAllScenceM2Wrold( sceneId, msg1, 5, 1)
	local msg2 ="莫斯科大公已被击败！"
	LuaAllScenceM2Wrold(sceneId, msg2, CHAT_PLANE_SCROLL, 1)
	LuaAllScenceM2Wrold(sceneId, msg2, CHAT_LEFTDOWN, 1)
	LuaAllScenceM2Wrold(sceneId, msg2, CHAT_MAIN_RIGHTDOWN, 1)
end
