
x413202_g_scriptId = 413202 
x413202_g_Impact1 = 8312 --Ч��ID�������Ӻ���

function x413202_ProcEventEntry( sceneId, selfId, bagIndex )
	return CallScriptFunction( MISSION_SCRIPT, "PositionUseItem", sceneId, selfId, bagIndex, x413202_g_Impact1 )
end

function x413202_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�

end

function x413202_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��

end

function x413202_OnConditionCheck( sceneId, selfId )
	return 0
end

function x413202_OnDeplete( sceneId, selfId )
	return 0
end

function x413202_OnActivateOnce( sceneId, selfId )
end

function x413202_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
