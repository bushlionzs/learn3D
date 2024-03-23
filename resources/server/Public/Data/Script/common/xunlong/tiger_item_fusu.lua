x310056_g_scriptId = 310056 


x310056_g_DestSceneName1 = "秦岭"
x310056_g_DestSceneName2 = "红沙漠"
x310056_g_DestSceneName3 = "波斯高原"
x310056_g_DestSceneName4 = "波兰王国"
x310056_g_DestSceneName5 = "拜占庭帝国"
x310056_g_DestSceneName6 = "西奈半岛"
x310056_g_DestSceneName7 = "九州岛"
x310056_g_DestSceneName8 = "印度河"
x310056_g_DestSceneName9 = "苏门答腊"
x310056_g_DestSceneId = {7,10,16,19,22,25,29,32,35}


function x310056_ProcEventEntry( sceneId, selfId, BagIndex )
	local PlayerPosX,PlayerPosZ = GetWorldPos( sceneId, selfId )

	--秦岭召龙
	if sceneId == 7 then
	local Positionx1 = 111
	local Positionz1 = 169
	local distanceRet = 5 * 5 - (Positionx1 - PlayerPosX) * (Positionx1 - PlayerPosX) - (Positionz1 - PlayerPosZ) * (Positionz1 - PlayerPosZ)

	if distanceRet <=0 then
		local strText = format("您应该在[%d,%d]使用此物品！", Positionx1, Positionz1 )
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, strText)
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId, selfId)
		Msg2Player(sceneId,selfId,strText, 8, 2)
		return 0
	end

	local ret = CreateMonster( sceneId, 3069, PlayerPosX, PlayerPosZ, 0, -1, x310056_g_scriptId, 160038, 21)

	if ret > 0 then
		EraseItem(sceneId, selfId, BagIndex); --删除物品
		local message = GetName(sceneId, selfId)
		message = message.."在秦岭召出了虎魄星君"
		LuaAllScenceM2Wrold( sceneId, message, CHAT_PLANE_SCROLL, 1 )
		LuaAllScenceM2Wrold( sceneId, message, CHAT_LEFTDOWN, 1 )
		
	--	x310056_UpdateTopList(sceneId, selfId)
	end
	
	--红沙漠召龙
	elseif sceneId == 10 then
	local Positionx2 = 211
	local Positionz2 = 109
	local distanceRet = 5 * 5 - (Positionx2 - PlayerPosX) * (Positionx2 - PlayerPosX) - (Positionz2 - PlayerPosZ) * (Positionz2 - PlayerPosZ)

	if distanceRet <=0 then
		local strText = format("您应该在[%d,%d]使用此物品！", Positionx2, Positionz2 )
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, strText)
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId, selfId)
		Msg2Player(sceneId,selfId,strText, 8, 2)
		return 0
	end

	local ret = CreateMonster( sceneId, 3069, PlayerPosX, PlayerPosZ, 0, -1, x310056_g_scriptId, 160038, 21)

	if ret > 0 then
		EraseItem(sceneId, selfId, BagIndex); --删除物品
		local message = GetName(sceneId, selfId)
		message = message.."在红沙漠召出了虎魄星君"
		LuaAllScenceM2Wrold( sceneId, message, CHAT_PLANE_SCROLL, 1 )
		LuaAllScenceM2Wrold( sceneId, message, CHAT_LEFTDOWN, 1 )
		
	--	x310056_UpdateTopList(sceneId, selfId)
	end
	
		--波斯高原召龙
	elseif sceneId == 16 then
	local Positionx3 = 90
	local Positionz3 = 198
	local distanceRet = 5 * 5 - (Positionx3 - PlayerPosX) * (Positionx3 - PlayerPosX) - (Positionz3 - PlayerPosZ) * (Positionz3 - PlayerPosZ)

	if distanceRet <=0 then
		local strText = format("您应该在[%d,%d]使用此物品！", Positionx3, Positionz3 )
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, strText)
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId, selfId)
		Msg2Player(sceneId,selfId,strText, 8, 2)
		return 0
	end

	local ret = CreateMonster( sceneId, 3069, PlayerPosX, PlayerPosZ, 0, -1, x310056_g_scriptId, 160038, 21)

	if ret > 0 then
		EraseItem(sceneId, selfId, BagIndex); --删除物品
		local message = GetName(sceneId, selfId)
		message = message.."在波斯高原召出了虎魄星君"
		LuaAllScenceM2Wrold( sceneId, message, CHAT_PLANE_SCROLL, 1 )
		LuaAllScenceM2Wrold( sceneId, message, CHAT_LEFTDOWN, 1 )
		
	--	x310056_UpdateTopList(sceneId, selfId)
	end
	
			--波兰王国召龙
	elseif sceneId == 19 then
	local Positionx4 = 128
	local Positionz4 = 47
	local distanceRet = 5 * 5 - (Positionx4 - PlayerPosX) * (Positionx4 - PlayerPosX) - (Positionz4 - PlayerPosZ) * (Positionz4 - PlayerPosZ)

	if distanceRet <=0 then
		local strText = format("您应该在[%d,%d]使用此物品！", Positionx4, Positionz4 )
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, strText)
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId, selfId)
		Msg2Player(sceneId,selfId,strText, 8, 2)
		return 0
	end

	local ret = CreateMonster( sceneId, 3069, PlayerPosX, PlayerPosZ, 0, -1, x310056_g_scriptId, 160038, 21)

	if ret > 0 then
		EraseItem(sceneId, selfId, BagIndex); --删除物品
		local message = GetName(sceneId, selfId)
		message = message.."在波兰王国召出了虎魄星君"
		LuaAllScenceM2Wrold( sceneId, message, CHAT_PLANE_SCROLL, 1 )
		LuaAllScenceM2Wrold( sceneId, message, CHAT_LEFTDOWN, 1 )
		
	--	x310056_UpdateTopList(sceneId, selfId)
	end
	
		--拜占庭帝国召龙
	elseif sceneId == 22 then
	local Positionx5 = 160
	local Positionz5 = 176
	local distanceRet = 5 * 5 - (Positionx5 - PlayerPosX) * (Positionx5 - PlayerPosX) - (Positionz5- PlayerPosZ) * (Positionz5 - PlayerPosZ)

	if distanceRet <=0 then
		local strText = format("您应该在[%d,%d]使用此物品！", Positionx5, Positionz5 )
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, strText)
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId, selfId)
		Msg2Player(sceneId,selfId,strText, 8, 2)
		return 0
	end

	local ret = CreateMonster( sceneId, 3069, PlayerPosX, PlayerPosZ, 0, -1, x310056_g_scriptId, 160038, 21)

	if ret > 0 then
		EraseItem(sceneId, selfId, BagIndex); --删除物品
		local message = GetName(sceneId, selfId)
		message = message.."在拜占庭帝国召出了虎魄星君"
		LuaAllScenceM2Wrold( sceneId, message, CHAT_PLANE_SCROLL, 1 )
		LuaAllScenceM2Wrold( sceneId, message, CHAT_LEFTDOWN, 1 )
		
	--	x310056_UpdateTopList(sceneId, selfId)
	end
	
	--西奈半岛召龙
	elseif sceneId == 25 then
	local Positionx6 = 181
	local Positionz6 = 64
	local distanceRet = 5 * 5 - (Positionx6 - PlayerPosX) * (Positionx6 - PlayerPosX) - (Positionz6- PlayerPosZ) * (Positionz6 - PlayerPosZ)

	if distanceRet <=0 then
		local strText = format("您应该在[%d,%d]使用此物品！", Positionx6, Positionz6 )
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, strText)
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId, selfId)
		Msg2Player(sceneId,selfId,strText, 8, 2)
		return 0
	end

	local ret = CreateMonster( sceneId, 3069, PlayerPosX, PlayerPosZ, 0, -1, x310056_g_scriptId, 160038, 21)

	if ret > 0 then
		EraseItem(sceneId, selfId, BagIndex); --删除物品
		local message = GetName(sceneId, selfId)
		message = message.."在西奈半岛召出了虎魄星君"
		LuaAllScenceM2Wrold( sceneId, message, CHAT_PLANE_SCROLL, 1 )
		LuaAllScenceM2Wrold( sceneId, message, CHAT_LEFTDOWN, 1 )
		
	--	x310056_UpdateTopList(sceneId, selfId)
	end
	
	--九州岛召龙
	elseif sceneId == 29 then
	local Positionx7 = 100
	local Positionz7 = 100
	local distanceRet = 5 * 5 - (Positionx7 - PlayerPosX) * (Positionx7 - PlayerPosX) - (Positionz7- PlayerPosZ) * (Positionz7 - PlayerPosZ)

	if distanceRet <=0 then
		local strText = format("您应该在[%d,%d]使用此物品！", Positionx7, Positionz7 )
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, strText)
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId, selfId)
		Msg2Player(sceneId,selfId,strText, 8, 2)
		return 0
	end

	local ret = CreateMonster( sceneId, 3069, PlayerPosX, PlayerPosZ, 0, -1, x310056_g_scriptId, 160038, 21)

	if ret > 0 then
		EraseItem(sceneId, selfId, BagIndex); --删除物品
		local message = GetName(sceneId, selfId)
		message = message.."在九州岛召出了虎魄星君"
		LuaAllScenceM2Wrold( sceneId, message, CHAT_PLANE_SCROLL, 1 )
		LuaAllScenceM2Wrold( sceneId, message, CHAT_LEFTDOWN, 1 )
		
	--	x310056_UpdateTopList(sceneId, selfId)
	end
	
	--印度河召龙
	elseif sceneId == 32 then
	local Positionx8 = 100
	local Positionz8 = 100
	local distanceRet = 5 * 5 - (Positionx8 - PlayerPosX) * (Positionx8 - PlayerPosX) - (Positionz8- PlayerPosZ) * (Positionz8 - PlayerPosZ)

	if distanceRet <=0 then
		local strText = format("您应该在[%d,%d]使用此物品！", Positionx8, Positionz8 )
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, strText)
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId, selfId)
		Msg2Player(sceneId,selfId,strText, 8, 2)
		return 0
	end

	local ret = CreateMonster( sceneId, 3069, PlayerPosX, PlayerPosZ, 0, -1, x310056_g_scriptId, 160038, 21)

	if ret > 0 then
		EraseItem(sceneId, selfId, BagIndex); --删除物品
		local message = GetName(sceneId, selfId)
		message = message.."在印度河召出了虎魄星君"
		LuaAllScenceM2Wrold( sceneId, message, CHAT_PLANE_SCROLL, 1 )
		LuaAllScenceM2Wrold( sceneId, message, CHAT_LEFTDOWN, 1 )
		
	--	x310056_UpdateTopList(sceneId, selfId)
	end
	
	--苏门答腊召龙
	elseif sceneId == 35 then
	local Positionx9 = 100
	local Positionz9 = 100
	local distanceRet = 5 * 5 - (Positionx9 - PlayerPosX) * (Positionx9 - PlayerPosX) - (Positionz9- PlayerPosZ) * (Positionz9 - PlayerPosZ)

	if distanceRet <=0 then
		local strText = format("您应该在[%d,%d]使用此物品！", Positionx9, Positionz9 )
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, strText)
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId, selfId)
		Msg2Player(sceneId,selfId,strText, 8, 2)
		return 0
	end

	local ret = CreateMonster( sceneId, 3069, PlayerPosX, PlayerPosZ, 0, -1, x310056_g_scriptId, 160038, 21)

	if ret > 0 then
		EraseItem(sceneId, selfId, BagIndex); --删除物品
		local message = GetName(sceneId, selfId)
		message = message.."在苏门答腊召出了虎魄星君"
		LuaAllScenceM2Wrold( sceneId, message, CHAT_PLANE_SCROLL, 1 )
		LuaAllScenceM2Wrold( sceneId, message, CHAT_LEFTDOWN, 1 )
		
	--	x310056_UpdateTopList(sceneId, selfId)
	end
	else
		local strText = format("这里毫无灵气，无法召唤出虎魄星君！" )
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId, strText)
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId, selfId)
		Msg2Player(sceneId,selfId,strText, 8, 2)
	end	
end

function x310056_IsSkillLikeScript( sceneId, selfId)
	return 0; --这个脚本需要动作支持    
	--返回0，走上面的ProcEventEntry逻辑
	--返回1，走下面的逻辑
end

function x310056_CancelImpacts( sceneId, selfId )
	return 0; --不需要这个接口，但要保留空函数,并且始终返回0。
end

function x310056_OnConditionCheck( sceneId, selfId )
	return 0
end

function x310056_OnDeplete( sceneId, selfId )

	return 0
end

function x310056_OnActivateOnce( sceneId, selfId )
end

function x310056_OnActivateEachTick( sceneId, selfId)
	return 1; --不是引导性脚本, 只保留空函数.
end

function x310056_OnDie(sceneId, selfId, killerId)--怪死亡添加日志
	
	x310056_UpdateTopList(sceneId, killerId)
	GamePlayScriptLog(sceneId, killerId, 551)
				
end

function x310056_UpdateTopList(sceneId,selfId)

	local lastday = GetQuestData( sceneId, selfId, MD_TULONG_DAY[1], MD_TULONG_DAY[2], MD_TULONG_DAY[3] )
	local curCount = GetQuestData( sceneId, selfId, MD_TULONG_COUNT[1], MD_TULONG_COUNT[2], MD_TULONG_COUNT[3] )
	local curday = GetWeekFirstDay()
	if lastday ~= curday then
		curCount = 0
	end
	curCount = curCount + 1
	SetQuestData( sceneId, selfId, MD_TULONG_COUNT[1], MD_TULONG_COUNT[2], MD_TULONG_COUNT[3], curCount )
	SetQuestData( sceneId, selfId, MD_TULONG_DAY[1], MD_TULONG_DAY[2], MD_TULONG_DAY[3], curday )
	
	SendToplistKeyValue2GL(sceneId, selfId, TULONG_TOPLIST, curCount)
	
end