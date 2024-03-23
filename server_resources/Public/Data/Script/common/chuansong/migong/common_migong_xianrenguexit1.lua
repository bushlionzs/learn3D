--功能：仙人谷Trap
--Trap

x550310_g_ScriptId = 550310
x550310_g_TransPos={"xianrenguexitone1","xianrenguexitone2","xianrenguexitone3","xianrenguexitone4"}


--玩家进入一个 area 时触发
function x550310_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )

	local country = GetCurCountry(sceneId, selfId)
	if country == 0 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550310_g_TransPos[1])
	elseif country == 1 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550310_g_TransPos[2])
	elseif country == 2 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550310_g_TransPos[3])
	elseif country == 3 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550310_g_TransPos[4])
	end

end

--玩家在一个 area 呆了一段时间没走则定时触发
function x550310_ProcTiming( sceneId, monsterobjid )

end

--玩家离开一个 area 时触发
function x550310_ProcAreaLeaved( sceneId, monsterobjid, ScriptId, MissionId )

end


function x550310_ProcEventEntry( sceneId, monsterobjid )

end

