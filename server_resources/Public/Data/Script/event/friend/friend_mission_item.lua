
x300781_g_scriptId = 300781
x300781_g_Impact1 = 7519 --Ч��ID�������Ӻ���

function x300781_ProcEventEntry( sceneId, selfId, bagIndex )
		local bCplay =  CallScriptFunction( 300782, "PositionUseItem", sceneId, selfId, bagIndex, x300781_g_Impact1 )
    
    if bCplay == 1 then
        SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, x300781_g_Impact1, 0);
    end

    return bCplay
end

function x300781_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�

 end

function x300781_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
 
end

function x300781_OnConditionCheck( sceneId, selfId )
	return 0
end

function x300781_OnDeplete( sceneId, selfId )
	return 0
end

function x300781_OnActivateOnce( sceneId, selfId )
end

function x300781_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
