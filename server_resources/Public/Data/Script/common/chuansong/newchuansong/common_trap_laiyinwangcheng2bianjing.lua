

x550102_g_ScriptId = 550102
x550102_g_TransPos="laiyinwangcheng2bianjing"


--玩家进入一个 area 时触发
function x550102_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
	CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550102_g_TransPos)
end

--玩家在一个 area 呆了一段时间没走则定时触发
function x550102_ProcTiming( sceneId, monsterobjid )

end

--玩家离开一个 area 时触发
function x550102_ProcAreaLeaved( sceneId, monsterobjid, ScriptId, MissionId )

end


function x550102_ProcEventEntry( sceneId, monsterobjid )

end

