
x400221_g_scriptId = 400221 
x400221_g_Impact1 = 3001 --Ч��ID�������Ӻ���

function x400221_ProcEventEntry( sceneId, selfId, bagIndex )
--print(111)
	return CallScriptFunction( MISSION_SCRIPT, "PositionUseItem", sceneId, selfId, bagIndex, x400221_g_Impact1 )
end

function x400221_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�
end

function x400221_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

function x400221_OnConditionCheck( sceneId, selfId )
	return 0
end

function x400221_OnDeplete( sceneId, selfId )
	return 0
end

function x400221_OnActivateOnce( sceneId, selfId )
end

function x400221_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
