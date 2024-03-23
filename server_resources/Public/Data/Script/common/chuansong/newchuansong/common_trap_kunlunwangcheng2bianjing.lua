

x550103_g_ScriptId = 550103
x550103_g_TransPos="kunlunwangcheng2bianjing"


--玩家进入一个 area 时触发
function x550103_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
	CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550103_g_TransPos)
end

--玩家在一个 area 呆了一段时间没走则定时触发
function x550103_ProcTiming( sceneId, monsterobjid )

end

--玩家离开一个 area 时触发
function x550103_ProcAreaLeaved( sceneId, monsterobjid, ScriptId, MissionId )

end


function x550103_ProcEventEntry( sceneId, monsterobjid )

end

