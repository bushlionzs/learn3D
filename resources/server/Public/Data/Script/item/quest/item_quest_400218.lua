





x400218_g_scriptId = 400218 
x400218_g_Impact1 = 3001 --Ч��ID�������Ӻ���

function x400218_ProcEventEntry( sceneId, selfId, BagIndex )
		CallScriptFunction( 203311, "useitem", sceneId, selfId)
	

end

function x400218_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�
end

function x400218_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

function x400218_OnConditionCheck( sceneId, selfId )
	return 0
end

function x400218_OnDeplete( sceneId, selfId )

	return 0
end

function x400218_OnActivateOnce( sceneId, selfId )
end

function x400218_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
