
x400005_g_scriptId = 400005 
x400005_g_Impact1 = 3001 --Ч��ID�������Ӻ���

function x400005_ProcEventEntry( sceneId, selfId, bagIndex )
--print(111)
	return CallScriptFunction( MISSION_SCRIPT, "PositionUseItem", sceneId, selfId, bagIndex, x400005_g_Impact1 )
end

function x400005_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�
end

function x400005_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

function x400005_OnConditionCheck( sceneId, selfId )
	return 0
end

function x400005_OnDeplete( sceneId, selfId )
	return 0
end

function x400005_OnActivateOnce( sceneId, selfId )
end

function x400005_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
