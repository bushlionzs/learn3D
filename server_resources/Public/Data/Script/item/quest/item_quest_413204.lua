
x413204_g_scriptId = 413204 
x413204_g_Impact1 = 8314 --Ч��ID�������Ӻ���

function x413204_ProcEventEntry( sceneId, selfId, bagIndex )
	return CallScriptFunction( MISSION_SCRIPT, "PositionUseItem", sceneId, selfId, bagIndex, x413204_g_Impact1 )
end

function x413204_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�

end

function x413204_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��

end

function x413204_OnConditionCheck( sceneId, selfId )
	return 0
end

function x413204_OnDeplete( sceneId, selfId )
	return 0
end

function x413204_OnActivateOnce( sceneId, selfId )
end

function x413204_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
