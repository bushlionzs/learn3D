
x400107_g_scriptId = 400107
x400107_g_Impact1 = 7519 --Ч��ID�������Ӻ���

function x400107_ProcEventEntry( sceneId, selfId, bagIndex )
local bCplay =  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem", sceneId, selfId, bagIndex, x400107_g_Impact1 )
    
    if bCplay == 1 then
        SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, x400107_g_Impact1, 0);
    end

    return bCplay
end

function x400107_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�

end

function x400107_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��

end

function x400107_OnConditionCheck( sceneId, selfId )
	return 0
end

function x400107_OnDeplete( sceneId, selfId )
	return 0
end

function x400107_OnActivateOnce( sceneId, selfId )
end

function x400107_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
