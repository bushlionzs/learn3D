
x400101_g_scriptId = 400101 
x400101_g_Impact1 = 7528 --Ч��ID�������Ӻ���

function x400101_ProcEventEntry( sceneId, selfId, bagIndex )
local bCplay =  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem", sceneId, selfId, bagIndex, x400101_g_Impact1 )
    
    if bCplay == 1 then
        SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, x400101_g_Impact1, 0);
    end

    return bCplay
end

function x400101_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�

end

function x400101_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��

end

function x400101_OnConditionCheck( sceneId, selfId )
	return 0
end

function x400101_OnDeplete( sceneId, selfId )
	return 0
end

function x400101_OnActivateOnce( sceneId, selfId )
end

function x400101_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
