





x400208_g_scriptId = 400208 
x400208_g_Impact1 = 3001 --Ч��ID�������Ӻ���

function x400208_ProcEventEntry( sceneId, selfId, BagIndex )
		CallScriptFunction( 270012, "useitem", sceneId, selfId)
	

end

function x400208_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�
end

function x400208_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
end

function x400208_OnConditionCheck( sceneId, selfId )
	return 0
end

function x400208_OnDeplete( sceneId, selfId )

	return 1
end

function x400208_OnActivateOnce( sceneId, selfId )
end

function x400208_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
