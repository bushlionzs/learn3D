

x550101_g_ScriptId = 550101
x550101_g_TransPos0="loulanwangcheng2bianjing"
x550101_g_TransPos1="laiyinwangcheng2bianjing"
x550101_g_TransPos2="kunlunwangcheng2bianjing"
x550101_g_TransPos3="dunhuangwangcheng2bianjing"

--玩家进入一个 area 时触发
function x550101_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
	if sceneId == 50 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550101_g_TransPos0)
	elseif sceneId == 150 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550101_g_TransPos1)
	elseif sceneId == 250 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550101_g_TransPos2)
	elseif sceneId == 350 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550101_g_TransPos3)
	end

end

--玩家在一个 area 呆了一段时间没走则定时触发
function x550101_ProcTiming( sceneId, monsterobjid )

end

--玩家离开一个 area 时触发
function x550101_ProcAreaLeaved( sceneId, monsterobjid, ScriptId, MissionId )

end


function x550101_ProcEventEntry( sceneId, monsterobjid )

end

