--ͻ������ըҩ
x413316_g_scriptId = 413316
x413316_g_Impact1 = 7524 --Ч��ID�������Ӻ���

function x413316_ProcEventEntry( sceneId, selfId, bagIndex )
 
	local bCplay =  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem", sceneId, selfId, bagIndex, x413316_g_Impact1 )
    
    if bCplay == 1 then
        SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, x413316_g_Impact1, 0);
    end

    return bCplay
end

function x413316_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�

end

function x413316_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��

end

function x413316_OnConditionCheck( sceneId, selfId )
	return 0
end

function x413316_OnDeplete( sceneId, selfId )
	return 0
end

function x413316_OnActivateOnce( sceneId, selfId )
end

function x413316_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
