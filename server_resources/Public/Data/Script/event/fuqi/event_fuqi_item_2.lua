
x300355_g_scriptId = 300355
x300355_g_Impact1 = -1 --Ч��ID�������Ӻ���

function x300355_ProcEventEntry( sceneId, selfId, bagIndex )
		local exp =  1000
		AddExp(sceneId, selfId, exp);

    return 1
end

function x300355_IsSkillLikeScript( sceneId, selfId)
	return 0; --����ű���Ҫ����֧��    
	--����0���������ProcEventEntry�߼�
	--����1����������߼�

 end

function x300355_CancelImpacts( sceneId, selfId )
	return 0; --����Ҫ����ӿڣ���Ҫ�����պ���,����ʼ�շ���0��
 
end

function x300355_OnConditionCheck( sceneId, selfId )
	return 0
end

function x300355_OnDeplete( sceneId, selfId )
	return 0
end

function x300355_OnActivateOnce( sceneId, selfId )
end

function x300355_OnActivateEachTick( sceneId, selfId)
	return 1; --���������Խű�, ֻ�����պ���.
end
