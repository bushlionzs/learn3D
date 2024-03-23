---------------------------------------------------------------------
-- fuben common area event
--副本回调函数:副本脚本可以Call这个脚本的函数
------------------------------------------------------------------
x700105_g_ScriptId			=	700105

--------------------------------------------------------------------------


--返回王城
function x700105_TeleportWangCheng(sceneId, selfId)
		local selfcountry =GetCurCountry( sceneId, selfId)
        TimerCommand( sceneId, selfId, 1, 7010, 3, -1, -1, -1 )
        TimerCommand( sceneId, selfId, 2, 7010, 3, -1, -1, -1 )
		if selfcountry == 0 then
        	NewWorld( sceneId, selfId, selfcountry * 100 + 50, 75 + random( 0, 5), 180 + random( 0, 5), x700105_g_ScriptId)
		elseif selfcountry ==1 then
			NewWorld( sceneId, selfId, selfcountry * 100 + 50, 75 + random( 0, 5), 180 + random( 0, 5), x700105_g_ScriptId)
		elseif selfcountry ==2 then
			NewWorld( sceneId, selfId, selfcountry * 100 + 50, 181 + random( 0, 5), 76 + random( 0, 5), x700105_g_ScriptId)
		elseif selfcountry ==3 then
			NewWorld( sceneId, selfId, selfcountry * 100 + 50, 181 + random( 0, 5), 76 + random( 0, 5), x700105_g_ScriptId)
		end
end


function x700105_ProcEventEntry(sceneId, selfId, NPCId,MissionId, nFlag)

	--print("x700105_ProcEventEntry",MissionId,nFlag)
	
	SetPlayerRuntimeData(sceneId,selfId,RD_COMMON_NPCID, nFlag)
	local nScriptId = GetFubenData_Param(sceneId, 1)
	if nFlag == 2 then
		BeginQuestEvent(sceneId)
		local desc = CallScriptFunction(700081,"GetNextLoopFubenDesc", sceneId, selfId, nScriptId)
		
		AddQuestText(sceneId,desc)
		EndQuestEvent(sceneId)
		
		--CallScriptFunction(700081,"NextLoopFuben", sceneId, selfId, nScriptId)
		--DispatchQuestEventList(sceneId,selfId,selfId)
		
		DispatchQuestInfoNM(sceneId, selfId, selfId, x700105_g_ScriptId, MissionId)
	elseif nFlag == 1 then
		--x700105_TeleportWangCheng(sceneId, selfId)
		local desc = CallScriptFunction(700081,"GetTeleportWangchengDesc", sceneId, selfId, nScriptId)
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,desc)
		EndQuestEvent(sceneId)
		
		DispatchQuestInfoNM(sceneId, selfId, selfId, x700105_g_ScriptId, MissionId)
	end
end


function x700105_ProcQuestAccept( sceneId, selfId, NPCId, MissionId)
	local nFlag = GetPlayerRuntimeData(sceneId,selfId,RD_COMMON_NPCID)
	local nScriptId = GetFubenData_Param(sceneId, 1)
	if nFlag == 2 then
		CallScriptFunction(700081,"NextLoopFuben", sceneId, selfId, nScriptId)
	elseif nFlag == 1 then
		x700105_TeleportWangCheng(sceneId, selfId)
	end
end


function x700105_PopupFubenMenu( sceneId, selfId, nEnter, MissionId, nScriptId, bLastLoop  )
	--print("x700105_PopupFubenMenu")
	if nEnter == 0 then  --出口
		--print("nScriptId",nScriptId)
		local desc = CallScriptFunction(700081,"GetLeaveFubenDesc", sceneId, selfId, nScriptId)
		BeginQuestEvent(sceneId)
		AddQuestText(sceneId,desc)
		
		if bLastLoop == nil or bLastLoop == 0 then
			AddQuestNumText(sceneId,MissionId,"进入下一环", 0, 2)
		else
			AddQuestNumText(sceneId,MissionId,"返回王城", 0, 1)
		end
		EndQuestEvent(sceneId)
		
		DispatchQuestEventList(sceneId,selfId,selfId)
	elseif nEnter == 1 then    --入口
		local desc = CallScriptFunction(700081,"GetEnterFubenDesc", sceneId, selfId, nScriptId)
		BeginQuestEvent(sceneId)
		
		
		AddQuestText(sceneId,desc)
		AddQuestNumText(sceneId,MissionId,"返回王城", 0, 1)
		EndQuestEvent(sceneId)
		DispatchQuestEventList(sceneId,selfId,selfId)
	end
end	