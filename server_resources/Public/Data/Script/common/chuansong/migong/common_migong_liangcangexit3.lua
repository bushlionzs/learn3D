--功能：地下粮仓Trap
--Trap



x550307_g_ScriptId = 550307
x550307_g_TransPos="liangcangexitthree"


--玩家进入一个 area 时触发
function x550307_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
	CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550307_g_TransPos)
end

--玩家在一个 area 呆了一段时间没走则定时触发
function x550307_ProcTiming( sceneId, monsterobjid )

end

--玩家离开一个 area 时触发
function x550307_ProcAreaLeaved( sceneId, monsterobjid, ScriptId, MissionId )

end


function x550307_ProcEventEntry( sceneId, monsterobjid )

end

