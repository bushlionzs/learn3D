--生长点

x310335_g_GrowpointId = 240 --对应生长点ID
x310335_g_ItemIndex = 10018001 --对应收集物品的ID

x310335_g_GameId = 1042

--生成函数开始************************************************************************
function 	x310335_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x310335_g_GrowpointId, sceneId, 0, x310335_g_ItemIndex)
end
--生成函数结束**********************************************************************


--打开前函数开始&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x310335_OnOpen(sceneId,selfId,targetId)
	if GetGameOpenById(x310335_g_GameId) <= 0 then
		Msg2Player(sceneId,selfId,"此活动已关闭",8,3)
		return 1
	end
    if GetTopListInfo_MinLevel( GetWorldID( sceneId, selfId) ) < 65 then
		Msg2Player(sceneId,selfId,"很抱歉，等级排行榜最后一名玩家未到65级，无法采集",8,3)
        return 1
    end
	return 0
end
--打开前函数结束&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--回收函数开始########################################################################
function	 x310335_OnRecycle(sceneId,selfId,targetId)
	GamePlayScriptLog(sceneId, selfId, 1621)
	local nHumanCount = GetScenePlayerCount(sceneId)
	for i=0,nHumanCount do
  		local objId = GetScenePlayerObjId(sceneId,i)
  		if IsPlayerStateNormal(sceneId,objId) == 1 then
  			local level = GetLevel(sceneId,objId)
  				if selfId == objId then
  					if level >64 then
  						AddExp(sceneId,selfId, level*500)
  						Msg2Player( sceneId, selfId, format("您搜寻到魔女的水晶球，获得%d点经验",level*500), 8, 2) 
  					else	                                                                                   
  						Msg2Player( sceneId, objId, format("您还不到65级，无法采集魔女的水晶球"), 8, 2)
  					end	
  				else
  					if level >64 then
  						AddExp(sceneId,objId, level*100)
  						Msg2Player( sceneId, objId, format("有玩家搜寻到了魔女的水晶球，每人获得%d点经验",level*100), 8, 2)
  					end	
  				end
  		end
	end
        
	return 1
end
--回收函数结束########################################################################



--打开后函数开始@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x310335_OnProcOver(sceneId,selfId,targetId)
	--CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
end
--打开后函数结束@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



function	x310335_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)
	--CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end
