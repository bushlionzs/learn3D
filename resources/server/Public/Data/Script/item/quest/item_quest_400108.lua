
x400108_g_scriptId = 400108
x400108_g_Impact1 = -1 --Ч��ID�������Ӻ���

function x400108_ProcEventEntry( sceneId, selfId, bagIndex )

	return CallScriptFunction( MISSION_SCRIPT, "PositionUseItem", sceneId, selfId, bagIndex, x400108_g_Impact1 )
end

function x400108_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�

end

function x400108_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��

end

function x400108_OnConditionCheck( sceneId, selfId )
	return 0
end

function x400108_OnDeplete( sceneId, selfId )
	return 0
end

function x400108_OnActivateOnce( sceneId, selfId )
end

function x400108_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
