
x300719_g_BirdId = 580
x300719_g_Scorpion1 = 581
x300719_g_Scorpion2 = 582	
x300719_g_Scorpion3 = 583

x300719_g_ScriptId = 300719

x300719_g_TickTime = 1000*60*120
x300719_g_BroadCastTickTime = 1000*60*105
x300719_g_Msg = "令火鸟要重新回到这个世界了"


function x300719_OnDie(sceneId, selfId, killerId)
	
	if sceneId == 50 then
		SetSystemTimerTick( sceneId, x300719_g_ScriptId, "OnBroadCast", 71, x300719_g_BroadCastTickTime  ) 
	elseif sceneId == 150 then
		SetSystemTimerTick( sceneId, x300719_g_ScriptId, "OnBroadCast", 72, x300719_g_BroadCastTickTime  ) 
	elseif sceneId == 250 then
		SetSystemTimerTick( sceneId, x300719_g_ScriptId, "OnBroadCast", 73, x300719_g_BroadCastTickTime  ) 
	elseif sceneId == 350 then
		SetSystemTimerTick( sceneId, x300719_g_ScriptId, "OnBroadCast", 74, x300719_g_BroadCastTickTime  ) 
	end
	
	if GetObjType(sceneId, killerId) == 3 then
		killerId = GetMasterObjId(sceneId, killerId)
		if killerId == nil then
			return
		end
	end

	GmKillObj( sceneId, killerId, x300719_g_Scorpion1 ) 
	GmKillObj( sceneId, killerId, x300719_g_Scorpion2 ) 
	GmKillObj( sceneId, killerId, x300719_g_Scorpion3 ) 
	
	local num = random(1,5)
	
	if num <= 4 then
	
	 	BeginAddItem(sceneId)
		
		AddItem( sceneId, 11990001 , 1 )
		
		local ret = EndAddItem(sceneId,killerId)
		
		if ret > 0 then
		
			AddItemListToPlayer(sceneId,killerId)
			
			local Name = GetName(sceneId,killerId)
			
			local Readme = "#G"..Name.."#o幸运的获得了帮会令牌！"
			
			LuaScenceM2Near(sceneId,killerId,Readme,CHAT_RIGHTDOWN,1)
			
		else
		
			Msg2Player(sceneId,killerId,"物品栏已满，无法获得帮会令！",8,2)
			
		end
		
	else
	
		return
		
	end
	
end

function x300719_OnBroadCast(sceneId, actId, uTime)
	
	if sceneId == 50 then
		LuaAllScenceM2Country (sceneId,  x300719_g_Msg, 0, CHAT_PLANE_SCROLL, 6)
		SetSystemTimerTick( sceneId, x300719_g_ScriptId, "OnRespawn", 71, x300719_g_TickTime-x300719_g_BroadCastTickTime  ) 
	elseif sceneId == 150 then
		LuaAllScenceM2Country (sceneId,  x300719_g_Msg, 1, CHAT_PLANE_SCROLL, 6)
		SetSystemTimerTick( sceneId, x300719_g_ScriptId, "OnRespawn", 72, x300719_g_TickTime-x300719_g_BroadCastTickTime  ) 
	elseif sceneId == 250 then
		LuaAllScenceM2Country (sceneId,  x300719_g_Msg, 2, CHAT_PLANE_SCROLL, 6)
		SetSystemTimerTick( sceneId, x300719_g_ScriptId, "OnRespawn", 73, x300719_g_TickTime-x300719_g_BroadCastTickTime  ) 
	elseif sceneId == 350 then
		LuaAllScenceM2Country (sceneId,  x300719_g_Msg, 3, CHAT_PLANE_SCROLL, 6)
		SetSystemTimerTick( sceneId, x300719_g_ScriptId, "OnRespawn", 74, x300719_g_TickTime-x300719_g_BroadCastTickTime  ) 
	end

end

function x300719_OnRespawn(sceneId, actId, uTime)
	RespawnMonster( sceneId,  x300719_g_BirdId)
	RespawnMonster( sceneId,  x300719_g_Scorpion1)
	RespawnMonster( sceneId,  x300719_g_Scorpion2)
	RespawnMonster( sceneId,  x300719_g_Scorpion3)
end


