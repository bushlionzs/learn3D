
x413322_g_scriptId = 413322
x413322_g_Impact1 = 7524 --Ч��ID�������Ӻ���

function x413322_ProcEventEntry( sceneId, selfId, bagIndex )
 
	local bCplay =  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem", sceneId, selfId, bagIndex, x413322_g_Impact1 )
    
    if bCplay == 1 then
        SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, x413322_g_Impact1, 0);
    end

    return bCplay
end

function x413322_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�

end

function x413322_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��

end

function x413322_OnConditionCheck( sceneId, selfId )
	return 0
end

function x413322_OnDeplete( sceneId, selfId )
	return 0
end

function x413322_OnActivateOnce( sceneId, selfId )
end

function x413322_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
