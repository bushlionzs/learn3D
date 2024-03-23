--功能：地下粮仓Trap
--Trap

x550316_g_ScriptId = 550316
x550316_g_TransPos="xianrenguexitfour"


--玩家进入一个 area 时触发
function x550316_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
	CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550316_g_TransPos)
end

--玩家在一个 area 呆了一段时间没走则定时触发
function x550316_ProcTiming( sceneId, monsterobjid )

end

--玩家离开一个 area 时触发
function x550316_ProcAreaLeaved( sceneId, monsterobjid, ScriptId, MissionId )

end


function x550316_ProcEventEntry( sceneId, monsterobjid )

end

