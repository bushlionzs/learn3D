
x413200_g_scriptId = 413200 
x413200_g_Impact1 = 8310 --Ч��ID�������Ӻ���

function x413200_ProcEventEntry( sceneId, selfId, bagIndex )
	return CallScriptFunction( MISSION_SCRIPT, "PositionUseItem", sceneId, selfId, bagIndex, x413200_g_Impact1 )
end

function x413200_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�

end

function x413200_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��

end

function x413200_OnConditionCheck( sceneId, selfId )
	return 0
end

function x413200_OnDeplete( sceneId, selfId )
	return 0
end

function x413200_OnActivateOnce( sceneId, selfId )
end

function x413200_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
