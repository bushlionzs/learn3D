x414029_g_scriptId = 414029 

function x414029_ProcEventEntry( sceneId, selfId, BagIndex )
	CallScriptFunction( 270300, "ItemProcEventEntry", sceneId, selfId, BagIndex )
end

function x414029_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�
end

function x414029_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

function x414029_OnConditionCheck( sceneId, selfId )
	return 0
end

function x414029_OnDeplete( sceneId, selfId )

	return 0
end

function x414029_OnActivateOnce( sceneId, selfId )
end

function x414029_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
