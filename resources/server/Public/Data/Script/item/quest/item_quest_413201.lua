
x413201_g_scriptId = 413201 
x413201_g_Impact1 = 8311 --Ч��ID�������Ӻ���

function x413201_ProcEventEntry( sceneId, selfId, bagIndex )
	return CallScriptFunction( MISSION_SCRIPT, "PositionUseItem", sceneId, selfId, bagIndex, x413201_g_Impact1 )
end

function x413201_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�

end

function x413201_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��

end

function x413201_OnConditionCheck( sceneId, selfId )
	return 0
end

function x413201_OnDeplete( sceneId, selfId )
	return 0
end

function x413201_OnActivateOnce( sceneId, selfId )
end

function x413201_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
