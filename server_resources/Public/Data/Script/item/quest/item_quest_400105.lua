
x400105_g_scriptId = 400105
x400105_g_Impact1 = 7522 --Ч��ID�������Ӻ���

function x400105_ProcEventEntry( sceneId, selfId, bagIndex )
local bCplay =  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem", sceneId, selfId, bagIndex, x400105_g_Impact1 )
    
    if bCplay == 1 then
        SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, x400105_g_Impact1, 0);
    end

    return bCplay
end

function x400105_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�

end

function x400105_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��

end

function x400105_OnConditionCheck( sceneId, selfId )
	return 0
end

function x400105_OnDeplete( sceneId, selfId )
	return 0
end

function x400105_OnActivateOnce( sceneId, selfId )
end

function x400105_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
