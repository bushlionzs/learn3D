





x400210_g_scriptId = 400210 
x400210_g_Impact1 = 3001 --Ч��ID�������Ӻ���

function x400210_ProcEventEntry( sceneId, selfId, BagIndex )
		CallScriptFunction( 270015, "useitem", sceneId, selfId,1)
	

end

function x400210_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�
end

function x400210_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

function x400210_OnConditionCheck( sceneId, selfId )
	return 0
end

function x400210_OnDeplete( sceneId, selfId )

	return 1
end

function x400210_OnActivateOnce( sceneId, selfId )
end

function x400210_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
