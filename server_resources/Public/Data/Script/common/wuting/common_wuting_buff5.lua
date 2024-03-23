
x300174_g_ScriptId = 300174
x300174_g_FarScriptId = 300160
x300174_g_BuffId = 7646

function x300174_ProcEnumEvent( sceneId, selfId, NPCId, MissionId)
	
	--场景限制写死
	if sceneId ~= 0 and sceneId ~= 14 then
		return
	end
	
    AddQuestNumText( sceneId, x300174_g_ScriptId, "领取基础奖励", 8, 1)
end

function x300174_ProcEventEntry( sceneId, selfId, NPCId, idScript, idExt)
	
	--场景限制写死
	if sceneId ~= 0 and sceneId ~= 14 then
		return
	end
	
    BeginQuestEvent( sceneId)
        AddQuestText( sceneId, "#Y".."大都美丽会" )
        AddQuestText( sceneId, format( "\t您是否要花费银卡（现银）#G   #{_MONEY%d}#W领取基础奖励？", GetLevel( sceneId, selfId) * 200) )
    EndQuestEvent()
    DispatchQuestInfo( sceneId, selfId, NPCId, x300174_g_ScriptId, -1)
end

function x300174_ProcAcceptCheck( sceneId, selfId, NPCId)
	
	--场景限制写死
	if sceneId ~= 0 and sceneId ~= 14 then
		return 0
	end
	
    if CallScriptFunction( x300174_g_FarScriptId, "IsOverDay", sceneId, selfId) == 0 then
        Msg2Player( sceneId, selfId, "很抱歉，24小时内只能领取一次基础奖励", 8, 3)
        return 0
    end

    local costMoney = GetLevel( sceneId, selfId) * 200
    if CostMoney( sceneId, selfId, 1, costMoney,306) == -1 then
        if CostMoney( sceneId, selfId, 0, costMoney,306) == -1 then
            Msg2Player( sceneId, selfId, "很抱歉，您身上的银卡（现银）不足，不能领取基础奖励。", 8, 3)
            return 0
        end
    end

    SendSpecificImpactToUnit( sceneId, selfId, selfId, selfId, x300174_g_BuffId, 0)
    CallScriptFunction( x300174_g_FarScriptId, "SetBaseBuffTime", sceneId, selfId, GetMinOfYear() )
end

