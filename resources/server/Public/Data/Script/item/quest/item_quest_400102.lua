
x400102_g_scriptId = 400102 
x400102_g_Impact1 = 7518 --Ч��ID�������Ӻ���

function x400102_ProcEventEntry( sceneId, selfId, bagIndex )

	local bCplay =  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem", sceneId, selfId, bagIndex, x400102_g_Impact1 )
    
    if bCplay == 1 then
        SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, x400102_g_Impact1, 0);
    end

    return bCplay
  end

function x400102_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�

end

function x400102_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��

end

function x400102_OnConditionCheck( sceneId, selfId )
	return 0
end

function x400102_OnDeplete( sceneId, selfId )
	return 0
end

function x400102_OnActivateOnce( sceneId, selfId )
end

function x400102_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
