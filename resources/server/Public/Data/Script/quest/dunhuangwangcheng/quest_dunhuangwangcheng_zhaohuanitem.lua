x256236_g_scriptId = 256236 
--x256236_g_Impact1 = 7528 --Ч��ID�������Ӻ���
x256236_g_Target_ScriptId =	256233

function x256236_ProcEventEntry( sceneId, selfId, BagIndex )

	CallScriptFunction( x256236_g_Target_ScriptId, "OnUseItem", sceneId, selfId, BagIndex, -1 )
    
end

function x256236_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�
end

function x256236_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

function x256236_OnConditionCheck( sceneId, selfId )
	return 0
end

function x256236_OnDeplete( sceneId, selfId )

	return 0
end

function x256236_OnActivateOnce( sceneId, selfId )
end

function x256236_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
