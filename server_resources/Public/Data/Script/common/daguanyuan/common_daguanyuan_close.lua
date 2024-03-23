
x310372_g_ScriptId 		= 310372



function x310372_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
end

function x310372_ProcEventEntry( sceneId, selfId, BagIndex )
end

function x310372_ProcEnumEvent(sceneId, selfId, NPCId, MissionId)
end

function x310372_OnTimerDoingStart( sceneId, TimerId, Param1, Param2, Param3, Param4, Param5)
	--print("x310320_OnTimerDoingStart")
    SetSystemTimerTick( sceneId, 310372, "OnTimer", TimerId, 1000)
    
end

function x310372_OnTimer( sceneId, TimerId, uTime)
	--print("x310320_OnTimer", uTime,x310320_g_State)
	local hour,minute,sec =GetHourMinSec();
	if hour == 23 and minute == 0 and sec >= 0 then
		local nHumanCount = GetScenePlayerCount( sceneId)
	    if nHumanCount > 0 then
	        for i = 0, nHumanCount do
	            local objId = GetScenePlayerObjId( sceneId,i)
	            if objId >= 0 then
        			SendSpecificImpactToUnit( sceneId, objId, objId, objId, 8400, 0) 
	            end
	        end
	    end
	end

    -- Çå³ý²ÊÆ±ºÅÂë
    SetCountryParam( sceneId, 0, CD_DAGUANYUAN_CAIPIAO1, -1)
end
