





x400209_g_scriptId = 400209 
x400209_g_Impact1 = 3001 --Ч��ID�������Ӻ���

function x400209_ProcEventEntry( sceneId, selfId, BagIndex )
		CallScriptFunction( 270015, "useitem", sceneId, selfId,0)
	

end

function x400209_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�
end

function x400209_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

function x400209_OnConditionCheck( sceneId, selfId )
	return 0
end

function x400209_OnDeplete( sceneId, selfId )

	return 1
end

function x400209_OnActivateOnce( sceneId, selfId )
end

function x400209_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
