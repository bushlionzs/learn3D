





x400204_g_scriptId = 400204 
x400204_g_Impact1 = 7520 --Ч��ID�������Ӻ���

function x400204_ProcEventEntry( sceneId, selfId, BagIndex )
			CallScriptFunction( MISSION_SCRIPT, "PositionUseItem", sceneId, selfId, BagIndex, x400204_g_Impact1 )
	

end

function x400204_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�
end

function x400204_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

function x400204_OnConditionCheck( sceneId, selfId )
	return 0
end

function x400204_OnDeplete( sceneId, selfId )

	return 0
end

function x400204_OnActivateOnce( sceneId, selfId )
end

function x400204_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
