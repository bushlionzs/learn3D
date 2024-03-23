--功能：地下粮仓Trap
--Trap


x550309_g_ScriptId = 550309
x550309_g_TransPos="liangcangexitfive"


--玩家进入一个 area 时触发
function x550309_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
	CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550309_g_TransPos)
end

--玩家在一个 area 呆了一段时间没走则定时触发
function x550309_ProcTiming( sceneId, monsterobjid )

end

--玩家离开一个 area 时触发
function x550309_ProcAreaLeaved( sceneId, monsterobjid, ScriptId, MissionId )

end


function x550309_ProcEventEntry( sceneId, monsterobjid )

end

