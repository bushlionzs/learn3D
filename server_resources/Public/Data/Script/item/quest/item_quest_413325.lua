
x413325_g_scriptId = 413325
x413325_g_Impact1 = 7524 --Ч��ID�������Ӻ���

function x413325_ProcEventEntry( sceneId, selfId, bagIndex )

		local bCplay =  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem", sceneId, selfId, bagIndex, x413325_g_Impact1 )
    
    if bCplay == 1 then
        SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, x413325_g_Impact1, 0);
    end

    return bCplay
end

function x413325_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�

end

function x413325_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

function x413325_OnConditionCheck( sceneId, selfId )
	return 0
end

function x413325_OnDeplete( sceneId, selfId )
	return 0
end

function x413325_OnActivateOnce( sceneId, selfId )
end

function x413325_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
