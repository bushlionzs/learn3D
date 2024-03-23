--功能：地下粮仓Trap
--Trap

x550312_g_ScriptId = 550312
x550312_g_TransPos={"xianrenguexittwo1","xianrenguexittwo2","xianrenguexittwo3","xianrenguexittwo4"}


--玩家进入一个 area 时触发
function x550312_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )

	local country = GetCurCountry(sceneId, selfId)
	if country == 0 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550312_g_TransPos[1])
	elseif country == 1 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550312_g_TransPos[2])
	elseif country == 2 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550312_g_TransPos[3])
	elseif country == 3 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550312_g_TransPos[4])
	end

end

--玩家在一个 area 呆了一段时间没走则定时触发
function x550312_ProcTiming( sceneId, monsterobjid )

end

--玩家离开一个 area 时触发
function x550312_ProcAreaLeaved( sceneId, monsterobjid, ScriptId, MissionId )

end


function x550312_ProcEventEntry( sceneId, monsterobjid )

end

