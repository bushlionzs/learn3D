
x413130_g_scriptId = 413130 
x413130_g_FarScriptId	= 300230

function x413130_ProcEventEntry( sceneId, selfId, bagIndex )
	return CallScriptFunction( x413130_g_FarScriptId, "OnUseItem", sceneId, selfId, bagIndex )
end

function x413130_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�

end

function x413130_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��

end

function x413130_OnConditionCheck( sceneId, selfId )
	return 0
end

function x413130_OnDeplete( sceneId, selfId )
	return 0
end

function x413130_OnActivateOnce( sceneId, selfId )
end

function x413130_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
