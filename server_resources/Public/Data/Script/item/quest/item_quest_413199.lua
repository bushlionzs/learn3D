
x413199_g_scriptId = 413199 
x413199_g_Impact1 = 3001 --Ч��ID�������Ӻ���

function x413199_ProcEventEntry( sceneId, selfId, bagIndex )
	return CallScriptFunction( MISSION_SCRIPT, "PositionUseItem", sceneId, selfId, bagIndex, x413199_g_Impact1 )
end

function x413199_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�

end

function x413199_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��

end

function x413199_OnConditionCheck( sceneId, selfId )
	return 0
end

function x413199_OnDeplete( sceneId, selfId )
	return 0
end

function x413199_OnActivateOnce( sceneId, selfId )
end

function x413199_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
