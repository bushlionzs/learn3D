
x300353_g_scriptId = 300353
x300353_g_Impact1 = 7519 --Ч��ID�������Ӻ���

function x300353_ProcEventEntry( sceneId, selfId, bagIndex )
		local bCplay =  CallScriptFunction( 300352, "PositionUseItem", sceneId, selfId, bagIndex, x300353_g_Impact1 )
    
    if bCplay == 1 then
        SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, x300353_g_Impact1, 0);
    end

    return bCplay
end

function x300353_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�

 end

function x300353_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
 
end

function x300353_OnConditionCheck( sceneId, selfId )
	return 0
end

function x300353_OnDeplete( sceneId, selfId )
	return 0
end

function x300353_OnActivateOnce( sceneId, selfId )
end

function x300353_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
