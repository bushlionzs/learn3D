--(西奈半岛到耶路撒冷)

x270171_g_ScriptId = 270171
x270171_g_TransPosloulan  ="xinaibandao2yelusaleng0"
x270171_g_TransPoslaiyin  ="xinaibandao2yelusaleng1"
x270171_g_TransPoskunlun  ="xinaibandao2yelusaleng2"
x270171_g_TransPosdunhuang="xinaibandao2yelusaleng3"


--玩家进入一个 area 时触发
function x270171_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
	--print("x270171_ProcAreaEntered sceneId = " .. sceneId .. " selfId = " .. selfId)
	local selfType = GetObjType(sceneId, selfId)
	
	if selfType == 1 then 
		------------------------------------------------------
		if IsHaveSpecificImpact( sceneId, selfId, 7610) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7607) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7608) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7605) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7616) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7613) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7614) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7611) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7622) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7619) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7620) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7617) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7628) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7625) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7626) == 1 or IsHaveSpecificImpact( sceneId, selfId, 7623) == 1 then
			Msg2Player(sceneId,selfId,"很抱歉，未完成铁人三项任务时无法通往其他场景！",8,2)
			return
		end
		--以上用于铁人三项禁止传送的处理
		------------------------------------------------------
	end
	
	if selfType == 9 then	--Bus进入区域 把bus和bus里的人跨场景
		local busType = GetBusType(sceneId, selfId)
		if busType == 1 then --BUS_TYPE_NORMAL
			local memberCount = GetBusMemberCount(sceneId, selfId)
			local daduSceneId = 0
			ReadyBusChangeScene(sceneId, daduSceneId,selfId)--注意：此步骤是必需的.BUS切换场景，要先做些准备工作,
			for	i = 0, memberCount - 1 do
				local ObjID = GetBusMemberObjId(sceneId, selfId, i)
				x270171_TransToPosition(sceneId, ObjID)
			end
			--删除BUS,但乘员仍在车上
			DeleteBus(sceneId, selfId,0)
			return
		end
	elseif selfType == 1 then	--玩家
--		local isBusMember = IsBusMember(sceneId, selfId)
--		if isBusMember == 1 then
--			return
--		end
	end
	
	local strText = ""
	local CanTrans = IsCashboxState(sceneId,selfId)	
	if CanTrans == 1 then
		BeginQuestEvent(sceneId)
			strText = "#Y运镖或者护送状态中，不允许传送"
			AddQuestText(sceneId,strText);
		EndQuestEvent(sceneId)
		DispatchQuestTips(sceneId,selfId)
		return
	end

	local guo = GetCurCountry(sceneId,selfId)
	
	x270171_TransToPosition(sceneId, selfId)
	
end

function x270171_TransToPosition(sceneId, selfId)

	local guo = GetCurCountry(sceneId,selfId)
	
	if guo == 0 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x270171_g_TransPosloulan)
		
		elseif guo == 1 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x270171_g_TransPoslaiyin)
		
		elseif guo == 2 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x270171_g_TransPoskunlun)
		
		elseif guo == 3 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x270171_g_TransPosdunhuang)
	
	end
end

--玩家在一个 area 呆了一段时间没走则定时触发
function x270171_ProcTiming( sceneId, monsterobjid )

end

--玩家离开一个 area 时触发
function x270171_ProcAreaLeaved( sceneId, monsterobjid, ScriptId, MissionId )

end


function x270171_ProcEventEntry( sceneId, monsterobjid )

end

