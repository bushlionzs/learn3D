
x310342_g_ScriptId 		= 310342
x310342_g_HongBuff		= 7536
x310342_g_LanBuff		= 7537


function x310342_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
end
function x310342_ProcEventEntry( sceneId, selfId, BagIndex )
end

function x310342_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
end
function x310342_OnTimerDoingStart( sceneId, TimerId, Param1, Param2, Param3, Param4, Param5)
	--print("x310320_OnTimerDoingStart")
    SetSystemTimerTick( sceneId, 310342, "OnTimer", TimerId, 1000)
    
end
function x310342_OnTimer( sceneId, TimerId, uTime)
	--print("x310320_OnTimer", uTime,x310320_g_State)
	local hour,minute,sec =GetHourMinSec();
	if hour == 23 and minute == 0 and sec >= 0 then
		local nHumanCount = GetScenePlayerCount( sceneId)
	    if nHumanCount > 0 then
	        for i = 0, nHumanCount do
	            local objId = GetScenePlayerObjId( sceneId,i)
	            if objId >= 0 then
	            	CancelSpecificImpact( sceneId, objId, x310342_g_HongBuff)
        			CancelSpecificImpact( sceneId, objId, x310342_g_LanBuff)
        			SendSpecificImpactToUnit( sceneId, objId, objId, objId, 8400, 0) 
	            end
	        end
	    end
    
		
	end
end