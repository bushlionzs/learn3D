





x400215_g_scriptId = 400215 
x400215_g_Impact1 = 3001 --Ч��ID�������Ӻ���

function x400215_ProcEventEntry( sceneId, selfId, BagIndex )
			CallScriptFunction( MISSION_SCRIPT, "PositionUseItem", sceneId, selfId, BagIndex, x400215_g_Impact1 )
	

end

function x400215_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�
end

function x400215_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

function x400215_OnConditionCheck( sceneId, selfId )
	return 0
end

function x400215_OnDeplete( sceneId, selfId )

	return 0
end

function x400215_OnActivateOnce( sceneId, selfId )
end

function x400215_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
