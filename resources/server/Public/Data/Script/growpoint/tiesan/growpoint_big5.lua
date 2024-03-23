--生长点

x301430_g_GrowpointId = 709 		--对应生长点ID

x301430_g_MissionId = 7538
x301430_g_BuffList={7709,7710,7711}

x301430_g_StateBuff = {{{7610,7607},{7608,7605}}, {{7616,7613},{7614,7611}}, {{7622,7619},{7620,7617}}, {{7628,7625},{7626,7623}}}
-- 加自行车buff
function x301430_SendStateBuff(sceneId, selfId)
	local country = GetCurCountry( sceneId, selfId )
	local sex = GetSex( sceneId, selfId )
	
	SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, x301430_g_StateBuff[country+1][2][sex+1], 0)
end

function x301430_CancelStateBuff(sceneId, selfId)
	local country = GetCurCountry( sceneId, selfId )
	local sex = GetSex( sceneId, selfId )
	
	if IsHaveSpecificImpact( sceneId, selfId, x301430_g_StateBuff[country+1][2][sex+1] ) > 0 then
		CancelSpecificImpact(sceneId, selfId,x301430_g_StateBuff[country+1][2][sex+1])
	end
end

function x301430_RandBuff(sceneId, selfId)
	local kindIndex = random(1, 100)
	if kindIndex < 0 or kindIndex > 100 then
		kindIndex = 0
	end
	
	if kindIndex <= 60 then
		return x301430_g_BuffList[1]
	elseif kindIndex <= 80 then
		return x301430_g_BuffList[2]
	else
		return x301430_g_BuffList[3]
	end
end


--生成函数开始************************************************************************
function 	x301430_OnCreate(sceneId,growPointType,x,y)
	local ItemBoxId = ItemBoxEnterScene(x, y, x301430_g_GrowpointId, sceneId, 0, -1)
	SetGrowPointObjID(sceneId,x301430_g_GrowpointId,x, y,ItemBoxId)
end
--生成函数结束**********************************************************************


--打开前函数开始&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
function	 x301430_OnOpen(sceneId,selfId,targetId)
		--PrintStr("x301430_OnOpen")
    return x301430_OnOpenItemBox(sceneId, selfId, targetId, x301430_g_GrowpointId, -1)	
end
--打开前函数结束&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&


--回收函数开始########################################################################
function	 x301430_OnRecycle(sceneId,selfId,targetId)
	return   x301430_OnGuildRecycle( sceneId, selfId, targetId, x301430_g_GrowpointId, -1 )
end
--回收函数结束########################################################################



--打开后函数开始@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
function	x301430_OnProcOver(sceneId,selfId,targetId)
	--CallScriptFunction( MISSION_SCRIPT, "OnProcOver", sceneId, selfId, targetId )
end
--打开后函数结束@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@



function	x301430_OpenCheck(sceneId,selfId,AbilityId,AblityLevel)
	--CallScriptFunction( MISSION_SCRIPT, "OpenCheck", sceneId, selfId, targetId )
end


--**********************************************************************
--采集任务
--打开ItemBox
function x301430_OnOpenItemBox( sceneId, selfId, targetId, gpType, needItemID )
	
	if IsHaveQuestNM( sceneId, selfId, x301430_g_MissionId ) <= 0 then
		Msg2Player(sceneId,selfId,"您没有任务【体】铁人三项，请您关注系统公告。",CHAT_TYPE_SELF,CHAT_PLUMB_SCROLL)
		return -31
	end
	    
	return 0
end

--回收
function x301430_OnGuildRecycle( sceneId, selfId, targetId, gpType, needItemID )
	
	local buff = x301430_RandBuff(sceneId, selfId)
	if buff == 7709 then
		local x,z = GetWorldPos(sceneId,selfId)
		local Num =  GetNearPlayerCount(sceneId, selfId,x,z,5)  
		for i = 0, Num-1 do
			local humanObjId = GetNearPlayerMember(sceneId, selfId,i);

			if humanObjId ~= -1 then
				if IsPlayerStateNormal(sceneId, humanObjId) > 0 then
					if IsHaveQuestNM( sceneId, humanObjId, x301430_g_MissionId ) > 0 then
						if IsHaveSpecificImpact( sceneId, humanObjId, 7710 ) > 0 then
							CancelSpecificImpact(sceneId, humanObjId,7710)
						end
						x301430_SendStateBuff(sceneId, humanObjId)
						SendSpecificImpactToUnit(sceneId, humanObjId, humanObjId, humanObjId, buff, 0)
						Msg2Player(sceneId,humanObjId,"您进入了骑车状态，增加速度15秒！",CHAT_TYPE_SELF,CHAT_PLUMB_SCROLL)
					end
				end
			end
		end
		return 1
	elseif buff == 7710 then
		local x,z = GetWorldPos(sceneId,selfId)
		local Num =  GetNearPlayerCount(sceneId, selfId,x,z,5)  
		for i = 0, Num-1 do
			local humanObjId = GetNearPlayerMember(sceneId, selfId,i);

			if humanObjId ~= -1 then
				if humanObjId ~= selfId then
					if IsPlayerStateNormal(sceneId, humanObjId) > 0 then
						if IsHaveQuestNM( sceneId, humanObjId, x301430_g_MissionId ) > 0 then
							if IsHaveSpecificImpact( sceneId, humanObjId, 7709 ) > 0 then
								CancelSpecificImpact(sceneId, humanObjId,7709)
							end
							x301430_CancelStateBuff(sceneId, humanObjId)
							SendSpecificImpactToUnit(sceneId, humanObjId, humanObjId, humanObjId, buff, 0)
							Msg2Player(sceneId,humanObjId,"很不幸，减少移动速度5秒！",CHAT_TYPE_SELF,CHAT_PLUMB_SCROLL)
						end
					end
				else
					Msg2Player(sceneId,humanObjId,"你成功抵御了减速！",CHAT_TYPE_SELF,CHAT_PLUMB_SCROLL)
				end
			end
		end
		return 1
	elseif buff == 7711 then
		local x,z = GetWorldPos(sceneId,selfId)
		local Num =  GetNearPlayerCount(sceneId, selfId,x,z,5)  
		for i = 0, Num-1 do
			local humanObjId = GetNearPlayerMember(sceneId, selfId,i);

			if humanObjId ~= -1 then
				if humanObjId ~= selfId then
					if IsPlayerStateNormal(sceneId, humanObjId) > 0 then
						if IsHaveQuestNM( sceneId, humanObjId, x301430_g_MissionId ) > 0 then
							if IsHaveSpecificImpact( sceneId, humanObjId, buff ) > 0 then
								CancelSpecificImpact(sceneId, humanObjId,buff)
							end
							SendSpecificImpactToUnit(sceneId, humanObjId, humanObjId, humanObjId, buff, 1000)
							Msg2Player(sceneId,humanObjId,"很不幸，眩晕2秒！",CHAT_TYPE_SELF,CHAT_PLUMB_SCROLL)
						end
					end
				else
					Msg2Player(sceneId,humanObjId,"你成功抵御了眩晕！",CHAT_TYPE_SELF,CHAT_PLUMB_SCROLL)
				end
			end
		end
		return 1
	end
	return 0
end