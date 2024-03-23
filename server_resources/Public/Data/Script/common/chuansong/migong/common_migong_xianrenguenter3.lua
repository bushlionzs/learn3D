--功能：仙人谷Trap
--Trap



x550313_g_ScriptId = 550313
x550313_g_TransPos="xianrenguenterthree"


--玩家进入一个 area 时触发
function x550313_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
	CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550313_g_TransPos)
end

--玩家在一个 area 呆了一段时间没走则定时触发
function x550313_ProcTiming( sceneId, monsterobjid )

end

--玩家离开一个 area 时触发
function x550313_ProcAreaLeaved( sceneId, monsterobjid, ScriptId, MissionId )

end


function x550313_ProcEventEntry( sceneId, monsterobjid )

end

