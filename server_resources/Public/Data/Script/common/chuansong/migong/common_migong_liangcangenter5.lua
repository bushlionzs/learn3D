--功能：地下粮仓Trap
--Trap

x550304_g_ScriptId = 550304
x550304_g_MissionName="地下粮仓"
x550304_g_TransPos="liangcangenterfive"


--玩家进入一个 area 时触发
function x550304_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
	CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550304_g_TransPos)
end

--玩家在一个 area 呆了一段时间没走则定时触发
function x550304_ProcTiming( sceneId, monsterobjid )

end

--玩家离开一个 area 时触发
function x550304_ProcAreaLeaved( sceneId, monsterobjid, ScriptId, MissionId )

end


function x550304_ProcEventEntry( sceneId, monsterobjid )

end

