
x400104_g_scriptId = 400104
x400104_g_Impact1 = 3001 --Ч��ID�������Ӻ���

function x400104_ProcEventEntry( sceneId, selfId, bagIndex )
	return CallScriptFunction( MISSION_SCRIPT, "PositionUseItem", sceneId, selfId, bagIndex, x400104_g_Impact1 )
end

function x400104_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�

end

function x400104_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��

end

function x400104_OnConditionCheck( sceneId, selfId )
	return 0
end

function x400104_OnDeplete( sceneId, selfId )
	return 0
end

function x400104_OnActivateOnce( sceneId, selfId )
end

function x400104_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
