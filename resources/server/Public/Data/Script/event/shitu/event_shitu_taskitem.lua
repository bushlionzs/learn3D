
x310301_g_scriptId = 310301
x310301_g_Impact1 = 8308 --Ч��ID�������Ӻ���

function x310301_ProcEventEntry( sceneId, selfId, bagIndex )
		local bCplay =  CallScriptFunction( 310300, "PositionUseItem", sceneId, selfId, bagIndex, x310301_g_Impact1 )
    
    if bCplay == 1 then
        SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, x310301_g_Impact1, 0);
    end

    return bCplay
end

function x310301_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�

 end

function x310301_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
 
end

function x310301_OnConditionCheck( sceneId, selfId )
	return 0
end

function x310301_OnDeplete( sceneId, selfId )
	return 0
end

function x310301_OnActivateOnce( sceneId, selfId )
end

function x310301_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
