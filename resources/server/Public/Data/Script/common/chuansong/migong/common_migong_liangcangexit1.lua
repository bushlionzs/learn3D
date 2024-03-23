

x550305_g_ScriptId = 550305
x550305_g_TransPos1="liangcangexitone1"
x550305_g_TransPos2="liangcangexitone2"
x550305_g_TransPos3="liangcangexitone3"
x550305_g_TransPos4="liangcangexitone4"


--玩家进入一个 area 时触发
function x550305_ProcAreaEntered( sceneId, selfId, zoneId, MissionId )
	local country = GetCurCountry(sceneId , selfId )
	
	if country == 0 then 
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550305_g_TransPos1)	
	elseif country == 1 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550305_g_TransPos2)
	elseif country == 2 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550305_g_TransPos3)
	elseif country == 3 then
		CallScriptFunction(COMMON_CHUANSONG_NORMAL, "TransferToWorld",sceneId,selfId,x550305_g_TransPos4)
	end
end

--玩家在一个 area 呆了一段时间没走则定时触发
function x550305_ProcTiming( sceneId, monsterobjid )

end

--玩家离开一个 area 时触发
function x550305_ProcAreaLeaved( sceneId, monsterobjid, ScriptId, MissionId )

end


function x550305_ProcEventEntry( sceneId, monsterobjid )

end

