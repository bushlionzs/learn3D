





x400213_g_scriptId = 400213 
x400213_g_Impact1 = 3001 --Ч��ID�������Ӻ���

function x400213_ProcEventEntry( sceneId, selfId, BagIndex )
			CallScriptFunction( MISSION_SCRIPT, "PositionUseItem", sceneId, selfId, BagIndex, x400213_g_Impact1 )
	

end

function x400213_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�
end

function x400213_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

function x400213_OnConditionCheck( sceneId, selfId )
	return 0
end

function x400213_OnDeplete( sceneId, selfId )

	return 0
end

function x400213_OnActivateOnce( sceneId, selfId )
end

function x400213_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
