
x400106_g_scriptId = 400106
x400106_g_Impact1 = 3001 --Ч��ID�������Ӻ���

function x400106_ProcEventEntry( sceneId, selfId, bagIndex )
	return CallScriptFunction( MISSION_SCRIPT, "PositionUseItem", sceneId, selfId, bagIndex, x400106_g_Impact1 )
end

function x400106_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�
end

function x400106_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��

end

function x400106_OnConditionCheck( sceneId, selfId )
	return 0
end

function x400106_OnDeplete( sceneId, selfId )
	return 0
end

function x400106_OnActivateOnce( sceneId, selfId )
end

function x400106_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
