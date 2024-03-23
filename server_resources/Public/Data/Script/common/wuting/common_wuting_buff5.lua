
x300174_g_ScriptId = 300174
x300174_g_FarScriptId = 300160
x300174_g_BuffId = 7646

function x300174_ProcEnumEvent( sceneId, selfId, NPCId, MissionId)
	
	--��������д��
	if sceneId ~= 0 and sceneId ~= 14 then
		return
	end
	
    AddQuestNumText( sceneId, x300174_g_ScriptId, "��ȡ��������", 8, 1)
end

function x300174_ProcEventEntry( sceneId, selfId, NPCId, idScript, idExt)
	
	--��������д��
	if sceneId ~= 0 and sceneId ~= 14 then
		return
	end
	
    BeginQuestEvent( sceneId)
        AddQuestText( sceneId, "#Y".."��������" )
        AddQuestText( sceneId, format( "\t���Ƿ�Ҫ����������������#G   #{_MONEY%d}#W��ȡ����������", GetLevel( sceneId, selfId) * 200) )
    EndQuestEvent()
    DispatchQuestInfo( sceneId, selfId, NPCId, x300174_g_ScriptId, -1)
end

function x300174_ProcAcceptCheck( sceneId, selfId, NPCId)
	
	--��������д��
	if sceneId ~= 0 and sceneId ~= 14 then
		return 0
	end
	
    if CallScriptFunction( x300174_g_FarScriptId, "IsOverDay", sceneId, selfId) == 0 then
        Msg2Player( sceneId, selfId, "�ܱ�Ǹ��24Сʱ��ֻ����ȡһ�λ�������", 8, 3)
        return 0
    end

    local costMoney = GetLevel( sceneId, selfId) * 200
    if CostMoney( sceneId, selfId, 1, costMoney,306) == -1 then
        if CostMoney( sceneId, selfId, 0, costMoney,306) == -1 then
            Msg2Player( sceneId, selfId, "�ܱ�Ǹ�������ϵ����������������㣬������ȡ����������", 8, 3)
            return 0
        end
    end

    SendSpecificImpactToUnit( sceneId, selfId, selfId, selfId, x300174_g_BuffId, 0)
    CallScriptFunction( x300174_g_FarScriptId, "SetBaseBuffTime", sceneId, selfId, GetMinOfYear() )
end

