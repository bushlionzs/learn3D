--生长点

x301023_g_GrowpointId = 547 		--对应生长点ID
x301023_g_MinLevel = 20   	

x301023_g_MissionName=""
x301023_g_MissionId = 9050
x301023_g_ItemIndex = -1
--x301023_g_ItemIndex = 
x301023_CSP_HEIWUCHANG_ID			=   22		--黑无常

function x301023_HaveAccepted(sceneId, selfId)
	
end



--生成函数开始************************************************************************
function 	x301023_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301023_g_GrowpointId, sceneId, 0, x301023_g_ItemIndex)
	SetGrowPointObjID(sceneId,x301023_g_GrowpointId,x, y,ItemBoxId)
end
--生成函数结束**********************************************************************


--打开前函数开始&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301023_OnOpen(sceneId,selfId,targetId)
		--PrintStr("x301023_OnOpen")
    return x301023_OnOpenItemBox(sceneId, selfId, targetId, x301023_g_GrowpointId, x301023_g_ItemIndex)	
end
--打开前函数结束&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--回收函数开始########################################################################
function	 x301023_OnRecycle(sceneId,selfId,targetId)
	return   x301023_OnGuildRecycle( sceneId, selfId, targetId, x301023_g_GrowpointId, x301023_g_ItemIndex )
	
end
--回收函数结束########################################################################



--打开后函数开始@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301023_OnProcOver(sceneId,selfId,targetId)
	--CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
end
--打开后函数结束@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



function	x301023_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)
	--CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end


--**********************************************************************
--采集任务
--打开ItemBox
function x301023_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	return 0
end

function x301023_ShowTipsToAll(sceneId, str)

	local nHumanCount = GetScenePlayerCount( sceneId)
    if nHumanCount > 0 then
        for i = 0, nHumanCount do
            local objId = GetScenePlayerObjId( sceneId,i)
            if objId >= 0 then
                Msg2Player(sceneId, objId, str, 0, 2)
            end
        end
    end
end

--回收
function x301023_OnGuildRecycle( sceneId, selfId, targetId, gpType, needItemID )
	--print("x301023_OnGuildRecycle")
	local ran = random(2,2) 
	if ran == 1 then  	--自爆
		local x,z = GetWorldPos(sceneId, selfId)
		
		local Num =  GetNearPlayerCount(sceneId, selfId,x,z,5)  
		for i = 0, Num-1 do
			local humanObjId = GetNearPlayerMember(sceneId, selfId,i);
			if humanObjId >= 0 then
				if IsPlayerStateNormal(sceneId, humanObjId) > 0 then
					local hp = GetHp(sceneId, humanObjId)
					local maxhp = GetPlayerMaxHP(sceneId, humanObjId)
					local ranIndex = random(10,40) 
					hp = floor(- maxhp*(ranIndex/100))
					SetHp(sceneId, humanObjId, hp)
					local str = format("你减血%d",-hp)
					Msg2Player(sceneId, humanObjId, str, 0, 2)
				end
			end
		end
		
	elseif ran == 2 then  	--
			
		local heiwuchangId = GetFubenData_Param(sceneId, x301023_CSP_HEIWUCHANG_ID )
		if heiwuchangId >= 0 then			--黑无常加BUFF
			SendSpecificImpactToUnit( sceneId, selfId,selfId, heiwuchangId, 7712, 0)
			local str = "黑无常停留30秒"
			local x,z = GetWorldPos(sceneId, selfId)
			local Num =  GetNearPlayerCount(sceneId, selfId,x,z,5)  
			for i = 0, Num-1 do
				local humanObjId = GetNearPlayerMember(sceneId, selfId,i);
				if humanObjId >= 0 then
					Msg2Player(sceneId, humanObjId, str, 0, 2)
					Msg2Player(sceneId,humanObjId, str, 0, 3)
				end
			end
		end
	end
	
	SetGrowPointIntervalContainer(sceneId, x301023_g_GrowpointId, 40000)
	
	return 1
	
end