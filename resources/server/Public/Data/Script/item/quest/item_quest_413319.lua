
x413319_g_scriptId = 413319 
x413319_g_Impact1 = 7520 --Ч��ID�������Ӻ���

function x413319_ProcEventEntry( sceneId, selfId, bagIndex )

	local bCplay =  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem", sceneId, selfId, bagIndex, x413319_g_Impact1 )
    
    if bCplay == 1 then
        SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, x413319_g_Impact1, 0);
    end

    return bCplay
  end

function x413319_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�

end

function x413319_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��

end

function x413319_OnConditionCheck( sceneId, selfId )
	return 0
end

function x413319_OnDeplete( sceneId, selfId )
	return 0
end

function x413319_OnActivateOnce( sceneId, selfId )
end

function x413319_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
