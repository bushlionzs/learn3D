--生长点

x301426_g_GrowpointId = 701 		--对应生长点ID

x301426_g_MissionList = {7537,7538,7539,7551,7552}
x301426_g_BuffList={7709,7710,7711,0}
x301426_g_PosX = 184
x301426_g_PosZ = 146 
function x301426_HaveAccepted(sceneId, selfId)

	for i, item in x301426_g_MissionList do
		if IsHaveQuestNM( sceneId, selfId, item ) > 0 then
			return 1
		end
	end
	return -1
end

function x301426_RandBuff(sceneId, selfId)
	local kindIndex = random(1, 100);
	if kindIndex >= 1 and kindIndex <= 40 then
		return x301426_g_BuffList[1]
	elseif kindIndex > 40 and kindIndex <= 80 then
		return x301426_g_BuffList[4]
	elseif kindIndex > 80 and kindIndex <= 90 then
		return x301426_g_BuffList[2]
	elseif kindIndex > 90 and kindIndex <= 100 then
		return x301426_g_BuffList[3]
	end
end


--生成函数开始************************************************************************
function 	x301426_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301426_g_GrowpointId, sceneId, 0, -1)
	SetGrowPointObjID(sceneId,x301426_g_GrowpointId,x, y,ItemBoxId)
end
--生成函数结束**********************************************************************


--打开前函数开始&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301426_OnOpen(sceneId,selfId,targetId)
		--PrintStr("x301426_OnOpen")
    return x301426_OnOpenItemBox(sceneId, selfId, targetId, x301426_g_GrowpointId, -1)	
end
--打开前函数结束&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--回收函数开始########################################################################
function	 x301426_OnRecycle(sceneId,selfId,targetId)
	return   x301426_OnGuildRecycle( sceneId, selfId, targetId, x301426_g_GrowpointId, -1 )
end
--回收函数结束########################################################################



--打开后函数开始@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301426_OnProcOver(sceneId,selfId,targetId)
	--CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
end
--打开后函数结束@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



function	x301426_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)
	--CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end


--**********************************************************************
--采集任务
--打开ItemBox
function x301426_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	
	if x301426_HaveAccepted(sceneId, selfId) < 0 then
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,"您没有任务【体】铁人三项，请您关注系统公告。")
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return -31
	end
	    
	return 0
end

--回收
function x301426_OnGuildRecycle( sceneId, selfId, targetId, gpType, needItemID )
	
	local buff = x301426_RandBuff(sceneId, selfId)
	if buff == 0 then
		local x,z = GetWorldPos(sceneId,selfId)
		local Num =  GetNearPlayerCount(sceneId, selfId,x,z,5)  
		for i = 0, Num-1 do
			local humanObjId = GetNearPlayerMember(sceneId, selfId,i);
			if humanObjId ~= -1 then
				if IsPlayerStateNormal(sceneId, humanObjId) > 0 then
					if x301426_HaveAccepted(sceneId, humanObjId) > 0 then
						SetPos(sceneId, humanObjId, x301426_g_PosX, x301426_g_PosZ)
					end
				end
			end
		end
		return 1
	end
	
	if buff == 7709 then
		local x,z = GetWorldPos(sceneId,selfId)
		local Num =  GetNearPlayerCount(sceneId, selfId,x,z,5)  
		for i = 0, Num-1 do
			local humanObjId = GetNearPlayerMember(sceneId, selfId,i);

			if humanObjId ~= -1 then
				if IsPlayerStateNormal(sceneId, humanObjId) > 0 then
					if x301426_HaveAccepted(sceneId, humanObjId) > 0 then
						if IsHaveSpecificImpact( sceneId, humanObjId, 7710 ) > 0 then
							CancelSpecificImpact(sceneId, humanObjId,7710)
						end
						SendSpecificImpactToUnit(sceneId, humanObjId, humanObjId, humanObjId, buff, 0)
						BeginQuestEvent(sceneId);
						AddQuestText(sceneId, "增加移动速度15秒");
						EndQuestEvent();
						DispatchQuestTips(sceneId, humanObjId);
					end
				end
			end
		end
		return 1
	end

	if buff == 7710 then
		local x,z = GetWorldPos(sceneId,selfId)
		local Num =  GetNearPlayerCount(sceneId, selfId,x,z,5)  
		for i = 0, Num-1 do
			local humanObjId = GetNearPlayerMember(sceneId, selfId,i);

			if humanObjId ~= -1 then
				if humanObjId ~= selfId then
					if IsPlayerStateNormal(sceneId, humanObjId) > 0 then
						if x301426_HaveAccepted(sceneId, humanObjId) > 0 then
							if IsHaveSpecificImpact( sceneId, humanObjId, 7709 ) > 0 then
								CancelSpecificImpact(sceneId, humanObjId,7709)
							end
							SendSpecificImpactToUnit(sceneId, humanObjId, humanObjId, humanObjId, buff, 0)
							BeginQuestEvent(sceneId);
							AddQuestText(sceneId, "减少移动速度5秒");
							EndQuestEvent();
							DispatchQuestTips(sceneId, humanObjId);
						end
					end
				else
					BeginQuestEvent(sceneId);
					AddQuestText(sceneId, "你抵御了减速厄运");
					EndQuestEvent();
					DispatchQuestTips(sceneId, humanObjId);
				end
			end
		end
		return 1
	end
	
	if buff == 7711 then
		local x,z = GetWorldPos(sceneId,selfId)
		local Num =  GetNearPlayerCount(sceneId, selfId,x,z,5)  
		for i = 0, Num-1 do
			local humanObjId = GetNearPlayerMember(sceneId, selfId,i);

			if humanObjId ~= -1 then
				if humanObjId ~= selfId then
					if IsPlayerStateNormal(sceneId, humanObjId) > 0 then
						if x301426_HaveAccepted(sceneId, humanObjId) > 0 then
							if IsHaveSpecificImpact( sceneId, humanObjId, buff ) > 0 then
								CancelSpecificImpact(sceneId, humanObjId,buff)
							end
							SendSpecificImpactToUnit(sceneId, humanObjId, humanObjId, humanObjId, buff, 1000)
							BeginQuestEvent(sceneId);
							AddQuestText(sceneId, "眩晕2秒");
							EndQuestEvent();
							DispatchQuestTips(sceneId, humanObjId);
						end
					end
				else
					BeginQuestEvent(sceneId);
					AddQuestText(sceneId, "你抵御了眩晕厄运");
					EndQuestEvent();
					DispatchQuestTips(sceneId, humanObjId);
				end
			end
		end
		return 1
	end
	
	return 0
end