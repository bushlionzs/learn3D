
x413300_g_scriptId = 413300
x413300_g_Impact1 = 7528 --Ч��ID�������Ӻ���

function x413300_ProcEventEntry( sceneId, selfId, bagIndex )

		local bCplay =  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem", sceneId, selfId, bagIndex, x413300_g_Impact1 )
    
    if bCplay == 1 then
        SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, x413300_g_Impact1, 0);
    end

    return bCplay
end

function x413300_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�

end

function x413300_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

function x413300_OnConditionCheck( sceneId, selfId )
	return 0
end

function x413300_OnDeplete( sceneId, selfId )
	return 0
end

function x413300_OnActivateOnce( sceneId, selfId )
end

function x413300_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
