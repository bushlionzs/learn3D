--ͻ������ըҩ
x413314_g_scriptId = 413314
x413314_g_Impact1 = 7524 --Ч��ID�������Ӻ���

function x413314_ProcEventEntry( sceneId, selfId, bagIndex )
 
	local bCplay =  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem", sceneId, selfId, bagIndex, x413314_g_Impact1 )
    
    if bCplay == 1 then
        SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, x413314_g_Impact1, 0);
    end

    return bCplay
end

function x413314_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�

end

function x413314_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��

end

function x413314_OnConditionCheck( sceneId, selfId )
	return 0
end

function x413314_OnDeplete( sceneId, selfId )
	return 0
end

function x413314_OnActivateOnce( sceneId, selfId )
end

function x413314_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
