--ͻ������ըҩ
x413315_g_scriptId = 413315
x413315_g_Impact1 = 7524 --Ч��ID�������Ӻ���

function x413315_ProcEventEntry( sceneId, selfId, bagIndex )
 
	local bCplay =  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem", sceneId, selfId, bagIndex, x413315_g_Impact1 )
    
    if bCplay == 1 then
        SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, x413315_g_Impact1, 0);
    end

    return bCplay
end

function x413315_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�

end

function x413315_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��

end

function x413315_OnConditionCheck( sceneId, selfId )
	return 0
end

function x413315_OnDeplete( sceneId, selfId )
	return 0
end

function x413315_OnActivateOnce( sceneId, selfId )
end

function x413315_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
