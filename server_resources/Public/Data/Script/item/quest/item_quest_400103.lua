
x400103_g_scriptId = 400103
x400103_g_Impact1 = 7519 --Ч��ID�������Ӻ���

function x400103_ProcEventEntry( sceneId, selfId, bagIndex )

local bCplay =  CallScriptFunction( MISSION_SCRIPT, "PositionUseItem", sceneId, selfId, bagIndex, x400103_g_Impact1 )
    
    if bCplay == 1 then
        SendSpecificImpactToUnit(sceneId, selfId, selfId, selfId, x400103_g_Impact1, 0);
    end

    return bCplay
end

function x400103_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�

 end

function x400103_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
 
end

function x400103_OnConditionCheck( sceneId, selfId )
	return 0
end

function x400103_OnDeplete( sceneId, selfId )
	return 0
end

function x400103_OnActivateOnce( sceneId, selfId )
end

function x400103_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
