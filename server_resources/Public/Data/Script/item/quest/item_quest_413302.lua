
x413302_g_scriptId = 413302
x413302_g_Impact1 = 7524 --Ч��ID�������Ӻ���


function x413302_ProcEventEntry( sceneId, selfId, bagIndex )
	local bCplay =  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem", sceneId, selfId, bagIndex, x413302_g_Impact1 )
    
    if bCplay == 1 then
        SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, x413302_g_Impact1, 0);
    end

    return bCplay
end

function x413302_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�

end

function x413302_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��

end

function x413302_OnConditionCheck( sceneId, selfId )
	return 0
end

function x413302_OnDeplete( sceneId, selfId )
	return 0
end

function x413302_OnActivateOnce( sceneId, selfId )
end

function x413302_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
